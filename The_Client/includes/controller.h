#ifndef CONTROLLER_H
#define CONTROLLER_H

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
#include "clientMenu.h"
#include "adminMenu.h"
#include <sqlite3.h>
#include <unistd.h>

#define DO_ANOTHER_OPERATION 10
#define DONT_DO_ANOTHER_OPERATION -10
#define MAX_MSG_LOG 100
#define MAX_ATTEMPTS 10

int setCurrentFlight(tFlight ** flights , char * flightCode);

void readClientMenu ();

void readAdministratorMenu ();

void readMenu ();

void fillOcuppiedMatrix(char * * occupiedSeats , int * * totalOccupied);

void updateOccupiedArrays(tPlane * plane , int row , int  ** totalOccupied , int * *left, int ** middle, int ** right);

void drawPlane();

void freeAllDrawPlane(int *** totalOccupied , tPlane ** plane , char *** occupiedSeats );

void freeFlightsArray( tFlight ** flights);

void cancelSeatNumber();

void reserveSeatNumber();

#endif