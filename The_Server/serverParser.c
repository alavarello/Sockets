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


char * sendAllFLights(int * bytes){
	tFlightArray * f = getFlightArray();
	int error = sqlite3_errcode(db);
	if(f == NULL){
		*bytes = ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int));
		char * resBuff = malloc(ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int)));
		strcpy(resBuff, ERROR_CODE);
		memcpy((resBuff+ERROR_CODE_CHAR_MAX), &error, sizeof(int));
		return ERROR_CODE;
	}
	*bytes = TFLIGHT_BYTES*f->size + sizeof(long);
	return serialize_flight_array(f);
}

char * sendFlight(char * flightCode, int * bytes){
	int error = sqlite3_errcode(db);
	tFlight * f = getFlight(flightCode);
	if(f == NULL){
		*bytes = ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int));
		char * resBuff = malloc(ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int)));
		strcpy(resBuff, ERROR_CODE);
		memcpy((resBuff+ERROR_CODE_CHAR_MAX), &error, sizeof(int));
		return ERROR_CODE;
	}
	*bytes = TFLIGHT_BYTES;
	return serialize_flight(f);
}

char * sendAllPlanes(int * bytes){
	int error = sqlite3_errcode(db);
	tPlaneArray * p = getPlaneArray();
	if(p == NULL){
		*bytes = ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int));
		char * resBuff = malloc(ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int)));
		strcpy(resBuff, ERROR_CODE);
		memcpy((resBuff+ERROR_CODE_CHAR_MAX), &error, sizeof(int));
		return ERROR_CODE;
	}
	*bytes = TPLANES_BYTES*p->size + 1*sizeof(long);
	return serialize_plane_array(p);
}

char * sendAllReservations(int * bytes){
	int error = sqlite3_errcode(db);
	tReservationArray * r = getReservationArray();
	if(r == NULL){
		*bytes = ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int));
		char * resBuff = malloc(ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int)));
		strcpy(resBuff, ERROR_CODE);
		memcpy((resBuff+ERROR_CODE_CHAR_MAX), &error, sizeof(int));
		return ERROR_CODE;
	}
	*bytes = TRESERVATION_BYTES*r->size + sizeof(long);
	return serialize_reservation_array(r);
}

char * sendAllCancellations(int * bytes){
	int error = sqlite3_errcode(db);
	tReservationArray * r = getCancelationArray();
	if(r == NULL){
		*bytes = ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int));
		char * resBuff = malloc(ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int)));
		strcpy(resBuff, ERROR_CODE);
		memcpy((resBuff+ERROR_CODE_CHAR_MAX), &error, sizeof(int));
		return ERROR_CODE;
	}
	*bytes = TRESERVATION_BYTES*r->size + sizeof(long);
	return serialize_reservation_array(r);
}

char * sendReservationForAFLight(char * flightCode,int * bytes){
	int error = sqlite3_errcode(db);
	tSeatsArray * s = getReservationsSeats(flightCode);
	if(s == NULL){
		*bytes = ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int));
		char * resBuff = malloc(ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int)));
		strcpy(resBuff, ERROR_CODE);
		memcpy((resBuff+ERROR_CODE_CHAR_MAX), &error, sizeof(int));
		return ERROR_CODE;
	}
	*bytes = (SEAT_NUMBER_CHAR_MAX*s->size)+sizeof(int);
	return serialize_seatArray(s);
}

char * sendReservation(char * flightCode, char * seat,int * bytes){
	int error = sqlite3_extended_errcode(db);
	tReservation * r = getReservation(flightCode, seat);
	if(r == NULL){
		*bytes = ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int));
		char * resBuff = malloc(ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int)));
		strcpy(resBuff, ERROR_CODE);
		memcpy((resBuff+ERROR_CODE_CHAR_MAX), &error, sizeof(int));
		return ERROR_CODE;
	}
	*bytes = TRESERVATION_BYTES;
	return serialize_reservation(r);
}

char * insertFlight(char * buff,int * bytes){
	tFlight *  f = deserialize_flight(buff);
	int  res = insert_flight(f->flightCode, f->origin, f->destination, f->departureTime, f->departureDate, f->arrivalTime, f->arrivalDate, f->planeCode);
	char * resBuff;
	if(res == SQLITE_OK){
		*bytes = COMPLETE_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int));
		resBuff = malloc(COMPLETE_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int)));
		strcpy(resBuff, COMPLETE_CODE);
		memcpy((resBuff+COMPLETE_CODE_CHAR_MAX), &res, sizeof(int));
		return resBuff;
	}
	else{
		*bytes = ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int));
		resBuff = malloc(ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int)));
		strcpy(resBuff, ERROR_CODE);
		memcpy((resBuff+ERROR_CODE_CHAR_MAX), &res, sizeof(int));
		return resBuff;
	}
}


