#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <ctype.h>
#include "getnum.h"
#include <stdlib.h>
#include "random.h"
#include <string.h>
#include <stdlib.h>
#include "FrontEnd.h"
#include "Controller.h"
#include "structs.h"



tFlight ** getFlights();
tPlane * getPlane();
char * * getOccupiedSeats(tFlight * flight);

#endif