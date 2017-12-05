//adminMenu.h

#ifndef ADMIN_MENU_H
#define ADMIN_MENU_H

#include <stdio.h>
#include <ctype.h>
#include "getnum.h"
#include <stdlib.h>
#include "random.h"
#include <string.h>
#include <stdlib.h>
#include "client.h"
#include "frontEnd.h"
#include "structs.h"
#include "expressions.h"

#define FREE_ALL() free(flightCode); free(origin) ; free(destination); free(departureDate); free(departureTime); free(arrivalTime) ; free(planeCode); free(arrivalDate)
#define RETURN_NULL_CONDITION(t) if(t == NULL){ FREE_ALL() ;  return 0 ;}
#define ERROR_MESSAGE_ADDING_FLIGHT "There has been a problem while adding the flight\n"
#define ERROR_MESSAGE_REMOVING_FLIGHT "There has been a problem while removing the flight\n"

int addFlight();
int removeFlight();
int administratorSession();
void readAdministratorMenu ();
char * getFlightCode();
char * getFlightCodeToRemove();
char * getOrigin();
char * getDestination(char *);
char * getDepartureTime();
char * getArrivalTime(char * departureDate, char * arrivalDate, char * departureTime);
char * getPlaneCode();
char * getDepartureDate();
char * getArrivalDate(char *);

#endif
