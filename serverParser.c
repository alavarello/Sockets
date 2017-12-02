#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "planesTableManager.h"
#include "flightsTableManager.h"
#include "reservationAndCancelationManager.h"
#include "serialize_flight.h"
#include "serialize_plane.h"
#include "serialize_reservation.h"
#include "serverParser.h"
#include "structs.h"
#include "constants.h"
#include <sqlite3.h>


#define SEND_ALL_FLIGHTS 1
#define SEND_FLIGHT 2
#define INSERT_FLIGHT 3
#define SEND_ALL_PLANES 4
#define SEND_ALL_RESERVATIONS 5
#define SEND_ALL_CANCELATIONS 6
#define INSERT_RESERVATION 7
#define INSERT_CANCELLATION 8
#define SEND_RESERVATIONS_FOR_A_FLIGHT 9
#define SEND_RESERVATION 10
#define DELETE_FLIGHT 11
#define DELETE_RESERVATON 12
#define ERROR_CODE "ERROR"
#define COMPLETE_CODE "OKEYY"
#define COMPLETE_CODE_CHAR_MAX 6
#define ERROR_CODE_CHAR_MAX 6
#define ACTION_CODE_ERROR 49

extern sqlite3 *db;


char * sendAllFLights(){
	tFlightArray * f = getFlightArray();
	int error = sqlite3_errcode(db);
	if(f == NULL){
		char * resBuff = malloc(ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int)));
		strcpy(resBuff, ERROR_CODE);
		memcpy((resBuff+ERROR_CODE_CHAR_MAX), &error, sizeof(int));
		return ERROR_CODE;
	}
	return serialize_flight_array(f);
}

char * sendFlight(char * flightCode){
	int error = sqlite3_errcode(db);
	tFlight * f = getFlight(flightCode);
	if(f == NULL){
		char * resBuff = malloc(ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int)));
		strcpy(resBuff, ERROR_CODE);
		memcpy((resBuff+ERROR_CODE_CHAR_MAX), &error, sizeof(int));
		return ERROR_CODE;
	}
	return serialize_flight(f);
}

char * sendAllPlanes(){
	int error = sqlite3_errcode(db);
	tPlaneArray * p = getPlaneArray();
	if(p == NULL){
		char * resBuff = malloc(ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int)));
		strcpy(resBuff, ERROR_CODE);
		memcpy((resBuff+ERROR_CODE_CHAR_MAX), &error, sizeof(int));
		return ERROR_CODE;
	}
	return serialize_plane_array(p);
}

char * sendAllReservations(){
	int error = sqlite3_errcode(db);
	tReservationArray * r = getReservationArray();
	if(r == NULL){
		char * resBuff = malloc(ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int)));
		strcpy(resBuff, ERROR_CODE);
		memcpy((resBuff+ERROR_CODE_CHAR_MAX), &error, sizeof(int));
		return ERROR_CODE;
	}
	return serialize_reservation_array(r);
}

char * sendAllCancellations(){
	int error = sqlite3_errcode(db);
	tReservationArray * r = getCancelationArray();
	if(r == NULL){
		char * resBuff = malloc(ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int)));
		strcpy(resBuff, ERROR_CODE);
		memcpy((resBuff+ERROR_CODE_CHAR_MAX), &error, sizeof(int));
		return ERROR_CODE;
	}
	return serialize_reservation_array(r);
}

char * sendReservationForAFLight(char * flightCode){
	int error = sqlite3_errcode(db);
	tSeatsArray * s = getReservationsSeats(flightCode);
	if(s == NULL){
		char * resBuff = malloc(ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int)));
		strcpy(resBuff, ERROR_CODE);
		memcpy((resBuff+ERROR_CODE_CHAR_MAX), &error, sizeof(int));
		return ERROR_CODE;
	}
	return serialize_seatArray(s);
}

char * sendReservation(char * flightCode, char * seat){
	int error = sqlite3_errcode(db);
	tReservation * r = getReservation(flightCode, seat);
	if(r == NULL){
		char * resBuff = malloc(ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int)));
		strcpy(resBuff, ERROR_CODE);
		memcpy((resBuff+ERROR_CODE_CHAR_MAX), &error, sizeof(int));
		return ERROR_CODE;
	}
	return serialize_reservation(r);
}

