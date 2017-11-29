/****************** CLIENT CODE ****************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include "structs.h"
#include "serialize_flight.h"
#include "serialize_plane.h"
#include "serialize_reservation.h"

//gcc client.c serialize_reservation.c serialize_plane.c serialize_flight.c -o client -lsqlite3 -std=c99

void printSeatsArray(tSeatsArray seatsArray){
  int i;
  printf("SEATS ARRAY: SIZE:%d\n",seatsArray.size);
  for (i = 0; i < seatsArray.size; ++i)
  {
   printf("SEAT:%s\n",seatsArray.reservedSeats[i]);
  }
}

int main(){
  int clientSocket, n;
  char buffer[2048];
  struct sockaddr_in serverAddr;
  socklen_t addr_size;


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
  connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

   /* Now ask for a message from the user, this message
      * will be read by server
   */
   
   printf("Please enter the message: ");
   bzero(buffer,256);
   fgets(buffer,255,stdin);
   
   /* Send message to the server */
   n = write(clientSocket, buffer, strlen(buffer));
   
   if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }
   
   /* Now read server response */
   bzero(buffer,2000);
   n = read(clientSocket, buffer, 2000);
   tSeatsArray * t = deserialize_seatArray(buffer);
   if (n < 0) {
      perror("ERROR reading from socket");
      exit(1);
   }
   printSeatsArray(*t);
   //printf("FC:%s. O:%s.  D:%s.   DT:%s.   DD:%s.   AT:%s.  AD:%s.   PC:%s \n",t->flightCode, t->origin, t->destination, t->departureTime, t->departureDate, t->arrivalTime, t->arrivalDate, t->planeCode);
   return 0;
}