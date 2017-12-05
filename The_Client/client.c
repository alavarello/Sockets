/****************** CLIENT CODE ****************/
#include "client.h"
//gcc client.c serialize_reservation.c serialize_plane.c serialize_flight.c clientParser.c -o client  -lsqlite3 -std=c99


char * resBuff;

int clientSocket, n;
char buffer[2048];struct sockaddr_in serverAddr;
socklen_t addr_size;

void closeSocket()
{
  communicate(END_PROCESS , NULL);
  close(clientSocket);
}

int initiateSocket()
{
  struct timeval tv;
  /*---- Create the socket. The three arguments are: ----*/
  /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
  clientSocket = socket(PF_INET, SOCK_STREAM, 0);
  /*---- Configure settings of the server address struct ----*/
  /* Address family = Internet */
  serverAddr.sin_family = AF_INET;
  /* Set port number, using htons function to use proper byte order */
  serverAddr.sin_port = htons(5002);
  /* Set IP address to localhost */
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //this address is for local conection
  /* Set all bits of the padding field to 0 */
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

  /*---- Connect the socket to the server using the address struct ----*/
  addr_size = sizeof serverAddr;
  tv.tv_sec = 60 * 5;        // 5 min Timeout
  tv.tv_usec = 0;        // Not init'ing this can cause strange errors
  setsockopt(clientSocket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv,sizeof(struct timeval));
  return connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);
}

int sendMessage( char * parsedMessage, int bytes)
{
    int i = 0 ;
    while( i < bytes)
    {
      n = write(clientSocket, parsedMessage, bytes - i);
      i += n;
      if(n == -1)
      {
        return 0;
      }
    }

   return 1;
}

int getBytesForReading(int instruction){
  switch(instruction){
    case GET_ALL_FLIGHTS:
      return TFLIGHT_BYTES*MAX_FLIGHTS + sizeof(long);
    case GET_FLIGHT:
      return TFLIGHT_BYTES;
    case INSERT_FLIGHT:
      return ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int));
    case GET_ALL_PLANES:
      return TPLANES_BYTES*MAX_PLANES + 1*sizeof(long);
    case GET_ALL_RESERVATIONS:
      return TRESERVATION_BYTES*MAX_RESERVATIONS + sizeof(long);
    case INSERT_RESERVATION:
      return ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int));
    case INSERT_CANCELLATION:
      return ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int));
    case GET_RESERVATIONS_FOR_A_FLIGHT:
      return SEAT_NUMBER_CHAR_MAX*MAX_SEATS+sizeof(int);
    case GET_RESERVATION:
      return TRESERVATION_BYTES;
    case DELETE_FLIGHT:
      return ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int));
    case DELETE_RESERVATON:
      return ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int));
    default: return 0;
  }
}

char * receiveMessage(int instruction)
{
  char * pBuffer;
  int bytes = getBytesForReading(instruction);
  pBuffer = malloc(bytes * sizeof(char));
  bzero(pBuffer,bytes);
  n = read(clientSocket, pBuffer, bytes);
  if (n < 0)
  {
      perror("ERROR reading from socket");
      return NULL;
  }

  return pBuffer;
}

void * communicate(int instruction , void * message)
{
  int success;
  char * response;
  int bytes;

  char * parsedMessage = parseMessageToSend(instruction , message ,&bytes);

  success = sendMessage(parsedMessage, bytes);

  if(!success)
  {
    logError("The server is not available");
    closeSocket();
    exit(1);
  }

  response = receiveMessage(instruction);

  if(response == NULL)
  {
    logError("The server is not available");
    closeSocket();
    exit(1);
  }

  free(parsedMessage);

  return parseRecivedMessage(instruction, response);

}

tFlight * * getFlights()
{
  tFlightArray * parsed ;

  parsed = communicate(GET_ALL_FLIGHTS, NULL);

  parsed->flightArray = realloc(parsed->flightArray , (parsed->size + 1) * sizeof(*parsed->flightArray));

  parsed->flightArray[parsed->size] = NULL;

  return parsed->flightArray;
}

tPlane * getPlane(tFlight * flight)
{

  int i = 0 ;

  tPlaneArray  * planes = getPlanes();
  tPlane * aux ;

  for (i = 0 ; i < planes->size ; i++)
  {
    aux = planes->planeArray[i];
    if(strcmp(aux->model , flight->planeCode) == 0)
    {
      return aux;
    }

  }

  return NULL;

}

