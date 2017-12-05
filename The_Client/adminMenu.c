//adminMenu.c

#include "adminMenu.h"

int administratorSession()
{
	readAdministratorMenu();

	return 0;
}

void readAdministratorMenu ()
{
	int sel;
	int error=1;
	int ret;
	tReservationArray * reservations;
	tReservationArray * cancelations;

	do
	{
		printAdministratorMenu();
		sel=getint("Choose your option:\n");
		switch(sel)
		{
			case 1:
			{
				logMessage("Adding a flight\n");
				ret = addFlight();

				if(ret == 0)
				{
					logError(ERROR_MESSAGE_ADDING_FLIGHT);
				}

				break;
			}
			
			case 2:
			{
				logMessage("Removing a flight\n");
				ret = removeFlight();

				if(ret == 0)
				{
					logError(ERROR_MESSAGE_REMOVING_FLIGHT);
				}

				break;
			}
			
			case 3:
			{
				reservations = getReservations();
				listReservations(reservations);
				freeReservationArray(&reservations);
				break;
			}
			case 4:
			{
				cancelations = getCancelations();
				listCancelations(cancelations);
				freeReservationArray(&cancelations);
				break;
			}
			case 5:
			{
				return;
				break;
			}		
			
			default:
			{
				logError("That option is not valid");
				error=1;
			}
		}

	}while (error);
}

int addFlight()
{
	char * flightCode = NULL;
	char * origin = NULL;
	char * destination = NULL;
	char * departureTime = NULL;
	char * arrivalTime = NULL;
	char * planeCode = NULL;
	char * departureDate = NULL;
	char * arrivalDate = NULL;

	flightCode = getFlightCode();

	RETURN_NULL_CONDITION(flightCode);

	origin = getOrigin();

	RETURN_NULL_CONDITION(origin);

	destination = getDestination(origin);

	RETURN_NULL_CONDITION(destination);

	departureDate = getDepartureDate();

	RETURN_NULL_CONDITION(departureDate);

	arrivalDate = getArrivalDate(departureDate);

	RETURN_NULL_CONDITION(arrivalDate);

	departureTime = getDepartureTime();

	RETURN_NULL_CONDITION(departureTime);

	arrivalTime = getArrivalTime(departureDate, arrivalDate, departureTime);

	RETURN_NULL_CONDITION(arrivalTime);

	planeCode = getPlaneCode();

	RETURN_NULL_CONDITION(planeCode);

	int res = addFlightClient(flightCode, origin , destination , departureTime ,arrivalTime , planeCode, departureDate , arrivalDate);

	FREE_ALL();
	
	return res;

}

int removeFlight()
{

	char * flightCode = getFlightCodeToRemove();  //por como lo hago, podriamos sacarlo desde aca

	if(flightCode == NULL)
	{
		return 1;
	}
	else
	{
		return removeFlightClient(flightCode);
	}

}

