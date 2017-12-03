/****************** CLIENT CODE ****************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include "structs.h"
#include "serialize_flight.h"
#include "serialize_plane.h"
#include "serialize_reservation.h"
#include "clientParser.h"
#include "client.h"

//gcc client.c serialize_reservation.c serialize_plane.c serialize_flight.c clientParser.c -o client  -lsqlite3 -std=c99


int clientSocket, n;
char buffer[2048];
char * resBuff;
struct sockaddr_in serverAddr;
socklen_t addr_size;

int initiateSocket(){

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
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //this address is for local conection
  /* Set all bits of the padding field to 0 */
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  /*---- Connect the socket to the server using the address struct ----*/
  addr_size = sizeof serverAddr;
  connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

  // add control if everything went fine
}

int sendMessage( char * parsedMessage, int bytes)
{
    
    printf("CLIENT SOCKET: %d\n",clientSocket );
    n = write(clientSocket, parsedMessage, bytes);
    printf("HOLAAA\n");
    if (n < 0) {
      return 0;
   }else{
      return 1;
   }
}

char * receiveMessage()
{
  char * pBuffer = malloc(2000 * sizeof(char)); 

  bzero(pBuffer,2000);
  n = read(clientSocket, pBuffer, 2000);
  if (n < 0) {
      perror("ERROR reading from socket");
      return NULL;
  }

  printf("Se leyeron %d \n", n );

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
    return NULL;
  }

  response = receiveMessage();

  if(response == NULL)
  {
    return NULL;
  }

  return parseRecivedMessage(instruction, response);

}

tFlight * * getFlights()
{
  tFlightArray * parsed ;

  parsed = askForInfo(GET_ALL_FLIGHTS, NULL);

  if(parsed == NULL)
  {
    printf("ERROR COMMUNICATING\n");
    return NULL;
  }

  parsed->flightArray = realloc(parsed->flightArray , (parsed->size + 1) * sizeof(*parsed->flightArray));

  parsed->flightArray[parsed->size] = NULL;

  return parsed->flightArray;
}

tPlane * getPlane(tFlight * flight)
{

  tPlane * plane = (tPlane * ) malloc(sizeof(tPlane));

  plane->model = "BO747";
  plane->rows = 20;
  plane->left = 3;
  plane->middle = 4;
  plane->right = 3;

  return plane;

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

  newReservation->flightCode = malloc(10 * sizeof(char));
  strcpy(newReservation->flightCode, flight->flightCode);
  newReservation->seatNumber = malloc(10 * sizeof(char));
  strcpy(newReservation->seatNumber , seat);
  newReservation->userName = "default";

  result = askForInfo(INSERT_RESERVATION , newReservation);

  free(newReservation);

  printf("result es %s\n",result );

  if(strcmp(result , OKEY) == 0)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

int cancel(tFlight * flight , char * seat){
  tReservation * newReservation = malloc(sizeof(*newReservation));
  char * result;

  newReservation->flightCode = malloc(10 * sizeof(char));
  strcpy(newReservation->flightCode, flight->flightCode);
  newReservation->seatNumber = malloc(10 * sizeof(char));
  strcpy(newReservation->seatNumber , seat);
  newReservation->userName = "default";

  result = askForInfo(INSERT_CANCELLATION, newReservation);

  free(newReservation);

  if(strcmp(result , OKEY) == 0)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

int addFlightClient(char * origin ,char *   destination ,char *  departureTime ,char * arrivalTime ,char *  planeCode,char *  departureDate ,char *  arrivalDate)
{
  return 1;
}
int removeFlightClient(char * flightCode)
{
  return 1;
}


   