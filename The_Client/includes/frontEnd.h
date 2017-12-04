#ifndef FRONT_END_H
#define FRONT_END_H

#include <stdio.h>
#include <ctype.h>
#include "getnum.h"
#include <stdlib.h>
#include "random.h"
#include <string.h>
#include <stdlib.h>
#include "client.h"
#include "controller.h"
#include "structs.h"

void drawPlaneFront(tPlane * plane , int * * totalOccupied  );
char * receiveSeatNumber();
void printMenu (void);
void printClientMenu (void);
void printAdministratorMenu (void);
char * readFlightCode();
void displayFlights(tFlight ** flights);
void printRow(int n , int * occupied);
void printHeaders(tPlane * plane);
char * readOrigin();
char * readDestination();
char * readDepTime();
char * readArrTime();
char * readPlaneCode();
char * readDepDate();
char * readArrDate();

void listReservationsAndCancelations(tReservationArray * reservations);
void listReservations(tReservationArray * reservations);
void listCancelations(tReservationArray * reservations);

/*error logs*/

void logError(char * msg);
void logAction(char * msg);
void logMessage(char * msg);


#endif