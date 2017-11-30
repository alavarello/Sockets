#include "Controller.h"

static tFlight  currentFlight ;

static char msgLog[MAX_MSG_LOG];

int main(void)
{
	printMenu();
	readMenu();
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

void cancelSeatNumber()
{
	char * seat;
	int flag = 1;

	while(flag){

		drawPlane();

		seat = receiveSeatNumber();

		if(strcmp(seat , "q") == 0){
			return;
		}

		if(checkSeatNumberFormat(seat , currentFlight)){
			
			flag = cancel(currentFlight , seat ) ;

			if(flag){
				sprintf(msgLog, "Cancelling seat %s\n" , seat);
				logAction(msgLog);
				flag = 0;
			}else{
				sprintf(msgLog, "\nSeat %s is not able to cancel:\n\n" , seat);
				 logError(msgLog);
				flag = 1;
			}
		}else{
			sprintf(msgLog , "The seat format is invalid\n");
			logError(msgLog);
			flag = 1;
		}

		free(seat);


		
	}

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

		if(checkSeatNumberFormat(seat , currentFlight)){
			
			flag = reserve(currentFlight , seat ) ;

			if(flag){
				sprintf(msgLog, "Reserving seat %s\n" , seat);
				logAction(msgLog);
				flag = 0;
			}else{
				sprintf(msgLog, "\nSeat %s is no longer available, please choose another one:\n\n" , seat);
				logError(msgLog);
				flag = 1;
			}
		}else{
			sprintf(msgLog ,"The seat format is invalid\n");
			logError(msgLog);
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
			sprintf(msgLog, "Please insert a valid flight code\n");
			logError(msgLog);
			flag = 1;
		}else{

			reserveSeatNumber();
			flag=0;
		}

	}	

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
			sprintf(msgLog,"Please insert a valid flight code\n");
			logError(msgLog);
			flag = 1;
			break;
		}else{


			cancelSeatNumber();

			flag=0;
		}
	}

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

	for( j = 0 ; j < plane->rows ; j++){
		totalOccupied[j] = calloc((plane->left + plane->right + plane->middle) , sizeof(int));
	}

	fillOcuppiedMatrix(occupiedSeats , totalOccupied);

	drawPlaneFront(plane, totalOccupied );


	freeAllDrawPlane(&totalOccupied , &plane , &occupiedSeats);
	

}

