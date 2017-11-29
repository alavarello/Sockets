#include "Controller.h"

#define DO_ANOTHER_OPERATION 10
#define DONT_DO_ANOTHER_OPERATION -10



static tFlight  currentFlight ;

int main(void)
{
	printMenu();
	readMenu();
	return 0;
}

int setCurrentFlight(tFlight ** flights , char * flightCode){

	int i = 0 ;

	while(flights[i]!= NULL && i < MAX_FLIGHTS){

		if(strcmp(flights[i]->flightCode, flightCode) == 0){
			currentFlight = *flights[i];
			return  1;
		}
		i++;
	}
	return 0;
}

void freeFlightsArray( tFlight ** flights)
{
	int h = 0 ;

	while(flights[h] != NULL){
		free(flights[h]);
		h++;
	}

	free(flights[h]);

	free(flights);

}

int isNumber(char c)
{
	if( c <= '9' && c>= '0'){
		return 1;
	}

	return 0;
}

int isAlpha(char c)
{
	if( c <= 'Z' && c>= 'A'){
		return 1;
	}

	return 0;
}

int isValidSeatExpression(char * seat)
{	

	char c1 = seat[0];
	char c2 = seat[1];
	char c3 = seat[2];

	if(isNumber(c1) && isNumber(c2) && isAlpha(c3) && seat[3] == 0){
		return 1;
	}else{
		return 0;
	}

}

int checkSeatNumberFormat(char * seat)
{
	int row = getNumber(seat);
	int column = getColumn(seat);

	tPlane * plane = getPlane(currentFlight);

	if(row <= 0  || row >= plane->rows + 1){
		return 0;
	}

	if(column < 0 || column >= (plane->left + plane->middle + plane->right)){
		return 0;
	}

	return 1;



}

void reserveSeatNumber()
{
	char * seat;
	int flag = 1;

	while(flag){

		drawPlane();

		seat = receiveSeatNumber();

		if(strcmp(seat , "q") == 0){
			return;
		}

		if(checkSeatNumberFormat(seat)){
			
			flag = reserve(currentFlight , seat ) ;

			if(flag){
				printf("Reserving seat %s\n" , seat);
				flag = 0;
			}else{
				printf("\nSeat %s is no longer available, please choose another one:\n\n" , seat);
				flag = 1;
			}
		}else{
			printf("The seat format is invalid\n");
			flag = 1;
		}

		free(seat);


		
	}

}

int reserveSeat()
{
	int flag = 1;
	tFlight ** flights;
	char * flightCode ;
	int result ;

	
	while(flag){

		flights = getFlights();

		printf("DIO %p\n", flights);
		
		displayFlights(flights);

		flightCode = readFlightCode();

		if(strcmp(flightCode , "q") == 0){
			freeFlightsArray(flights);
			free(flightCode);
			flights = NULL;
			return 0 ;
		}

		result = setCurrentFlight(flights , flightCode);

		freeFlightsArray(flights);
		free(flightCode);

		flights = NULL;

		if(!result){
			printf("Please insert a valid flight code\n");
			flag = 1;
		}else{

			reserveSeatNumber();
			flag=0;
		}

	}	

}

void listFlights()
{
	tFlight ** flights;
	printf("Listing flights\n");
	flights = getFlights();
	displayFlights(flights);
}

void cancelSeat()
{
	tFlight ** flights;
	char * flightCode ;
	int result ;
	char * seat; 
	int flag = 1;

	while(flag){

		flights = getFlights();

		displayFlights(flights);

		flightCode = readFlightCode();

		if(strcmp(flightCode , "q") == 0){
			freeFlightsArray(flights);
			free(flightCode);
			flights = NULL;
			return ;
		}

		result = setCurrentFlight(flights , flightCode);

		freeFlightsArray(flights);
		free(flightCode);

		flights = NULL;

		if(!result){
			printf("Please insert a valid flight code\n");
			flag = 1;
			break;
		}else{


			//TODO

			drawPlane();

			seat = receiveSeatNumber();

			if(strcmp(seat , "q") == 0){
				free(seat);
				return;
			}

			printf("Canceling seat %s\n" , seat);

			free(seat);

			flag=0;
		}
	}

}

