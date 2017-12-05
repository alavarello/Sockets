//flightInfo.c
#include "flightInfo.h"

char * getFlightCode()
{
	int flag = 1;
	tFlight ** flights;
	char * flightCode;
	int result;
	
	while(flag)
	{
		flights = getFlights();
		
		displayFlights(flights);

		flightCode = readFlightCode();

		if(strcmp(flightCode , "q") == 0)
		{
			freeFlightsArray(flights);
			free(flightCode);
			return NULL;
		}

		result = (isValidFlightAndPlaneCodeExpression(flightCode) && isntOnTheList(flightCode, flights)) ? 1 : 0;

		freeFlightsArray(flights);

		if(!result)
		{
			logError("Please insert a valid flight code\n");
			flag = 1;
		}
		else
		{
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

	while(flag)
	{
		flights = getFlights();
		
		displayFlights(flights);

		flightCode = readFlightCode();

		if(strcmp(flightCode , "q") == 0)
		{
			freeFlightsArray(flights);
			free(flightCode);
			return NULL;
		}

		result = (isValidFlightAndPlaneCodeExpression(flightCode) && isOnTheList(flightCode, flights)) ? 1 : 0;

		freeFlightsArray(flights);

		if(!result)
		{
			logError("Please insert a valid flight code\n");
			flag = 1;
		}
		else
		{
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

	
	while(flag)
	{

		origin = readOrigin();

		if(strcmp(origin , "q") == 0)
		{
			free(origin);
			return NULL;
		}

		result = isValidOriginDestination(origin);

		if(!result)
		{
			logError("Please insert a valid flight origin location\n");
			flag = 1;
		}
		else
		{
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

	
	while(flag)
	{

		destination = readDestination();

		if(strcmp(destination , "q") == 0)
		{
			free(destination);
			return NULL;
		}

		if(strcmp(destination,origin) == 0)
		{
			result = 0;
		}else{
			result = isValidOriginDestination(destination);
		}

		if(!result)
		{
			logError("Please insert a valid flight origin location\n");
			flag = 1;
		}
		else
		{
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

	
	while(flag)
	{

		depTime = readDepTime();

		if(strcmp(depTime , "q") == 0)
		{
			free(depTime);
			return NULL;
		}

		result = isValidTime(depTime);

		if(!result)
		{
			logError("Please insert a valid departure time\n");
			flag = 1;
		}
		else
		{
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

	
	while(flag)
	{

		arrTime = readArrTime();

		if(strcmp(arrTime , "q") == 0)
		{
			free(arrTime);
			return NULL;
		}

		result = isValidTime(arrTime) && checkLogicalTimeDifference(departureTime, arrTime, departureDate, arrivalDate);



		if(!result)
		{
			logError("Please insert a valid arrival time\n");
			flag = 1;
		}
		else
		{
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

	
	while(flag)
	{
		logMessage("Please choose one of the following plane codes:\n");
		planes = getPlanes();
		printPlanes(planes);
		

		planeCode = readPlaneCode();

		if(strcmp(planeCode , "q") == 0)
		{
			free(planeCode);
			return NULL;
		}

		result = isValidPlaneCodeExpression(planeCode , planes);

		if(!result)
		{
			logError("Please insert a valid plane code\n");
			flag = 1;
		}
		else
		{
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

	
	while(flag)
	{

		depDate = readDepDate();

		if(strcmp(depDate , "q") == 0)
		{
			free(depDate);
			return NULL;
		}

		result = isValidDate(depDate);

		if(!result)
		{
			logError("Please insert a valid departure date\n");
			flag = 1;
		}
		else
		{
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

	
	while(flag)
	{

		arrDate = readArrDate();

		if(strcmp(arrDate , "q") == 0)
		{
			free(arrDate);
			return NULL;
		}

		result = isValidDate(arrDate);

		if(dateDiff(arrDate, departureDate) < 0)
		{
			result = 0;
		}

		if(!result)
		{
			logError("Please insert a valid arrival date\n");
			flag = 1;
		}
		else
		{
			flag=0;
		}

	}

	return arrDate;

}
