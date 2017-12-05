//freeMemory.c
#include "freeMemory.h"

void freeAllDrawPlane(int *** totalOccupiedP , tPlane ** planeP , char *** occupiedSeatsP )
{
	int j;

	int ** totalOccupied = *totalOccupiedP;
	tPlane * plane = *planeP;
	char ** occupiedSeats = *occupiedSeatsP;
	
	for( j = 0 ; j < plane->rows ; j++)
	{
		free(totalOccupied[j]);
		totalOccupied[j] = NULL;
	}

	free(totalOccupied);
	free(occupiedSeats);
	free(plane);


}

void freeFlightsArray( tFlight ** flights)
{
	int h = 0 ;

	while(flights[h] != NULL)
	{
		free(flights[h]);
		h++;
	}

	free(flights[h]);

	free(flights);
}
