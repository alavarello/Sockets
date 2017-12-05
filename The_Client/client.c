/****************** CLIENT CODE ****************/

#include <stdio.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <string.h>
#include "structs.h"
#include "serialize_flight.h"
#include "serialize_plane.h"
#include "serialize_reservation.h"
#include "clientParser.h"
#include "client.h"
#include <unistd.h>

//gcc client.c serialize_reservation.c serialize_plane.c serialize_flight.c clientParser.c -o client  -lsqlite3 -std=c99


char * resBuff;

int clientSocket, n;
char buffer[2048];struct sockaddr_in serverAddr;
socklen_t addr_size;

int initiateSocket(){
  struct timeval tv;
  printf("INITIATING\n");
  /*---- Create the socket. The three arguments are: ----*/
  /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
  clientSocket = socket(PF_INET, SOCK_STREAM, 0);
  printf("CLIENT SOCKET: %d\n",clientSocket );
  /*---- Configure settings of the server address struct ----*/
  /* Address family = Internet */
  serverAddr.sin_family = AF_INET;
  /* Set port number, using htons function to use proper byte order */
  serverAddr.sin_port = htons(5002);
  /* Set IP address to localhost */
  serverAddr.sin_addr.s_addr = inet_addr("10.2.69.99"); //this address is for local conection
  /* Set all bits of the padding field to 0 */
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

  /*---- Connect the socket to the server using the address struct ----*/
  addr_size = sizeof serverAddr;
  tv.tv_sec = 30;        // 30 Secs Timeout
  tv.tv_usec = 0;        // Not init'ing this can cause strange errors
  setsockopt(clientSocket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv,sizeof(struct timeval));
  return connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

  // add control if everything went fine
}

int sendMessage( char * parsedMessage, int bytes)
{
    int i = 0 ;
    while( i < bytes){
      n = write(clientSocket, parsedMessage, bytes - i);
      i += n;
      if(n == -1){
        return 0;
      }
    }

   return 1;
}

char * receiveMessage()
{
  int i = 0;

  char * pBuffer = malloc(2000 * sizeof(char));
  bzero(pBuffer,2000);
  n = read(clientSocket, pBuffer, 2000);
  if (n < 0) {
      perror("ERROR reading from socket");
      return NULL;
  }

  return pBuffer;
}

void * askForInfo(int instruction , void * message)
{
  int success;
  char * response;
  int bytes;

  char * parsedMessage = parseMessageToSend(instruction , message ,&bytes);

  success = sendMessage(parsedMessage, bytes);

  if(!success){
    logError("The server is not available");
    exit(1);
  }

  response = receiveMessage();

  if(response == NULL)
  {
    logError("The server is not available");
    exit(1);
  }

  return parseRecivedMessage(instruction, response);

}

tFlight * * getFlights()
{
  tFlightArray * parsed ;

  parsed = askForInfo(GET_ALL_FLIGHTS, NULL);

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

  seatsArray = (tSeatsArray * ) askForInfo(GET_RESERVATIONS_FOR_A_FLIGHT , flight->flightCode);

  if(seatsArray == NULL)
  {
    printf("ERROR COMMUNICATING\n");
    return NULL;
  }

  seats = malloc((seatsArray->size + 1)*sizeof(*seats));

  for(i = 0 ; i < seatsArray->size ; i++){
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
  char * name = malloc(100);
  name[0] = 0;
  sprintf(name, "%ld" , (long) getpid());

  newReservation->flightCode = malloc(10 * sizeof(char));
  strcpy(newReservation->flightCode, flight->flightCode);
  newReservation->seatNumber = malloc(10 * sizeof(char));
  strcpy(newReservation->seatNumber , seat);
  newReservation->userName = name;

  result = askForInfo(INSERT_RESERVATION , newReservation);

  free(newReservation);

  printf("result es %s\n",result );


  res = ERROR_RETURN(result);

  number =  *((int*)(result+6));

  printf("%d\n", number );

  if(res == 0){
    return -1 *  number;
  }else{
    return res;
  }

}

int cancel(tFlight * flight , char * seat){
  tReservation * newReservation = malloc(sizeof(*newReservation));
  char * result;
  char name[100];
  name[0] = 0;
  sprintf(name, "%ld" , (long) getpid());

  newReservation->flightCode = malloc(10 * sizeof(char));
  strcpy(newReservation->flightCode, flight->flightCode);
  newReservation->seatNumber = malloc(10 * sizeof(char));
  strcpy(newReservation->seatNumber , seat);

  newReservation->userName = name;

  result = askForInfo(INSERT_CANCELLATION, newReservation);

  free(newReservation);

  printf("%s\n",result );

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

  result = askForInfo(INSERT_FLIGHT, newFlight);

  free(newFlight);

  return  ERROR_RETURN(result);

}
int removeFlightClient(char * flightCode)
{
  char * result;

  result = askForInfo( DELETE_FLIGHT, flightCode);

  return  ERROR_RETURN(result);
}

tPlaneArray  * getPlanes()
{
  tPlaneArray * planes;

  planes = (tPlaneArray * ) askForInfo( GET_ALL_PLANES , NULL);

  return planes;
}

tReservationArray * getReservations()
{
  tReservationArray * reservations;

  reservations = (tReservationArray * ) askForInfo(GET_ALL_RESERVATIONS , NULL);

  return reservations;

}

tReservationArray * getCancelations()
{
  tReservationArray * reservations;

  reservations = (tReservationArray * ) askForInfo(GET_ALL_RESERVATIONS , NULL);

  return reservations;
}
