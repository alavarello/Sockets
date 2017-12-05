#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "serialize_flight.h"
#include "serialize_plane.h"
#include "serialize_reservation.h"
#include "clientParser.h"
#include "structs.h"
#include "constants.h"

char * parseMessageToSend(int action, void * param, int * bytes)
{
	char * resBuff = malloc(sizeof(int));
	*bytes = sizeof(int);
	char * aux;
	int error = ACTION_CODE_ERROR;

	switch(action)
	{
		case GET_ALL_FLIGHTS:
		{
			memcpy(resBuff, &action, sizeof(int));
			return resBuff;
		}	
		case GET_FLIGHT:
		{
			resBuff = realloc(resBuff, sizeof(int)+FLIGHT_CODE_CHAR_MAX); 
			*bytes = sizeof(int)+FLIGHT_CODE_CHAR_MAX;
			memcpy(resBuff, &action, sizeof(int));
			strcpy(resBuff+sizeof(int), (char*)param);
			return resBuff;
		}	
		case INSERT_FLIGHT:
		{
			aux = serialize_flight((tFlight *) param);
			free(resBuff);
			resBuff = malloc(TFLIGHT_BYTES+sizeof(int));
			*bytes = sizeof(int)+TFLIGHT_BYTES;
			memcpy(resBuff, &action, sizeof(int));		
			memcpy(resBuff+sizeof(int), aux, TFLIGHT_BYTES);
			return resBuff;
		}	
		case GET_ALL_PLANES:
		{
			memcpy(resBuff, &action, sizeof(int));
			return resBuff;
		}	
		case GET_ALL_RESERVATIONS:
		{
			memcpy(resBuff, &action, sizeof(int));
			return resBuff;
		}	
		case GET_ALL_CANCELATIONS:
		{
			memcpy(resBuff, &action, sizeof(int));
			return resBuff;
		}	
		case INSERT_RESERVATION:
		{
			aux = serialize_reservation((tReservation *) param);
			free(resBuff);
			resBuff = malloc(TRESERVATION_BYTES+sizeof(int));
			*bytes = sizeof(int)+TRESERVATION_BYTES;
			memcpy(resBuff, &action, sizeof(int));
			memcpy(resBuff+sizeof(int), aux, TRESERVATION_BYTES);
			return resBuff;
		}	
		case INSERT_CANCELLATION:
		{
			aux = serialize_reservation((tReservation *) param);
			free(resBuff);
			resBuff = malloc(TRESERVATION_BYTES+sizeof(int));
			*bytes = sizeof(int)+TRESERVATION_BYTES;
			memcpy(resBuff, &action, sizeof(int));
			memcpy(resBuff+sizeof(int), aux, TRESERVATION_BYTES);
			return resBuff;
		}	
		case GET_RESERVATIONS_FOR_A_FLIGHT:
		{
			resBuff = realloc(resBuff, sizeof(int)+FLIGHT_CODE_CHAR_MAX);
			*bytes = sizeof(int)+FLIGHT_CODE_CHAR_MAX;
			memcpy(resBuff, &action, sizeof(int));
			strcpy(resBuff+sizeof(int), (char*)param);
			return resBuff;
		}	
		case GET_RESERVATION:
		{
			resBuff = realloc(resBuff, sizeof(int)+FLIGHT_CODE_CHAR_MAX+SEAT_NUMBER_CHAR_MAX);
			*bytes = sizeof(int)+FLIGHT_CODE_CHAR_MAX + SEAT_NUMBER_CHAR_MAX;
			memcpy(resBuff, &action, sizeof(int));
			strcpy(resBuff+sizeof(int), (char*)((tReservation*)param)->flightCode);
			strcpy(resBuff+sizeof(int)+FLIGHT_CODE_CHAR_MAX, (char*)((tReservation*)param)->seatNumber);
			return resBuff;
		}	
		case DELETE_FLIGHT:
		{
			resBuff = realloc(resBuff, sizeof(int)+FLIGHT_CODE_CHAR_MAX);
			*bytes = sizeof(int)+FLIGHT_CODE_CHAR_MAX;
			memcpy(resBuff, &action, sizeof(int));
			strcpy(resBuff+sizeof(int), (char*)param);
			return resBuff;
		}	
		case DELETE_RESERVATON:
		{
			resBuff = realloc(resBuff, sizeof(int)+FLIGHT_CODE_CHAR_MAX+SEAT_NUMBER_CHAR_MAX);
			*bytes = sizeof(int)+FLIGHT_CODE_CHAR_MAX + SEAT_NUMBER_CHAR_MAX;
			memcpy(resBuff, &action, sizeof(int));
			strcpy(resBuff+sizeof(int), (char*)((tReservation*)param)->flightCode);
			strcpy(resBuff+sizeof(int)+FLIGHT_CODE_CHAR_MAX, (char*)((tReservation*)param)->seatNumber);
			return resBuff;
		}	
	}

	resBuff = malloc(ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int)));
	strcpy(resBuff, ERROR_CODE);
	memcpy((resBuff+ERROR_CODE_CHAR_MAX), &error, sizeof(int));

	return resBuff;
}


void * parseRecivedMessage(int action, char * buff){

	int error = ACTION_CODE_ERROR;
	char * resBuff;
	tFlightArray * fa;
	tFlight * f;
	tPlaneArray * pa;
	tReservationArray * ra;
	tSeatsArray * sa;
	tReservation * r;
	switch(action){
		case GET_ALL_FLIGHTS:
			fa = deserialize_flight_array(buff);
			free(buff);
			return fa;
		case GET_FLIGHT:
			f = deserialize_flight(buff);
			free(buff);
			return f;
		case INSERT_FLIGHT:
			buff[ERROR_CODE_CHAR_MAX] = 0;
			return buff;
		case GET_ALL_PLANES:
			pa = deserialize_plane_array(buff);
			free(buff);
			return pa;
		case GET_ALL_RESERVATIONS:
			ra = deserialize_reservation_array(buff);
			free(buff);
			return ra;
		case GET_ALL_CANCELATIONS:
			ra = deserialize_reservation_array(buff);
			return ra;
		case INSERT_RESERVATION:
			return buff;
		case INSERT_CANCELLATION:
			buff[ERROR_CODE_CHAR_MAX] = 0;
			return buff;
		case GET_RESERVATIONS_FOR_A_FLIGHT:
			sa = deserialize_seatArray(buff);
			free(buff);
			return sa;
		case GET_RESERVATION:
			r = deserialize_reservation(buff);
			printf("%s.  %s\n",r->flightCode, r->seatNumber );
			free(buff);
			return r;
		case DELETE_FLIGHT:
			buff[ERROR_CODE_CHAR_MAX] = 0;
			return buff;
		case DELETE_RESERVATON:
			buff[ERROR_CODE_CHAR_MAX] = 0;
			return buff;
		default: 
			resBuff = malloc(ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int)));
			strcpy(resBuff, ERROR_CODE);
			memcpy((resBuff+ERROR_CODE_CHAR_MAX), &error, sizeof(int));
			return resBuff;
	}
}
