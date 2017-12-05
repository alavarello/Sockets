//flightInfo.h
#ifndef FLIGHT_INFO_H
#define FLIGHT_INFO_H

#include "adminMenu.h"

char * getFlightCode();
char * getFlightCodeToRemove();
char * getOrigin();
char * getDestination(char * origin);
char * getDepartureTime();
char * getArrivalTime(char * departureDate, char * arrivalDate, char * departureTime);
char * getPlaneCode();
char * getDepartureDate();
char * getArrivalDate(char * departureDate);



#endif
