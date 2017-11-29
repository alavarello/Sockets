#include "terminalTest.h"
#include <stdlib.h>

tFlight * * getFlights()
{
	tFlight * * flights = (tFlight **) malloc(20 * sizeof(*flights));

	for(int i = 0 ; i < 20 ; i++){
		flights[i] = (tFlight *) malloc(sizeof(**flights));
	}

	flights[0]->flightCode = "AA223";
	flights[0]->planeCode = "BO747";

	flights[1]->flightCode = "AA225";
	flights[1]->planeCode = "B0737";

	flights[2]->flightCode = "UA004";
	flights[2]->planeCode = "AB380";

	flights[3] = NULL;

	return flights;   
}

tPlane * getPlane(tFlight * flight)
{

	tPlane * plane = (tPlane * ) malloc(sizeof(tPlane));

	plane->model = "BO747";
	plane->rows = 20;
	plane->left = 2;
	plane->middle = 3;
	plane->right = 2;

	return plane;

}

char * * getOccupiedSeats(tFlight * flight)
{
	char ** seats = malloc(8 * sizeof(*seats));
	seats[0] = "01B";
	seats[1] = "10A";
	seats[2] = "13E";
	seats[3] = "13C";
	seats[4] = "17G";
	seats[5] = "18F";
	seats[6] = "19A";
	seats[7] = NULL;

	return seats;
}