char * insertFlight(char * buff){
	int error = sqlite3_errcode(db);
	tFlight *  f = deserialize_flight(buff);
	int  res = insert_flight(f->flightCode, f->origin, f->destination, f->departureTime, f->departureDate, f->arrivalTime, f->arrivalDate, f->planeCode); 
	char * resBuff;
	if(res == SQLITE_OK){
		resBuff = malloc(COMPLETE_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int)));
		strcpy(resBuff, COMPLETE_CODE);
		memcpy((resBuff+COMPLETE_CODE_CHAR_MAX), &res, sizeof(int));
		return resBuff;
	}
	else{
		resBuff = malloc(ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int)));
		strcpy(resBuff, ERROR_CODE);
		memcpy((resBuff+ERROR_CODE_CHAR_MAX), &res, sizeof(int));
		return resBuff;
	}
}


char * insertReservation(char * buff){
	int error = sqlite3_errcode(db);
	tReservation *  r = deserialize_reservation(buff);
	int  res = insert_reservation(r->flightCode, r->seatNumber, r->userName);
	char * resBuff;
	if(res == SQLITE_OK){
		resBuff = malloc(COMPLETE_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int)));
		strcpy(resBuff, COMPLETE_CODE);
		memcpy((resBuff+COMPLETE_CODE_CHAR_MAX), &res, sizeof(int));
		return resBuff;
	}
	else{
		resBuff = malloc(ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int)));
		strcpy(resBuff, ERROR_CODE);
		memcpy((resBuff+ERROR_CODE_CHAR_MAX), &res, sizeof(int));
		return resBuff;
	}
}

char * insertCancellation(char * buff){
	int error = sqlite3_errcode(db);
	tReservation *  r = deserialize_reservation(buff);
	int  res = insert_cancellation(r->flightCode, r->seatNumber, r->userName);
	char * resBuff;
	if(res == SQLITE_OK){
		resBuff = malloc(COMPLETE_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int)));
		strcpy(resBuff, COMPLETE_CODE);
		memcpy((resBuff+COMPLETE_CODE_CHAR_MAX), &res, sizeof(int));
		return resBuff;
	}
	else{
		resBuff = malloc(ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int)));
		strcpy(resBuff, ERROR_CODE);
		memcpy((resBuff+ERROR_CODE_CHAR_MAX), &res, sizeof(int));
		return resBuff;
	}
}

char * deleteFlight(char * buff){
	int error = sqlite3_errcode(db);
	int  res =delete_flight(buff);
	char * resBuff;
	if(res == SQLITE_OK){
		resBuff = malloc(COMPLETE_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int)));
		strcpy(resBuff, COMPLETE_CODE);
		memcpy((resBuff+COMPLETE_CODE_CHAR_MAX), &res, sizeof(int));
		return resBuff;
	}
	else{
		resBuff = malloc(ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int)));
		strcpy(resBuff, ERROR_CODE);
		memcpy((resBuff+ERROR_CODE_CHAR_MAX), &res, sizeof(int));
		return resBuff;
	}
}

char * deleteReservation(char * buff){
	int error = sqlite3_errcode(db);
	int  res = delete_reservation(buff, buff + FLIGHT_CODE_CHAR_MAX);
	char * resBuff;
	if(res == SQLITE_OK){
		resBuff = malloc(COMPLETE_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int)));
		strcpy(resBuff, COMPLETE_CODE);
		memcpy((resBuff+COMPLETE_CODE_CHAR_MAX), &res, sizeof(int));
		return resBuff;
	}
	else{
		resBuff = malloc(ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int)));
		strcpy(resBuff, ERROR_CODE);
		memcpy((resBuff+ERROR_CODE_CHAR_MAX), &res, sizeof(int));
		return resBuff;
	}
}







char * parseAndExecute(char * buff){

	int action = (int) *buff;
	char * resBuff;
	int error = ACTION_CODE_ERROR;
	buff += sizeof(int);
	switch(action){
		case SEND_ALL_FLIGHTS:
			return sendAllFLights();
		case SEND_FLIGHT:
			return sendFlight(buff);
		case INSERT_FLIGHT:
			return insertFlight(buff);
		case SEND_ALL_PLANES:
			return sendAllPlanes();
		case SEND_ALL_RESERVATIONS:
			return sendAllReservations();
		case INSERT_RESERVATION:
			return insertReservation(buff);
		case INSERT_CANCELLATION:
			insertCancellation(buff);
		case SEND_RESERVATIONS_FOR_A_FLIGHT:
			return sendReservationForAFLight(buff);
		case SEND_RESERVATION:
			return sendReservation(buff, (buff + FLIGHT_CODE_CHAR_MAX ));
		case DELETE_FLIGHT:
			return deleteFlight(buff);
		case DELETE_RESERVATON:
			return deleteReservation(buff);
	}
	resBuff = malloc(ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int)));
	strcpy(resBuff, ERROR_CODE);
	memcpy((resBuff+ERROR_CODE_CHAR_MAX), &error, sizeof(int));
	return resBuff;

}
