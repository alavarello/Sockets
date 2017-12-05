//constants.h
#ifndef CONSTANTS_H
#define CONSTANTS_H


//The 0 counts
#define FLIGHT_CODE_CHAR_MAX 6 
#define ORIGIN_CHAR_MAX 4
#define DESTINATION_CHAR_MAX 4
#define DEPARTURE_TIME_CHAR_MAX 6
#define DEPARTURE_DATE_CHAR_MAX 11
#define ARRIVAL_TIME_CHAR_MAX 6
#define ARRIVAL_DATE_CHAR_MAX 11
#define PLANE_CODE_CHAR_MAX 15

#define MODEL_CHAR_MAX 15

#define SEAT_NUMBER_CHAR_MAX 4
#define USER_NAME_CHAR_MAX 25
#define RESERVATION_CODE_CHAR_MAX 10

#define ERROR -1
#define OK 0

#define EOSA "FFF" //End Of Seats Array

#define MAX_SMAPHORE_NAME 15
#define PLANE_SEMAPHORE "/Plane"
#define FLIGHT_SEMAPHORE "/Flight"
#define RESERVATION_SEMAPHORE "/Reservation"
#define CANCELLATION_SEMAPHORE "/Cancellation"

#define MAX_PLANES 5
#define MAX_SEATS 1000
#define MAX_RESERVATIONS 4000


#define TFLIGHT_BYTES ((FLIGHT_CODE_CHAR_MAX + ORIGIN_CHAR_MAX + DESTINATION_CHAR_MAX + DEPARTURE_TIME_CHAR_MAX + DEPARTURE_DATE_CHAR_MAX + ARRIVAL_TIME_CHAR_MAX + ARRIVAL_DATE_CHAR_MAX + PLANE_CODE_CHAR_MAX )*sizeof(char))
#define TPLANES_BYTES (MODEL_CHAR_MAX*sizeof(char) + 4*sizeof(int))
#define TRESERVATION_BYTES ((FLIGHT_CODE_CHAR_MAX + SEAT_NUMBER_CHAR_MAX + USER_NAME_CHAR_MAX)*sizeof(char))
#endif