char * * getOccupiedSeats(tFlight * flight)
{
  tSeatsArray * seatsArray;
  int i ;
  char ** seats;

  seatsArray = (tSeatsArray * ) communicate(GET_RESERVATIONS_FOR_A_FLIGHT , flight->flightCode);

  if(seatsArray == NULL)
  {
    printf("ERROR COMMUNICATING\n");
    return NULL;
  }

  seats = malloc((seatsArray->size + 1)*sizeof(*seats));

  for(i = 0 ; i < seatsArray->size ; i++)
  {
    seats[i] = malloc(4 * sizeof(char));
    strcpy(seats[i] , seatsArray->reservedSeats[i]);
    free(seatsArray->reservedSeats[i]);
  }

  seats[i] = NULL;

  free(seatsArray->reservedSeats);
  free(seatsArray);

  return seats;
}

int reserve(tFlight * flight , char * seat)
{

  tReservation * newReservation = malloc(sizeof(*newReservation));
  char * result;
  int res;
  int number;
  char name[USER_NAME_CHAR_MAX];
  name[0] = 0;
  int size  = sprintf(name, "%ld" , (long) getpid());

  printf("se copiaron : %d\n", size);

  newReservation->flightCode = malloc(10 * sizeof(char));
  strcpy(newReservation->flightCode, flight->flightCode);
  newReservation->seatNumber = malloc(10 * sizeof(char));
  strcpy(newReservation->seatNumber , seat);
  newReservation->userName = calloc(USER_NAME_CHAR_MAX , sizeof(char));
  strcpy(newReservation->userName , name);

  result = communicate(INSERT_RESERVATION , newReservation);

  free(newReservation);

  res = ERROR_RETURN(result);

  number =  *((int*)(result+6));

  if(res == 0){
    return -1 *  number;
  }else{
    return res;
  }

}

int cancel(tFlight * flight , char * seat)
{
  tReservation * newReservation = malloc(sizeof(*newReservation));
  char * result;
  char name[USER_NAME_CHAR_MAX];
  name[0] = 0;
  sprintf(name, "%ld" , (long) getpid());

  newReservation->flightCode = malloc(10 * sizeof(char));
  strcpy(newReservation->flightCode, flight->flightCode);
  newReservation->seatNumber = malloc(10 * sizeof(char));
  strcpy(newReservation->seatNumber , seat);
  newReservation->userName = calloc(USER_NAME_CHAR_MAX, sizeof(char));
  strcpy(newReservation->userName , name);

  result = communicate(INSERT_CANCELLATION, newReservation);

  free(newReservation);

  return  ERROR_RETURN(result);
}

int addFlightClient(char * flightCode , char * origin ,char *   destination ,char *  departureTime ,char * arrivalTime ,char *  planeCode,char *  departureDate ,char *  arrivalDate)
{
  char * result;
  tFlight * newFlight = malloc(sizeof(*newFlight));

  newFlight->flightCode = flightCode;
  newFlight->origin = origin;
  newFlight->destination = destination;
  newFlight->departureTime = departureTime;
  newFlight->departureDate = departureDate;
  newFlight->arrivalTime = arrivalTime;
  newFlight->arrivalDate = arrivalDate;
  newFlight->planeCode = planeCode;

  result = communicate(INSERT_FLIGHT, newFlight);

  free(newFlight);

  return  ERROR_RETURN(result);

}
int removeFlightClient(char * flightCode)
{
  char * result;

  result = communicate( DELETE_FLIGHT, flightCode);

  return  ERROR_RETURN(result);
}

tPlaneArray  * getPlanes()
{
  tPlaneArray * planes;

  planes = (tPlaneArray * ) communicate( GET_ALL_PLANES , NULL);

  return planes;
}

tReservationArray * getReservations()
{
  tReservationArray * reservations;

  reservations = (tReservationArray * ) communicate(GET_ALL_RESERVATIONS , NULL);

  return reservations;

}

tReservationArray * getCancelations()
{
  tReservationArray * reservations;

  reservations = (tReservationArray * ) communicate(GET_ALL_CANCELATIONS , NULL);

  return reservations;
}
