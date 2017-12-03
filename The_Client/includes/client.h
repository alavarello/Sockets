#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <ctype.h>
#include "getnum.h"
#include <stdlib.h>
#include "random.h"
#include <string.h>
#include <stdlib.h>
#include "frontEnd.h"
#include "controller.h"
#include "structs.h"

#define OKEY "OKEYY"

#define ERROR_RETURN(param) (strcmp(param , OKEY) == 0)?  1 :  0;

tFlight ** getFlights();
tPlane * getPlane();
char * * getOccupiedSeats(tFlight * flight);

int addFlightClient(char * flightCode,char * origin ,char *   destination ,char *  departureTime ,char * arrivalTime ,char *  planeCode,char *  departureDate ,char *  arrivalDate);
int removeFlightClient(char * flightCode);

int reserve(tFlight * flight , char * seat);
int cancel(tFlight * flight , char * seat);

#endif