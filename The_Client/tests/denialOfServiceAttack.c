#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <structs.h>
#include "clientParser.h"
#include "random.h"
#include <unistd.h>
#include <assert.h>
#include <arpa/inet.h>




int process;


int initiateSocket()
{

  int clientSocket, n;
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
  
  n = connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);
 
  if(n < 0)
  {
  	printf("ERROR EN LA CONEXCION\n");
  	exit(0);
  }
  // add control if everything went fine
  return clientSocket;
}

//makes a request to the server and reads it
//This function intends to overload the server with work.
void attack(int action)
{
	int bytes;
	int n;
	char  *buff, *pBuffer, *flightCode; 
	int clientSocket;
	clientSocket = initiateSocket();
	if(action == 2 || action == 9 || action == 11)
	{
		flightCode = "AA954";
		buff = parseMessageToSend(action, flightCode, &bytes);
	}
	else if(action == 3)
	{
		tFlight t = {"AA954", "EZE", "MIA", "00:30", "01/01/2017", "04:20", "02/01/2017", "Boeing 777"};
		buff = parseMessageToSend(action, &t, &bytes);
	}
	else if(action == 7 || action == 8 || action == 10 || action == 12)
	{
		tReservation r = {"AR136","01A", "John Doe"};
		buff = parseMessageToSend(action, &r, &bytes);
	}
	else 
	{
		buff = parseMessageToSend(action, NULL, &bytes);
	}
	
	n = write(clientSocket, buff, bytes);

	if(n < 0)
	{
		printf("ERROR WITH PROCESS: %d WRITE WITHOUT READ ATTACK WITH ACTION: %d\n",process, action);
	}

	pBuffer = malloc(2000 * sizeof(char)); 
  	bzero(pBuffer,2000);
  	n = read(clientSocket, pBuffer, 2000);

  	if(n < 0)
  	{
		printf("ERROR WITH PROCESS: %d WRITE WITHOUT READ ATTACK WITH ACTION: %d\n",process, action);
	}

  	printf("PROCESS: %d ATTACK WITH ACTION: %d\n",process, action);
  	free(pBuffer);
  	free(buff);
}
//makes a request to the server without reading it. 
//The server should close the connection and the process created for this client after the time out define in it.
//This function intends to saturate the server. 
void writeWithoutReadAttack(int action)
{
	int bytes;
	int n;
	char  *buff; 
	int clientSocket;
	clientSocket = initiateSocket();
	if(action == 2 || action == 9 || action == 11)
	{
		char * flightCode = "AA954";
		buff = parseMessageToSend(action, flightCode, &bytes);
	}
	else if(action == 3)
	{
		tFlight t = {"AA954", "EZE", "MIA", "00:30", "01/01/2017", "04:20", "02/01/2017", "Boeing 777"};
		buff = parseMessageToSend(action, &t, &bytes);
	}
	else if(action == 7 || action == 8 || action == 10 || action == 12)
	{
		tReservation r = {"AR136","01A", "John Doe"};
		buff = parseMessageToSend(action, &r, &bytes);
	}
	else
	{
		buff = parseMessageToSend(action, NULL, &bytes);
	}
	n = write(clientSocket, buff, bytes);
	if(n < 0){
		printf("ERROR WITH PROCESS: %d WRITE WITHOUT READ ATTACK WITH ACTION: %d\n",process, action);
	}
	printf("PROCESS: %d WRITE WITHOUT READ ATTACK WITH ACTION: %d\n",process, action);
}


void reproduce()
{	
	int action, i = 0, pid;
	double rand;
	while(i<1000){
	/* Create child process */
      pid = fork();
      //the action for the parser to perform
      action = ((++process)%12)+1;
      rand = randNormalize();
      if (pid < 0) 
      {
         perror("ERROR on fork");
         exit(1);
      }
     
      if (pid == 0)
       {
      	if(rand < 0.75)
      	{	
         	attack(action);
      	}
      	else if(rand < 1)
      	{
      		writeWithoutReadAttack(action);
      	}
      	return;
      }
      i++;
	}
}


int main(void)
{
	reproduce();
	return 0;
}


