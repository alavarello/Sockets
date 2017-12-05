#include "frontEnd.h"

void printPlanes(tPlaneArray * planeArray)
{
	int i ; 

	tPlane ** planes = planeArray->planeArray;

	printf("%15s | %15s | %15s | %15s | %15s \n" , "Plane Code" , "Rows", "Left", "Middle" , "Right");

	for (i = 0 ; i < planeArray->size ; i++)
	{
		printf("%15s | %15d | %15d | %15d | %15d \n" , planes[i]->model , planes[i]->rows, planes[i]->left, planes[i]->middle, planes[i]->right);
	}

	putchar('\n');
}

void printMenu (void)
{
	printf("Welcome:\n\n");

	printf("1. Client\n");
	printf("2. Administrator\n");
	printf("3. Finish\n\n");
}

void printClientMenu (void)
{
	printf("\nWelcome to the client menu\n\n");

	printf("Choose your action:\n");
	printf("1. Reserve\n");
	printf("2. List available flights\n");
	printf("3. Cancel a seat\n");
	printf("4. Finish\n\n");
}
void printAdministratorMenu (void)
{
	printf("\nWelcome to the administrator menu\n\n");

	printf("Choose your action:\n");
	printf("1. Add a flight\n");
	printf("2. Remove a flight\n");
	printf("3. List reservations\n");
	printf("4. List cancelations\n");
	printf("5. Finish\n\n");
}

char * readFlightCode()
{
	char * s = malloc(MAX_BUFFER * sizeof(*s));
	int c;
	int i = 0 ;
	int error = 1;

	while(error)
	{
		i=0;

		printf("\nPlease insert the flight code:\n");

		while((c = getchar()) != '\n'  && i < MAX_BUFFER)
		{
				s[i] = c ; 
				i ++ ;
		}

		if( i >= MAX_BUFFER)
		{
			printf("Please insert a valid flight code \n");
			CLEAN_BUFFER;
			error = 1;
		}
		else
		{
			error = 0;
		}
	}

	s[i] = 0;

	return s;

}

char * readOrigin()
{
	char * s = malloc(MAX_BUFFER * sizeof(*s));
	int c;
	int i = 0 ;
	int error = 1;

	while(error)
	{
		i=0;

		printf("\nPlease insert the flight origin location:\n");

		while((c = getchar()) != '\n'  && i < MAX_BUFFER)
		{
				s[i] = c ; 
				i ++ ;

		}

		if( i >= MAX_BUFFER)
		{
			printf("Please insert a valid flight origin location \n");
			CLEAN_BUFFER;
			error = 1;
		}
		else
		{
			error = 0;
		}
	}

	s[i] = 0;

	return s;
}

char * readDestination()
{
	char * s = malloc(MAX_BUFFER * sizeof(*s));
	int c;
	int i = 0 ;
	int error = 1;

	while(error)
	{
		i=0;

		printf("\nPlease insert the flight destination:\n");

		while((c = getchar()) != '\n'  && i < MAX_BUFFER)
		{
				s[i] = c ; 
				i ++ ;
		}

		if( i >= MAX_BUFFER)
		{
			printf("Please insert a valid flight destination \n");
			CLEAN_BUFFER;
			error = 1;
		}
		else
		{
			error = 0;
		}
	}

	s[i] = 0;

	return s;
}

char * readDepTime()
{

	char * s = malloc(MAX_BUFFER * sizeof(*s));
	int c;
	int i = 0 ;
	int error = 1;

	while(error)
	{
		i=0;

		printf("\nPlease insert the departure time:\n");

		while((c = getchar()) != '\n'  && i < MAX_BUFFER)
		{
				s[i] = c ; 
				i ++ ;
		}

		if( i >= MAX_BUFFER)
		{
			printf("Please insert a valid departure time \n");
			CLEAN_BUFFER;
			error = 1;
		}
		else
		{
			error = 0;
		}
	}

	s[i] = 0;

	return s;
}

char * readArrTime()
{
	char * s = malloc(MAX_BUFFER * sizeof(*s));
	int c;
	int i = 0 ;
	int error = 1;

	while(error)
	{
		i=0;

		printf("\nPlease insert the arrival time:\n");

		while((c = getchar()) != '\n'  && i < MAX_BUFFER)
		{
				s[i] = c ; 
				i ++ ;
		}

		if( i >= MAX_BUFFER)
		{
			printf("Please insert a valid arrival time \n");
			CLEAN_BUFFER;
			error = 1;
		}
		else
		{
			error = 0;
		}
	}

	s[i] = 0;

	return s;
}

char * readPlaneCode()
{
	char * s = malloc(MAX_BUFFER * sizeof(*s));
	int c;
	int i = 0 ;
	int error = 1;

	while(error)
	{
		i=0;

		printf("\nPlease insert the plane code:\n");

		while((c = getchar()) != '\n'  && i < MAX_BUFFER)
		{
				s[i] = c ; 
				i ++ ;
		}

		if( i >= MAX_BUFFER)
		{
			printf("Please insert a valid plane code \n");
			CLEAN_BUFFER;
			error = 1;
		}
		else
		{
			error = 0;
		}
	}

	s[i] = 0;

	return s;
}

