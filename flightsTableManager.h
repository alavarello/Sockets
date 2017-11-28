//flightsTableManager.h

#ifndef FLIGHTSTABLEMANAGER_H
#define FLIGHTSTABLEMANAGER_H
#include "structs.h"

void printFlightArray(tFlightArray flightArray);
tFlight** expandFLightArray(tFlight ** flightArray, long size);
int getNumberOfFLighst();
tFlightArray getFlightArray();
int getFlight(char * flight_code);
int insert_flight(char * flight_code, char * origin, char * destination, char * departure_time, char * departure_date, char * arrival_time, char * arrival_date, char * model);

#endif