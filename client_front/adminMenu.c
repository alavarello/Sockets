//adminMenu.c

#include "adminMenu.h"

int addFlight()
{
	char * flightCode;
	char * origin;
	char * destination;
	char * departureTime;
	char * arrivalTime;
	char * planeCode;
	char * departureDate;
	char * arrivalDate;

	flightCode = getFlightCode();
	
	RETURN_NULL_CONDITION(flightCode);

	origin = getOrigin();

	RETURN_NULL_CONDITION(origin);

	destination = getDestination();

	RETURN_NULL_CONDITION(destination);

	departureTime = getDepartureTime();

	RETURN_NULL_CONDITION(departureTime);

	arrivalTime = getArrivalTime();

	RETURN_NULL_CONDITION(arrivalTime);

	planeCode = getPlaneCode();

	RETURN_NULL_CONDITION(planeCode);

	departureDate = getDepartureDate();

	RETURN_NULL_CONDITION(departureDate);

	arrivalDate = getArrivalDate();

	RETURN_NULL_CONDITION(arrivalDate);

	return addFlightClient(origin , destination , departureTime ,arrivalTime , planeCode, departureDate , arrivalDate);

}

int removeFlight()
{

	char * flightCode;

	flightCode = getFlightCode();

	return removeFlightClient(flightCode);

}

int administratorSession()
{
	readAdministratorMenu();

	return 0;
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
				logMessage("Adding a flight\n");
				int ret = addFlight();
				if(ret == 0){
					logError(ERROR_MESSAGE_ADDING_FLIGHT);
				}

				break;
			}
			
			case 2:
			{
				printf("Removing a flight\n");
				int ret = removeFlight();

				if(ret == 0){
					logError(ERROR_MESSAGE_REMOVING_FLIGHT);
				}

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

char * getFlightCode()
{
	return "AA987";
}
char * getOrigin()
{
	return "AEP";
}
char * getDestination()
{
	return "EZE";
}
char * getDepartureTime()
{
	return "22:00";
}
char * getArrivalTime()
{
	return "08:00";
}
char * getPlaneCode()
{
	return "BO747";
}
char * getDepartureDate()
{
	return "04/06/2017";
}
char * getArrivalDate()
{
	return "05/06/2017";

}