//adminMenu.c

#include "adminMenu.h"


static char msgLog[MAX_MSG_LOG];

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

	char * flightCode = getFlightCodeToRemove(); //por como lo hago, podriamos sacarlo desde aca

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
	//char nombrearch[MAX_BUFFER]; 

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

int isntOnTheList(char * flightCode, tFlight ** flights){
	int i = 0 ;

	while(flights[i]!= NULL && i < MAX_FLIGHTS){

		if(strcmp(flights[i]->flightCode, flightCode) == 0){
			return 0;
		}
		i++;
	}
	return 1;
}

int isOnTheList(char * flightCode, tFlight ** flights){
	int i = 0 ;

	while(flights[i]!= NULL && i < MAX_FLIGHTS){

		if(strcmp(flights[i]->flightCode, flightCode) == 0){
			
			return 1;
		}
		i++;
	}
	return 0;
}

char * getFlightCode()
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
			return NULL;
		}

		result = (isValidFlightAndPlaneCodeExpression(flightCode) && isntOnTheList(flightCode, flights)) ? 1 : 0;

		freeFlightsArray(flights);

		if(!result){
			sprintf(msgLog, "Please insert a valid flight code\n");
			logError(msgLog);
			flag = 1;
		}else{

			flag=0;
		}

	}

	return flightCode;
}

char * getFlightCodeToRemove()
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
			return NULL;
		}

		result = (isValidFlightAndPlaneCodeExpression(flightCode) && isOnTheList(flightCode, flights)) ? 1 : 0;

		freeFlightsArray(flights);

		if(!result){
			sprintf(msgLog, "Please insert a valid flight code\n");
			logError(msgLog);
			flag = 1;
		}else{

			flag=0;
		}

	}

	return flightCode;
}

char * getOrigin()
{
	int flag = 1;
	int result ;
	char * origin;

	
	while(flag){

		origin = readOrigin();

		if(strcmp(origin , "q") == 0){
			free(origin);
			return NULL;
		}

		result = isValidOriginDestination(origin);

		if(!result){
			sprintf(msgLog, "Please insert a valid flight origin location\n");
			logError(msgLog);
			flag = 1;
		}else{
			flag=0;
		}

	}

	return origin;
}

char * getDestination(char * origin)
{
	int flag = 1;
	int result ;
	char * destination;

	
	while(flag){

		destination = readDestination();

		if(strcmp(destination , "q") == 0){
			free(destination);
			return NULL;
		}

		if(strcmp(destination,origin) == 0){
			result = 0;
		}else
			result = isValidOriginDestination(destination);

		if(!result){
			sprintf(msgLog, "Please insert a valid flight origin location\n");
			logError(msgLog);
			flag = 1;
		}else{
			flag=0;
		}

	}

	return destination;

}

char * getDepartureTime()
{
	int flag = 1;
	int result ;
	char * depTime;

	
	while(flag){

		depTime = readDepTime();

		if(strcmp(depTime , "q") == 0){
			free(depTime);
			return NULL;
		}

		result = isValidTime(depTime);

		if(!result){
			sprintf(msgLog, "Please insert a valid departure time\n");
			logError(msgLog);
			flag = 1;
		}else{
			flag=0;
		}

	}

	return depTime;
}

char * getArrivalTime(char * departureDate, char * arrivalDate, char * departureTime)
{
	int flag = 1;
	int result ;
	char * arrTime;

	
	while(flag){

		arrTime = readArrTime();

		if(strcmp(arrTime , "q") == 0){
			free(arrTime);
			return NULL;
		}

		result = isValidTime(arrTime) && checkLogicalTimeDifference(departureTime, arrTime, departureDate, arrivalDate);



		if(!result){
			sprintf(msgLog, "Please insert a valid arrival time\n");
			logError(msgLog);
			flag = 1;
		}else{
			flag=0;
		}

	}

	return arrTime;
}

char * getPlaneCode()
{
	int flag = 1;
	int result ;
	char * planeCode;
	tPlaneArray * planes;

	
	while(flag){

		sprintf(msgLog, "Please choose one of the following plane codes:\n");
		logMessage(msgLog);
		planes = getPlanes();
		printPlanes(planes);
		

		planeCode = readPlaneCode();

		if(strcmp(planeCode , "q") == 0){
			free(planeCode);
			return NULL;
		}

		result = isValidPlaneCodeExpression(planeCode , planes);

		if(!result){
			sprintf(msgLog, "Please insert a valid plane code\n");
			logError(msgLog);
			flag = 1;
		}else{
			flag=0;
		}

	}

	return planeCode;
}

char * getDepartureDate()
{
	int flag = 1;
	int result ;
	char * depDate;

	
	while(flag){

		depDate = readDepDate();

		if(strcmp(depDate , "q") == 0){
			free(depDate);
			return NULL;
		}

		result = isValidDate(depDate);

		if(!result){
			sprintf(msgLog, "Please insert a valid departure date\n");
			logError(msgLog);
			flag = 1;
		}else{
			flag=0;
		}

	}

	return depDate;
}

char * getArrivalDate(char * departureDate)
{
	int flag = 1;
	int result ;
	char * arrDate;

	
	while(flag){

		arrDate = readArrDate();

		if(strcmp(arrDate , "q") == 0){
			free(arrDate);
			return NULL;
		}

		result = isValidDate(arrDate);

		if(dateDiff(arrDate, departureDate) < 0)
			result = 0;

		if(!result){
			sprintf(msgLog, "Please insert a valid arrival date\n");
			logError(msgLog);
			flag = 1;
		}else{
			flag=0;
		}

	}

	return arrDate;

}