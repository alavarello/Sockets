/****************** SERVER CODE ****************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include "constants.h"
#include "structs.h"
#include "serialize_flight.h"
#include "flightsTableManager.h"
#include <sqlite3.h>

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
   n = read(sock,buffer,255);
   openDataBase();
  //tFlight t = {"AR304","EZE", "LIM", "19:00", "27/11/2017", "20:00", "27/11/2017", "Boeing 777"};
  //char * buff = serialize_flight(&t);
  tFlightArray * t = getFlightArray();
  int bytes = ( FLIGHT_CODE_CHAR_MAX + ORIGIN_CHAR_MAX + DESTINATION_CHAR_MAX + DEPARTURE_TIME_CHAR_MAX + DEPARTURE_DATE_CHAR_MAX +
  ARRIVAL_TIME_CHAR_MAX + ARRIVAL_DATE_CHAR_MAX + PLANE_CODE_CHAR_MAX )*sizeof(char);
  char * buff = serialize_flight_array(t);
  tFlightArray * r = deserialize_flight_array(buff);
  printFlightArray(*r);
   if (n < 0) {
      perror("ERROR reading from socket");
      exit(1);
   }
   
  printf("Here is the message: %s\n",buffer);
  n = write(sock,buff,(bytes*t->size)+sizeof(long));
   
   if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }
   
}

int main(){
  int welcomeSocket, newSocket, pid;
  char buffer[1024];
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;

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

  /*---- Bind the address struct to the socket ----*/
  bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

  /*---- Listen on the socket, with 5 max connection requests queued ----*/
  if(listen(welcomeSocket,5)==0)
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