void readClientMenu ()
{
	int sel;
	int flag=1;
	char nombrearch[MAX_BUFFER]; 
	char * flightCode ;
	char * seat;
	int result; 
	do
	{
		printClientMenu();
		sel=getint("Choose your option:\n");
		switch(sel)
		{
			case 1:
			{
				reserveSeat();
				break;
			}
			
			case 2:
			{
				listFlights();
				break;
			}

			case 3:
			{
				cancelSeat();
				break;
			}	
			
			case 4:
			{
				flag = 0;
				break;
			}	
			
			default:
			{
				printf("That option is not valid");
				flag=1;
			}
		}

	}
	while (flag );


}

void readAdministratorMenu ()
{
	int sel;
	int error=1;
	int ret=0;
	char nombrearch[MAX_BUFFER]; 

	do
	{
		printAdministratorMenu();
		sel=getint("Choose your option:\n");
		switch(sel)
		{
			case 1:
			{
				printf("Adding a flight\n");
				error=0;
				break;
			}
			
			case 2:
			{
				printf("Removing a flight\n");
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

int clientSession()
{
	readClientMenu();

	return 0;
}

int administratorSession()
{
	readAdministratorMenu();

	return 0;
}


void readMenu ()
{
	int sel;
	int flag=1;
	int ret=0;
	char nombrearch[MAX_BUFFER]; 

	do
	{
		sel=getint("Choose your option:\n");
		switch(sel)
		{
			case 1:
			{
				flag = clientSession();
				break;
			}
			
			case 2:
			{
				flag = administratorSession();
				break;
			}
			
			case 3:
			{
				flag = 0;
				break;
			}
			
			default:
			{
				printf("That option is not valid \n");
				flag=1;
			}
		}
	}
	while (flag);
}

int getNumber(char * seat){

	char c1 = seat[0];
	char c2 = seat[1];

	int a = c1 - '0';
	int b = c2 - '0';

	return a*10 + b;

}

int getColumn(char * seat){

	char c3 = seat[2];

	return c3 - 'A';

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

		printf("Asiento %s : numero %d ,columna %c\n", occupiedSeats[i] , number , 'A' + column );

		totalOccupied[number-1][column] = 1;

		i++;
	}


}

void updateOccupiedArrays(tPlane * plane , int row , int  ** totalOccupied , int ** left, int ** middle, int ** right)
{
	*left = totalOccupied[row] + 0;
	*middle = totalOccupied[row] + plane->left;
	*right = totalOccupied[row] + plane->middle + plane->left;


}

void drawPlane()
{
	int j = 0;

	int i = 0;

	tPlane * plane = getPlane(&currentFlight);

	char * * occupiedSeats = getOccupiedSeats(&currentFlight);

	int * * totalOccupied = malloc(plane->rows* sizeof(*totalOccupied));

	printf("FREE BEFORe %p - %p - %p \n", totalOccupied , plane, occupiedSeats );

	for( j = 0 ; j < plane->rows ; j++){
		totalOccupied[j] = calloc((plane->left + plane->right + plane->middle) , sizeof(int));
	}

	printf("FREE BEFORE 2 %p - %p - %p \n", totalOccupied , plane, occupiedSeats );

	fillOcuppiedMatrix(occupiedSeats , totalOccupied);

	drawPlaneFront(plane, totalOccupied );


	freeAllDrawPlane(&totalOccupied , &plane , &occupiedSeats);

	

}

void freeAllDrawPlane(int *** totalOccupiedP , tPlane ** planeP , char *** occupiedSeatsP ){

	int j;

	int ** totalOccupied = *totalOccupiedP;
	tPlane * plane = *planeP;
	char ** occupiedSeats = *occupiedSeatsP;

	printf("FREE %p - %p - %p \n", totalOccupied , plane, occupiedSeats );
	
	for( j = 0 ; j < plane->rows ; j++){
		printf(" FOR %p \n", totalOccupied[j] );
		free(totalOccupied[j]);
		totalOccupied[j] = NULL;
	}

	free(totalOccupied);
	free(occupiedSeats);
	free(plane);


}