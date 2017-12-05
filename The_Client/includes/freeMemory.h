//freeMemory.h

#ifndef FREE_MEMORY_H
#define FREE_MEMORY_H

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

void freeAllDrawPlane(int *** totalOccupiedP , tPlane ** planeP , char *** occupiedSeatsP );
void freeFlightsArray( tFlight ** flights);
void freeReservationArray(tReservationArray ** reservations);

#endif
