/****************** SERVER CODE ****************/

#include <stdio.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <string.h>
#include "constants.h"
#include "structs.h"
#include "serialize_flight.h"
#include "serialize_plane.h"
#include "serialize_reservation.h"
#include "flightsTableManager.h"
#include "planesTableManager.h"
#include "reservationAndCancelationManager.h"
#include "serverParser.h"
#include <sqlite3.h>

#define MAX_NUMBER_OF_CLIENTS 100

 void openDataBase();
 void closeDataBase();

//gcc serialize_flight.c server.c flightsTableManager.c reservationAndCancelationManager.c planesTableManager.c serialize_reservation.c serialize_plane.c serverParser.c semaphores.c -o server -lsqlite3


 sqlite3 *db;

 void openDataBase(){
  int rc;
    /* Open database */
   rc = sqlite3_open("flightsDataBase.db", &db);
   
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
   } else {
      fprintf(stdout, "Opened database successfully\n");
   }
 }

void closeDataBase(){
  sqlite3_close(db);
   printf("Close database successfully\n");
 }

void childForClient (int sock) {
   int n;
   char buffer[256];
   bzero(buffer,256);
   char * resBuffer;

   while(1)
   {
   n = read(sock,buffer,255);
   openDataBase();
   resBuffer = parseAndExecute(buffer);

   if (n < 0) {
      perror("ERROR reading from socket");
      exit(1);
   }
   
  n = write(sock,resBuffer,500);
   
   if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }
 }
   
}

int main(){
  int welcomeSocket, newSocket, pid;
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;
   struct timeval tv;

  openDataBase();
  
  /*---- Create the socket. The three arguments are: ----*/
  /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
  welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);
  
  /*---- Configure settings of the server address struct ----*/
  /* Address family = Internet */
  serverAddr.sin_family = AF_INET;
  /* Set port number, using htons function to use proper byte order */
  serverAddr.sin_port = htons(5002);
  /* Set IP address to localhost */
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");//this address is for local conection
  /* Set all bits of the padding field to 0 */
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  //putting a timeout interval for the input using the write and read
  tv.tv_sec = 30;        // 30 Secs Timeout
  tv.tv_usec = 0;        // Not init'ing this can cause strange errors
  /*---- Bind the address struct to the socket ----*/
  bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));


  setsockopt(welcomeSocket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv,sizeof(struct timeval));
  /*---- Listen on the socket, with 5 max connection requests queued ----*/
  if(listen(welcomeSocket,MAX_NUMBER_OF_CLIENTS)==0)
    printf("Listening\n");
  else
    printf("Error\n");

  /*---- Accept call creates a new socket for the incoming connection ----*/
  addr_size = sizeof serverStorage;

  while(1){
   newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);

  if(newSocket < 0){
   printf("ERROR in getting the new socket\n");
  }else{


      /* Create child process */
      pid = fork();
      
      if (pid < 0) {
         perror("ERROR on fork");
         exit(1);
      }
      
      if (pid == 0) {
         /* This is the client process */
          printf("AGARRO LA CONEXCION\n");
         close(welcomeSocket);
         childForClient(newSocket);
         exit(0);
      }
      else {
         close(newSocket);
      }
  }
  /*---- Send message to the socket of the incoming connection ----*/
  }
  
  closeDataBase();
   printf("Close database successfully\n");
  return 0;
}



