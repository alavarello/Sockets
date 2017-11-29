#include <stdio.h>
#include <ctype.h>
#include "getnum.h"
#include <stdlib.h>
#include "random.h"
#include <string.h>
#include "terminal.h"
#include "terminalTest.h"
#include <stdlib.h>

#define MAX_FLIGHTS 50

static tFlight * currentFlight ;

int validateFormat(char entrada[]); //no se usa
void drawPlane();
char * * getOccupiedSeats(tFlight * currentFlight);
char * receiveSeatNumber();
void yesNo2 (char *respuesta); //no se usa
void printMenu (void);
void printClientMenu (void);
void printAdministratorMenu (void);
char * readFlightCode();
void displayFlights(tFlight ** flights);
int setCurrentFlight(tFlight ** flights , char * flightCode);
void readClientMenu ();
void readAdministratorMenu ();
void readMenu ();
void entrada(char entrada[]);//no se usa
int validateCommand(char * entrada );//no se usa
int leeEntrada(char entrada[]);//no se usa
void printRow(int n , int * occupied);
void printHeaders(tPlane * plane);
int getNumber(char * seat);
int getColumn(char * seat);
void fillOcuppiedMatrix(char * * occupiedSeats , int * * totalOccupied);
void updateOccupiedArrays(tPlane * plane , int row , int  ** totalOccupied , int * *left, int ** middle, int ** right);

int main(void)
{
	printMenu();
	readMenu();
	return 0;
}


void yesNo2 (char *respuesta)
{
	char enter;
	int ret;
	int estado;
	do
	{
		printf("Ingrese S/N \n");
		ret=scanf("%c%c",respuesta, &enter );
		estado=(enter!='\n'|| ret!=2 || (((*respuesta)!='s') && ((*respuesta)!='S') && ((*respuesta)!='n') && ((*respuesta)!='N')));
		/* Verifica que scanf haya recibido exactamente el formato de respuesta esperado */
	
			if(estado==1)
			{
				printf("Ingreso inválido\n");
				CLEAN_BUFFER;
			}
	}
	while(estado==1);
}

void printMenu (void)
{
	printf("Welcome:\n");
	printf("1. Client\n");
	printf("2. Administrator\n");
	printf("3. Finish\n\n");
}

void printClientMenu (void)
{
	printf("Choose your action:\n");
	printf("1. Reserve\n");
	printf("2. List available flights\n");
	printf("3. Cancel a seat\n\n");
	printf("4. Finish\n\n");
}
void printAdministratorMenu (void)
{
	printf("Choose your action:\n");
	printf("1. Add a flight\n");
	printf("2. Remove a flight\n");
	printf("3. Finish\n\n");
}

char * readFlightCode(){

	char * s = malloc(MAX_BUFFER * sizeof(*s));
	int c;
	int i = 0 ;
	int error = 1;

	while(error)
	{
		i=0;

		while((c = getchar()) != '\n'  && i < MAX_BUFFER){
				s[i] = c ; 
				i ++ ;

		}

		if( i >= MAX_BUFFER){
			printf("Please insert a valid flight code \n");
			CLEAN_BUFFER;
			error = 1;
		}else{
			error = 0;
		}
	}

	s[i] = 0;

	printf("Su numero es : %s\n", s ); 

	return s;

}

void displayFlights(tFlight ** flights)
{
	char * flightCode ;
	char * origin;
	char * destination;
	char *  departureTime ; 
	char * arrivalTime;
	char * planeCode;
	char *  departureDate; 
	char * arrivalDate;
	int i = 0;
	printf("The current available flights are : \n\n" );
	printf("%15s | %15s | %15s | %15s | %15s | %15s | %15s | %15s \n" , "Flight Code" , "Origin" , "Destination", "Departure Time" , "Arrival Time", "Departure Date" , "Arrival  Date" , "Plane Code");
	while(flights[i] != NULL){
		flightCode = (flights[i]->flightCode != NULL )? flights[i]->flightCode : "N/D";
		origin = (flights[i]->origin != NULL )? flights[i]->origin : "N/D";
		destination = (flights[i]->destination != NULL )? flights[i]->destination : "N/D";
		departureTime = (flights[i]->departureTime != NULL )? flights[i]->departureTime : "N/D";
		arrivalTime = (flights[i]->arrivalTime != NULL )? flights[i]->arrivalTime : "N/D";
		planeCode = (flights[i]->planeCode != NULL )? flights[i]->planeCode : "N/D";
		departureDate = (flights[i]->departureDate != NULL )? flights[i]->departureDate : "N/D";
		arrivalDate = (flights[i]->arrivalDate != NULL )? flights[i]->arrivalDate : "N/D";

		printf("%15s | %15s | %15s | %15s | %15s | %15s | %15s | %15s \n" , flightCode , origin, destination, departureTime , arrivalTime, departureDate , arrivalDate , planeCode);

		i++;
	
	}


}

