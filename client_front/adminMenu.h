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
#include "Client.h"
#include "FrontEnd.h"
#include "structs.h"

#define RETURN_NULL_CONDITION(t) if(t == NULL) return 0
#define ERROR_MESSAGE_ADDING_FLIGHT "There has been a problem while adding the flight\n"
#define ERROR_MESSAGE_REMOVING_FLIGHT "There has been a problem while removing the flight\n"

int administratorSession();
void readAdministratorMenu ();
char * getFlightCode();
char * getOrigin();
char * getDestination();
char * getDepartureTime();
char * getArrivalTime();
char * getPlaneCode();
char * getDepartureDate();
char * getArrivalDate();

#endif