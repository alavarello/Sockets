#ifndef SERIALIZE_RESERVATION_H
#define SERIALIZE_RESERVATION_H

#include "structs.h"

char * serialize_reservation(tReservation * t);
tReservation * deserialize_reservation(char * buff);
char * serialize_reservation_array(tReservationArray * reservationArray);
tReservationArray * deserialize_reservation_array(char * buff);

#endif

