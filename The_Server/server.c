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
#include <unistd.h>

#define MAX_NUMBER_OF_CLIENTS 100

 void openDataBase();
 void closeDataBase();
 void enableFK();

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
      enableFK();
   }
 }

 void enableFK()
 {
   char * sql = "PRAGMA foreign_keys = ON;";
   sqlite3_stmt * res;
   int rc;

   rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
   if(rc != SQLITE_OK)
   {
      fprintf(stderr, "Can't enable Foreign Key support: %s\n", sqlite3_errmsg(db));
      return;
   }
   rc = sqlite3_step(res);

    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Can't enable Foreign Key support: %s\n", sqlite3_errmsg(db));

    }

    sqlite3_finalize(res);
 }

void closeDataBase(){
  sqlite3_close(db);
   printf("Close database successfully\n");
 }

void childForClient (int sock) {
   int n, bytes;
   char buffer[256];

   char * resBuffer;
  openDataBase();

   while(1)
   {

  bzero(buffer,256);
   n = read(sock,buffer,255);

   resBuffer = parseAndExecute(buffer, &bytes);

   if (n < 0) {
      perror("ERROR reading from socket");
      exit(1);
   }
   printf("%d\n",bytes );
  n = write(sock,resBuffer,bytes);

   if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }
 }

}

int main(){
  int welcomeSocket, newSocket, pid, ret, enable = 1;
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;
   struct timeval tv;

  openDataBase();
do{

  /*---- Create the socket. The three arguments are: ----*/
  /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
  welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);

  if (setsockopt(welcomeSocket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
  {
    printf("setsockopt(SO_REUSEADDR) failed");

  }


  /*---- Configure settings of the server address struct ----*/
  /* Address family = Internet */
  serverAddr.sin_family = AF_INET;
  /* Set port number, using htons function to use proper byte order */
  serverAddr.sin_port = htons(5002);
  /* Set IP address to localhost */
  serverAddr.sin_addr.s_addr = inet_addr("10.2.69.99");//this address is for local conection
  /* Set all bits of the padding field to 0 */
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

  //putting a timeout interval for the input using the write and read
  tv.tv_sec = 60 * 5 ;        // 30 Secs Timeout
  tv.tv_usec = 0;        // Not init'ing this can cause strange errors

  /*---- Bind the address struct to the socket ----*/
    ret = bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
    sleep(2);
  } while(ret == -1);





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
