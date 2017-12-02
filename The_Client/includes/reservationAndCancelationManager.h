//reservationAndCancelationManager.h

#ifndef RESERVATIONANDCANCELATIONMANAGER_H
#define RESERVATIONANDCANCELATIONMANAGER_H
#include "structs.h"

tReservation** expanReservationArray(tReservation** reservationsArray, long size);
int getNumberOfReservationOrCancelations(char* table);
tReservationArray *getReservationOrCancelationArray(char* table);
void printReservationArray(tReservationArray reservationsArray);
tReservation * getReservation(char * flightCode, char * seat);
int insert_reservation(char * flight_code, char * seat, char * name);
tReservationArray *getReservationArray();
tReservationArray *getCancelationArray();
tSeatsArray * getReservationsSeats(char * flightCode);
char ** exapndSeatsArray(char** seatsArray, int* size);
void printSeatsArray(tSeatsArray seatsArray);
int delete_reservation(char * flight_code, char * seat);
#endif