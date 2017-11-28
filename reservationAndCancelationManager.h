//reservationAndCancelationManager.h

#ifndef RESERVATIONANDCANCELATIONMANAGER_H
#define RESERVATIONANDCANCELATIONMANAGER_H
#include "structs.h"

tReservation** expanReservationArray(tReservation** reservationsArray, long size);
int getNumberOfReservationOrCancelations(char* table);
tReservationArray getReservationOrCancelationArray(char* table);
void printReservationArray(tReservationArray reservationsArray);
int getReservation(char * reservation_code);
int insert_reservation(char * flight_code, char * seat, char * passport, char * name, char * reservation_code);
int insert_cancellation(char * reservation);
tReservationArray getReservationArray();
tReservationArray getCancelationArray();
char** getReservationsSeats(char * flightCode);
char ** exapndSeatsArray(char** seatsArray, int* size);
#endif