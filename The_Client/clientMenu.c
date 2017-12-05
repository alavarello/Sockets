//clientMenu.c
#include "clientMenu.h"

static char msgLog[MAX_MSG_LOG];

int clientSession()
{
	readClientMenu();
	return 0;
}

void readClientMenu ()
{
	int sel;
	int flag=1;
	//char nombrearch[MAX_BUFFER];
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
				sprintf(msgLog , "That option is not valid");
				logError(msgLog);
				flag=1;
			}
		}

	}
	while (flag);


}

void listFlights()
{
	tFlight ** flights;
	sprintf(msgLog,"Listing flights\n");
	logMessage(msgLog);
	flights = getFlights();
	displayFlights(flights);
	freeFlightsArray(flights);
}

void reserveSeat()
{
	int flag = 1;
	tFlight ** flights;
	char * flightCode ;
	int result ;

	while(flag)
	{
		flights = getFlights();

		displayFlights(flights);

		flightCode = readFlightCode();

		if(strcmp(flightCode , "q") == 0)
		{
			freeFlightsArray(flights);
			free(flightCode);
			flights = NULL;
			return;
		}

		result = setCurrentFlight(flights , flightCode);

		freeFlightsArray(flights);
		free(flightCode);

		flights = NULL;

		if(!result)
		{
			sprintf(msgLog, "Please insert a valid flight code\n");
			logError(msgLog);
			flag = 1;
		}
		else
		{

			reserveSeatNumber();
			flag=1;
		}

	}

}

void cancelSeat()
{
	tFlight ** flights;
	char * flightCode;
	int result;
	int flag = 1;

	while(flag)
	{
		flights = getFlights();

		displayFlights(flights);

		flightCode = readFlightCode();

		if(strcmp(flightCode , "q") == 0)
		{
			freeFlightsArray(flights);
			free(flightCode);
			flights = NULL;
			return ;
		}

		result = setCurrentFlight(flights , flightCode);

		freeFlightsArray(flights);
		free(flightCode);

		flights = NULL;

		if(!result)
		{
			sprintf(msgLog,"Please insert a valid flight code\n");
			logError(msgLog);
			flag = 1;
			break;
		}
		else
		{
			cancelSeatNumber();
			flag=0;
		}
	}

}

