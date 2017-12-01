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
	while (flag );


}

void listFlights()
{
	tFlight ** flights;
	sprintf(msgLog,"Listing flights\n");
	logMessage(msgLog);
	flights = getFlights();
	displayFlights(flights);
}