char * insertReservation(char * buff,int * bytes){
	tReservation *  r = deserialize_reservation(buff);
	int  res = insert_reservation(r->flightCode, r->seatNumber, r->userName);
	char * resBuff;
	if(res == SQLITE_OK){
		*bytes = COMPLETE_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int));
		resBuff = malloc(COMPLETE_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int)));
		strcpy(resBuff, COMPLETE_CODE);
		memcpy((resBuff+COMPLETE_CODE_CHAR_MAX), &res, sizeof(int));
		return resBuff;
	}
	else{
		*bytes = ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int));
		resBuff = malloc(ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int)));
		strcpy(resBuff, ERROR_CODE);
		memcpy((resBuff+ERROR_CODE_CHAR_MAX), &res, sizeof(int));
		return resBuff;
	}
}

char * insertCancellation(char * buff,int * bytes){
	tReservation *  r = deserialize_reservation(buff);
	int  res = insert_cancellation(r->seatNumber,r->flightCode);
	char * resBuff;
	if(res == SQLITE_OK){
		*bytes = COMPLETE_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int));
		resBuff = malloc(COMPLETE_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int)));
		strcpy(resBuff, COMPLETE_CODE);
		memcpy((resBuff+COMPLETE_CODE_CHAR_MAX), &res, sizeof(int));
		return resBuff;
	}
	else{
		*bytes = ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int));
		resBuff = malloc(ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int)));
		strcpy(resBuff, ERROR_CODE);
		memcpy((resBuff+ERROR_CODE_CHAR_MAX), &res, sizeof(int));
		return resBuff;
	}
}

char * deleteFlight(char * buff,int * bytes){
	int  res =delete_flight(buff);
	char * resBuff;
	if(res == SQLITE_OK){
		*bytes = COMPLETE_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int));
		resBuff = malloc(COMPLETE_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int)));
		strcpy(resBuff, COMPLETE_CODE);
		memcpy((resBuff+COMPLETE_CODE_CHAR_MAX), &res, sizeof(int));
		return resBuff;
	}
	else{
		*bytes = ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int));
		resBuff = malloc(ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int)));
		strcpy(resBuff, ERROR_CODE);
		memcpy((resBuff+ERROR_CODE_CHAR_MAX), &res, sizeof(int));
		return resBuff;
	}
}

char * deleteReservation(char * buff,int * bytes){
	int  res = delete_reservation(buff, buff + FLIGHT_CODE_CHAR_MAX);
	char * resBuff;
	if(res == SQLITE_OK){
		*bytes = COMPLETE_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int));
		resBuff = malloc(COMPLETE_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int)));
		strcpy(resBuff, COMPLETE_CODE);
		memcpy((resBuff+COMPLETE_CODE_CHAR_MAX), &res, sizeof(int));
		return resBuff;
	}
	else{
		*bytes = ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int));
		resBuff = malloc(ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int)));
		strcpy(resBuff, ERROR_CODE);
		memcpy((resBuff+ERROR_CODE_CHAR_MAX), &res, sizeof(int));
		return resBuff;
	}
}







char * parseAndExecute(char * buff,int * bytes){

	int action = (int) *buff;
	char * resBuff;
	int error = ACTION_CODE_ERROR;
	buff += sizeof(int);
	switch(action){
		case SEND_ALL_FLIGHTS:
			return sendAllFLights(bytes);
		case SEND_FLIGHT:
			return sendFlight(buff,bytes);
		case INSERT_FLIGHT:
			return insertFlight(buff,bytes);
		case SEND_ALL_PLANES:
			return sendAllPlanes(bytes);
		case SEND_ALL_RESERVATIONS:
			return sendAllReservations(bytes);
		case INSERT_RESERVATION:
			return insertReservation(buff,bytes);
		case INSERT_CANCELLATION:
			return insertCancellation(buff,bytes);
		case SEND_RESERVATIONS_FOR_A_FLIGHT:
			return sendReservationForAFLight(buff,bytes);
		case SEND_RESERVATION:
			return sendReservation(buff, (buff + FLIGHT_CODE_CHAR_MAX ),bytes);
		case DELETE_FLIGHT:
			return deleteFlight(buff,bytes);
		case DELETE_RESERVATON:
			return deleteReservation(buff,bytes);
	}
	*bytes = ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int));
	resBuff = malloc(ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int)));
	strcpy(resBuff, ERROR_CODE);
	memcpy((resBuff+ERROR_CODE_CHAR_MAX), &error, sizeof(int));
	return resBuff;

}
