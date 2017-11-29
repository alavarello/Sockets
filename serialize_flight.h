
#ifndef SERIALIZE_FLIGHT_H
#define SERIALIZE_FLIGHT_H
#include "structs.h"

tFlight * deserialize_flight(char * buff);
char * serialize_flight(tFlight * t);
char * serialize_flight_array(tFlightArray * flightArray);
tFlightArray * deserialize_flight_array(char * buff);
char * serialize_seatArray(tSeatsArray * seatArray);
tSeatsArray * deserialize_seatArray(char* buff);

#endif