int setCurrentFlight(tFlight ** flights , char * flightCode){

	int i = 0 ;

	while(flights[i]!= NULL && i < MAX_FLIGHTS){
		if(strcmp(flights[i]->flightCode, flightCode) == 0){
			currentFlight = flights[i];
			return  1;
		}
		i++;
	}
	printf("ERROR AL CURRENT FLIGHT\n");
	return 0;
}

void readClientMenu ()
{
	int sel;
	int error=1;
	int ret=0;
	char nombrearch[MAX_BUFFER]; 
	tFlight ** flights;
	char * flightCode ;
	char * seat;
	int result ; 
	int first = 1;

	do
	{
		if(first){
			sel=getint("\n\nChoose your option:\n");
		}
		switch(sel)
		{
			case 1:
			{
				flights = getFlights();
				displayFlights(flights);
				printf("Please enter the flight code\n");
				flightCode = readFlightCode();
				result = setCurrentFlight(flights , flightCode);
				if(!result){
					printf("Please insert a valid flight code\n");
					sel = 1;
					first = 0;
					error = 1;
					break;
				}
				drawPlane();
				seat = receiveSeatNumber();
				//cancelSeat(seat);
				printf("Reserving seat %s\n" , seat);
				error=0;
				break;
			}
			
			case 2:
			{
				printf("Listing flights\n");
				flights = getFlights();
				displayFlights(flights);
				error=0;
				break;
			}

			case 3:
			{
				flights = getFlights();
				displayFlights(flights);
				printf("Please enter the flight code\n");
				flightCode = readFlightCode();
				result = setCurrentFlight(flights , flightCode);
				if(!result){
					printf("Please insert a valid flight code\n");
					sel = 3;
					first = 0;
					error = 1;
					break;
				}
				drawPlane();
				seat = receiveSeatNumber();
				//cancelSeat(seat);
				//setCurrentFlight(flights , flightCode)
				printf("Canceling seat %s\n" , seat);
				error=0;
				break;
			}	
			
			case 4:
			{
				return;
				break;
			}		
			
			default:
			{
				printf("That option is not valid");
				first = 1;
				error=1;
			}
		}
	}
	while (error);
}

void readAdministratorMenu ()
{
	int sel;
	int error=1;
	int ret=0;
	char nombrearch[MAX_BUFFER]; 

	do
	{
		sel=getint("Choose your option:\n");
		switch(sel)
		{
			case 1:
			{
				printf("Adding a flight\n");
				//printClientMenu();
				error=0;
				break;
			}
			
			case 2:
			{
				printf("Removing a flight\n");
				//validatePassword();
				//printAdministratorMenu();
				error=0;
				break;
			}
			
			case 3:
			{
				return;
				break;
			}		
			
			default:
			{
				printf("That option is not valid");
				error=1;
			}
		}
	}
	while (error);
}


void readMenu ()
{
	int sel;
	int error=1;
	int ret=0;
	char nombrearch[MAX_BUFFER]; 

	do
	{
		sel=getint("Choose your option:\n");
		switch(sel)
		{
			case 1:
			{
				printf("You are the client\n");
				printClientMenu();
				readClientMenu();
				error=0;
				break;
			}
			
			case 2:
			{
				printf("You are the administrator\n");
				//validatePassword();
				printAdministratorMenu();
				readAdministratorMenu();
				error=0;
				break;
			}
			
			case 3:
			{
				return;
				break;
			}
			
			default:
			{
				printf("That option is not valid \n");
				error=1;
			}
		}
	}
	while (error);
}


int pideCom(tjugada * jugada, tdim * dim)
{
	char ent[MAX_BUFFER];
	int estado;

	do
	{
		entrada(ent);
		estado=validateCommand(ent);
	}
	
	while(estado == ERROR);

return estado;
}

void entrada(char entrada[])
{
	int estado=OK;
	do
	{
		printf("Ingrese un comando:\n");
		estado=leeEntrada(entrada);

		if(estado==ERROR)
		{
			printf("Excedio la capacidad de lectura\n");
		}
	}

	while(estado == ERROR);

}

int validateCommand(char * entrada )
{
	int estado=OK;
	int ret;
	int valida=validateFormat(entrada);

	if(valida==ERROR)
	{
		printf("Comando no valido\n");
		estado=ERROR;
	}
	else if(valida==QUIT)
	{
		estado=QUIT;
	}

return estado;
}

