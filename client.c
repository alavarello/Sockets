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

//gcc client.c serialize_reservation.c serialize_plane.c serialize_flight.c -o client -lsqlite3 -std=c99



int main(){
  int clientSocket, n;
  char buffer[2048];
  char * resBuff;
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
   int action = (int)((*buffer)-'0');
   char * res;
   if(action == 2 || action == 9){
       res = "AA954";
       resBuff = parseMessageToSend(action, res);
   }
   else if(action == 3){
      tFlight t = {"ZD136","EZE", "LIM", "19:00", "27/11/2017", "20:00", "27/11/2017", "Boeing 777"};
      resBuff = parseMessageToSend(action, &t);
   }
   else if(action == 7 || action == 8){
    tReservation r = {"ZD136","01A", "John"};
    resBuff = parseMessageToSend(action, &r);
   }
   else{
    resBuff = parseMessageToSend(action, NULL);
   }
   
   n = write(clientSocket, resBuff, 200);
   if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }
   
   /* Now read server response */
   bzero(buffer,2000);
   n = read(clientSocket, buffer, 2000);
   if (n < 0) {
      perror("ERROR reading from socket");
      exit(1);
   }
  parseRecivedMessage(action, buffer);
   return 0;
}