char * readDepDate()
{
	char * s = malloc(MAX_BUFFER * sizeof(*s));
	int c;
	int i = 0 ;
	int error = 1;

	while(error)
	{
		i=0;

		printf("\nPlease insert the departure date:\n");

		while((c = getchar()) != '\n'  && i < MAX_BUFFER)
		{
				s[i] = c ; 
				i ++ ;
		}

		if( i >= MAX_BUFFER)
		{
			printf("Please insert a valid departure date \n");
			CLEAN_BUFFER;
			error = 1;
		}
		else
		{
			error = 0;
		}
	}

	s[i] = 0;

	return s;
}

char * readArrDate()
{
	char * s = malloc(MAX_BUFFER * sizeof(*s));
	int c;
	int i = 0 ;
	int error = 1;

	while(error)
	{
		i=0;

		printf("\nPlease insert the arrival date:\n");

		while((c = getchar()) != '\n'  && i < MAX_BUFFER)
		{
				s[i] = c ; 
				i ++ ;
		}

		if( i >= MAX_BUFFER)
		{
			printf("Please insert a valid arrival date \n");
			CLEAN_BUFFER;
			error = 1;
		}
		else
		{
			error = 0;
		}
	}

	s[i] = 0;

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
	printf("\nThe current available flights are : \n\n" );
	printf("%15s | %15s | %15s | %15s | %15s | %15s | %15s | %15s \n" , "Flight Code" , "Origin" , "Destination", "Departure Time" , "Arrival Time", "Departure Date" , "Arrival  Date" , "Plane Code");
	while(flights[i] != NULL)
	{
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


void printRow(int n , int * occupied)
{
	for(int i = 0 ; i < n; i++)
	{
		if(occupied[i])
		{
			printf(" %c |", 'X' );
		}
		else
		{
			printf(" %c |", 'O' );
		}
	}
}

void printHeaders(tPlane * plane)
{
	char c = 'A';

	printf(" %3s  |" , "n");

	for(int j = 0 ; j < plane->left; j++)
	{
		printf(" %c |", c);
		c++;
	}
	putchar(' ');
	putchar(' ');
	putchar('|');
	for(int j = 0 ; j < plane->middle  ; j++)
	{
		printf(" %c |", c);
		c++;
	}
	putchar(' ');
	putchar(' ');
	putchar('|');
	for(int j = 0 ; j < plane->right ; j++)
	{
		printf(" %c |", c);
		c++;
	}
	putchar('\n');

}

void drawPlaneFront(tPlane * plane , int * * totalOccupied )
{
	int i;
	int * left;
	int * middle;
	int * right;

	printHeaders(plane);
	putchar('\n');

	for( i = 0 ; i < plane->rows ; i++)
	{
		updateOccupiedArrays(plane, i , totalOccupied , &left, &middle, &right);

		printf(" %3d  |" , i + 1 );

		printRow( plane->left, left);
		putchar(' ');
		putchar(' ');
		putchar('|');
		printRow(plane->middle, middle);
		putchar(' ');
		putchar(' ');
		putchar('|');
		printRow(plane->right, right);
		putchar('\n');

	}
	putchar('\n');

}

char * receiveSeatNumber()
{
	char c;
	char empty;
	char digit1 , digit2;

	char * buffer = malloc(4 * sizeof(*buffer));
	
	int i = 0 ;
	int result;

	int flag = 1;

	printf("Please insert your seat number. Example: '01A' \n");

	while(flag){

		i = 0 ;

		buffer[1] = 0;

		while((c = getchar()) != '\n' && i < 3)
		{
			buffer[i] = c;
			i++;
		}
		

		if(i == 1 && strcmp(buffer , "q") == 0)
		{
			free(buffer);
			return "q";
		}

		if(c != '\n' || i != 3)
		{
			if(c != '\n')
			{
				CLEAN_BUFFER;
			}	
			printf("You have entered an invalid seat. Please try  again  1\n");

		}
		else
		{
			buffer[3] = 0;
			result = sscanf(buffer , "%c%c%c%c" , &digit1, &digit2 , &c , &empty);

			if(result != 3)
			{
				flag = 1;
				printf("You have entered an invalid seat. Please try  again 2\n");
			}
			else
			{
				flag = 0;
			}
		}
	}

	buffer[3] = 0;
	
	return buffer ;
}

void logError(char * msg)
{
	printf("\nERROR: %s \n", msg );
}

void logAction(char * msg)
{
	printf("\nACTION: %s \n", msg );
}

void logMessage(char * msg)
{
	printf("%s\n",msg );
}

void listReservationsAndCancelations(tReservationArray * reservations)
{
	int i = 0 ;
	tReservation * aux; 

	printf("%15s | %15s | %15s \n" , "Flight Code" , "Seat Number" , "User Pid" );

	for (i = 0 ; i < reservations->size ; i++)
	{
		aux = reservations->reservationsArray[i];
		printf("%15s | %15s | %15s \n" , aux->flightCode , aux-> seatNumber , aux->userName );
	}
	putchar('\n');
}

void listReservations(tReservationArray * reservations)
{
	printf("These are all the reservations\n\n");
	listReservationsAndCancelations(reservations);
}

void listCancelations(tReservationArray * reservations)
{
	printf("These are all the cancellations\n\n");
	listReservationsAndCancelations(reservations);
}


