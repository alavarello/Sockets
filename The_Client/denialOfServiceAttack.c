#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include "./includes/clientParser.h"



int process;


int initiateSocket(){

  printf("INITIATING\n");
  int clientSocket;
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
  return clientSocket;
}

void whileAttack(int action ){
	int bytes;
	int n;
	char  *buff, *pBuffer; 
	int clientSocket;
	while(1){
		clientSocket = initiateSocket();
		if(action == 2 || action == 9 || action == 11){
		char * flightCode = "AA954";
		buff = parseMessageToSend(action, flightCode, bytes);
		}
		else if(action == 3){
			tFlight * t = {"AA954", "EZE", "MIA", "00:30", "01/01/2017", "04:20", "02/01/2017", "Boeing 777"};
			buff = parseMessageToSend(action, t, bytes);
		}else if(action == 7 || action == 8 || action == 10 || action == 12){
			tReservation * r = {"AR136","01A", "John Doe"};
			buff = parseMessageToSend(action, r, bytes);
		}else {
			buff = parseMessageToSend(action, NULL, bytes);
		}
	
		buff = parseMessageToSend(action, NULL, bytes);
		n = write(clientSocket, parsedMessage, bytes);
		char * pBuffer = malloc(2000 * sizeof(char)); 
  		bzero(pBuffer,2000);
  		n = read(clientSocket, pBuffer, 2000);
  	}
}

void attack(int action){
	int bytes;
	int n;
	char  *buff, *pBuffer; 
	int clientSocket;

	clientSocket = initiateSocket();
	if(action == 2 || action == 9 || action == 11){
		char * flightCode = "AA954";
		buff = parseMessageToSend(action, flightCode, bytes);
	}
	else if(action == 3){
		tFlight * t = {"AA954", "EZE", "MIA", "00:30", "01/01/2017", "04:20", "02/01/2017", "Boeing 777"};
		buff = parseMessageToSend(action, t, bytes);
	}else if(action == 7 || action == 8 || action == 10 || action == 12){
		tReservation * r = {"AR136","01A", "John Doe"};
		buff = parseMessageToSend(action, r, bytes);
	}else {
		buff = parseMessageToSend(action, NULL, bytes);
	}
	
	n = write(clientSocket, parsedMessage, bytes);
	char * pBuffer = malloc(2000 * sizeof(char)); 
  	bzero(pBuffer,2000);
  	n = read(clientSocket, pBuffer, 2000);
  	free(pBuffer);
  	free(buff);
}

void writeWithoutReadAttack(){
	int bytes;
	int n;
	char  *buff, *pBuffer; 
	int clientSocket;

	clientSocket = initiateSocket();
	if(action == 2 || action == 9 || action == 11){
		char * flightCode = "AA954";
		buff = parseMessageToSend(action, flightCode, bytes);
	}
	else if(action == 3){
		tFlight * t = {"AA954", "EZE", "MIA", "00:30", "01/01/2017", "04:20", "02/01/2017", "Boeing 777"};
		buff = parseMessageToSend(action, t, bytes);
	}else if(action == 7 || action == 8 || action == 10 || action == 12){
		tReservation * r = {"AR136","01A", "John Doe"};
		buff = parseMessageToSend(action, r, bytes);
	}else {
		buff = parseMessageToSend(action, NULL, bytes);
	}
	
	n = write(clientSocket, parsedMessage, bytes);
}


void reproduce()
{	
	int i = 0;
	while(i<4000){
	/* Create child process */
      pid = fork();
      
      if (pid < 0) {
         perror("ERROR on fork");
         exit(1);
      }
      
      if (pid == 0) {
         /* This is the client process */
         attack(2);
      }
      i++;
	}
}


int main(void)
{
	reproduce();
}


