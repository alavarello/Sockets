#ifndef FRONT_END_H
#define FRONT_END_H

#include <stdio.h>
#include <ctype.h>
#include "getnum.h"
#include <stdlib.h>
#include "random.h"
#include <string.h>
#include <stdlib.h>
#include "Client.h"
#include "Controller.h"
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

#endif