int leeEntrada(char entrada[])
{
	int estado=OK, c, i=0;
	
	while((c=getchar())!='\n')
	{

		if(i<MAX_BUFFER-1)
		{
			entrada[i++]=c;
		}
		else
		{
			estado=ERROR;
		}

	}
	entrada[i]=0;

return estado;

}

void printRow(int n , int * occupied){
	for(int i = 0 ; i < n; i++){
		if(occupied[i]){
			printf(" %c |", 'X' );
		}else{
		printf(" %c |", 'O' );
		}
	}
}

void printHeaders(tPlane * plane)
{
	char c = 'A';

	printf(" %3s  |" , "n");

	for(int j = 0 ; j < plane->left; j++){
		printf(" %c |", c);
		c++;
	}
	putchar(' ');
	putchar(' ');
	putchar('|');
	for(int j = 0 ; j < plane->middle  ; j++){
		printf(" %c |", c);
		c++;
	}
	putchar(' ');
	putchar(' ');
	putchar('|');
	for(int j = 0 ; j < plane->right ; j++){
		printf(" %c |", c);
		c++;
	}
	putchar('\n');

}

int getNumber(char * seat){

	return 1;

}

int getColumn(char * seat){

	return 0;

}

void fillOcuppiedMatrix(char * * occupiedSeats , int * * totalOccupied)
{
	int i = 0;
	int number;
	int column;

	while(occupiedSeats[i] != NULL)
	{
		number = getNumber(occupiedSeats[i]);  
		column = getColumn(occupiedSeats[i]);

		totalOccupied[number-1][column] = 1;

		i++;
	}


}

void updateOccupiedArrays(tPlane * plane , int row , int  ** totalOccupied , int * *left, int ** middle, int ** right)
{
	*left = totalOccupied[row] + 0;
	*middle = totalOccupied[row] + plane->left;
	*right = totalOccupied[row] + plane->middle;


}




void drawPlane()
{

	tPlane * plane = getPlane(currentFlight);

	int i = 0;

	char * * occupiedSeats = getOccupiedSeats(currentFlight);

	

	int j = 0;

	int * * totalOccupied = malloc(plane->rows* sizeof(*totalOccupied));
	for( j = 0 ; j < plane->rows ; j++){
		totalOccupied[j] = calloc((plane->left + plane->right + plane->middle) , sizeof(*totalOccupied[j]));
	}
	fillOcuppiedMatrix(occupiedSeats , totalOccupied);


	printHeaders(plane);
	putchar('\n');

	char number[4];

	int * left = calloc(plane->left , sizeof(*left)  );
	int * middle = calloc(plane->middle , sizeof(*middle)  );
	int * right = calloc(plane->right , sizeof(*right) );

	for( i = 0 ; i < plane->rows ; i++){

		updateOccupiedArrays(plane, i , totalOccupied , &left, &middle, &right);

		printf(" %3d  |" , i + 1 );

		printRow( plane->left , left);
		putchar(' ');
		putchar(' ');
		putchar('|');
		printRow(plane->middle , middle);
		putchar(' ');
		putchar(' ');
		putchar('|');
		printRow(plane->right,right);
		putchar('\n');

	}

	putchar('\n');

}

char * receiveSeatNumber()
{
	char c;
	char empty;
	char digit1 , digit2;
	char letter;

	char * buffer = malloc(4 * sizeof(*buffer)) ;
	
	int i = 0 ;
	int result;

	int flag = 1;

	printf("Please insert your seat number. Example: '01A' \n");

	while(flag){

		i = 0 ;

		while((c = getchar()) != '\n' && i < 3){
			buffer[i] = c;
			i++;
		}
		if(c != '\n'){
			CLEAN_BUFFER;


			printf("You have entered an invalid seat. Please try  again \n");

		}else{

		/* char empty should be empty , result must be 3*/
		result = sscanf(buffer , "%c%c%c%c" , &digit1, &digit2 , &c , &empty);

		if(result != 3){

			flag = 1;

			printf("You have entered an invalid seat. Please try  again \n");

		}else{

			flag = 0;
		}
	}


	}

	buffer[3] = 0;

	return buffer ;
}


int validateFormat(char entrada[])
{
	char corchete;
	int sscanf_res;
	int estado=OK;
	char espacio;

	if(strcmp(entrada,"quit")==0)
	{
		estado=QUIT;
	}
	else
	{
		/*sscanf_res=sscanf(entrada,"[%d,%d][%d,%d%c%c",&(jugada->inicial.fil),&(jugada->inicial.col)
						,&(jugada->final.fil),&(jugada->final.col),&corchete,&espacio); 
		/* espacio no deberia tomar ningun valor, si lo hace es que el formato es invalido*/

		/*if(sscanf_res!=5 || corchete!=']') 
		{	
			estado=ERROR;

		}
		*/
	}
return estado;
}