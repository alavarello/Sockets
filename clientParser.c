#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "serialize_flight.h"
#include "serialize_plane.h"
#include "serialize_reservation.h"
#include "clientParser.h"
#include "structs.h"
#include "constants.h"
#include <sqlite3.h>


#define GET_ALL_FLIGHTS 1
#define GET_FLIGHT 2
#define INSERT_FLIGHT 3
#define GET_ALL_PLANES 4
#define GET_ALL_RESERVATIONS 5
#define GET_ALL_CANCELATIONS 6
#define INSERT_RESERVATION 7
#define INSERT_CANCELLATION 8
#define GET_RESERVATIONS_FOR_A_FLIGHT 9
#define GET_RESERVATION 10
#define ERROR_CODE "ERROR"
#define ERROR_CODE_CHAR_MAX 6
#define ACTION_CODE_ERROR 49



char * parseMessageToSend(int action, void * param){

	char * resBuff = malloc(sizeof(int));
	char * aux;
	int error = ACTION_CODE_ERROR;
	switch(action){
		case GET_ALL_FLIGHTS:
			memcpy(resBuff, &action, sizeof(int));
			return resBuff;
		case GET_FLIGHT:
			resBuff = realloc(resBuff, sizeof(int)+FLIGHT_CODE_CHAR_MAX);
			memcpy(resBuff, &action, sizeof(int));
			strcpy(resBuff+sizeof(int), (char*)param);
			return resBuff;
		case INSERT_FLIGHT:
			aux = serialize_flight((tFlight *) param);
			free(resBuff);
			resBuff = malloc(TFLIGHT_BYTES+sizeof(int));
			memcpy(resBuff, &action, sizeof(int));		
			memcpy(resBuff+sizeof(int), aux, TFLIGHT_BYTES);
			return resBuff;
		case GET_ALL_PLANES:
			memcpy(resBuff, &action, sizeof(int));
			return resBuff;
		case GET_ALL_RESERVATIONS:
			memcpy(resBuff, &action, sizeof(int));
			return resBuff;
		case INSERT_RESERVATION:
			aux = serialize_reservation((tReservation *) param);
			free(resBuff);
			resBuff = malloc(TRESERVATION_BYTES+sizeof(int));
			memcpy(resBuff, &action, sizeof(int));
			memcpy(resBuff+sizeof(int), aux, TRESERVATION_BYTES);
			return resBuff;
		case INSERT_CANCELLATION:
			aux = serialize_reservation((tReservation *) param);
			free(resBuff);
			resBuff = malloc(TRESERVATION_BYTES+sizeof(int));
			memcpy(resBuff, &action, sizeof(int));
			memcpy(resBuff+sizeof(int), aux, TRESERVATION_BYTES);
			return resBuff;
		case GET_RESERVATIONS_FOR_A_FLIGHT:
			resBuff = realloc(resBuff, sizeof(int)+FLIGHT_CODE_CHAR_MAX);
			memcpy(resBuff, &action, sizeof(int));
			strcpy(resBuff+sizeof(int), (char*)param);
			return resBuff;
		case GET_RESERVATION:
			resBuff = realloc(resBuff, sizeof(int)+FLIGHT_CODE_CHAR_MAX+SEAT_NUMBER_CHAR_MAX);
			memcpy(resBuff, &action, sizeof(int));
			strcpy(resBuff+sizeof(int), (char*)((tReservation*)param)->flightCode);
			strcpy(resBuff+sizeof(int)+FLIGHT_CODE_CHAR_MAX, (char*)((tReservation*)param)->seatNumber);
			return resBuff;
	}
	resBuff = malloc(ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int)));
	strcpy(resBuff, ERROR_CODE);
	memcpy((resBuff+ERROR_CODE_CHAR_MAX), &error, sizeof(int));
	return resBuff;

}

void printFlightArray(tFlightArray flightArray)
{
  int i;
  printf("PRINTING ARRAY: SIZE:%ld\n--------------------------------------------------",flightArray.size );
  for(i = 0; i<flightArray.size; i++)
  {

    printf("FlighCode: %s\n", flightArray.flightArray[i]->flightCode);
    printf("O:%s  D:%s\n", flightArray.flightArray[i]->origin,flightArray.flightArray[i]->destination);
    printf("DT:%s  DD:%s\n", flightArray.flightArray[i]->departureTime, flightArray.flightArray[i]->departureDate);
    printf("AT:%s  AD:%s\n", flightArray.flightArray[i]->arrivalTime,flightArray.flightArray[i]->arrivalDate);

  }
}

void printPlaneArray(tPlaneArray planeArray)
{
  int i;
  printf("PLANE SIZE: %d\n",planeArray.size );
  for(i=0; i< planeArray.size; i++)
  {
    printf("%s\n",planeArray.planeArray[i]->model ); 
    printf("Rows:%d R:%d M:%d L:%d\n",planeArray.planeArray[i]->rows,planeArray.planeArray[i]->right,planeArray.planeArray[i]->middle,planeArray.planeArray[i]->left); 
  }
}

void printReservationArray(tReservationArray reservationsArray)
{
  int i;
  printf("RESERVATION ARRAY: SIZE:%d\n",reservationsArray.size);
  for (i = 0; i < reservationsArray.size; ++i)
  {
   printf("FC:%s  SN:%s\n",reservationsArray.reservationsArray[i]->flightCode,reservationsArray.reservationsArray[i]->seatNumber);
  }
}

void printSeatsArray(tSeatsArray seatsArray)
{
  int i;
  printf("SEATS ARRAY: SIZE:%d\n",seatsArray.size);
  for (i = 0; i < seatsArray.size; ++i)
  {
   printf("SEAT:%s\n",seatsArray.reservedSeats[i]);
  }
}

char * parseRecivedMessage(int action, char * buff){

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
			printFlightArray(*fa);
			break;
		case GET_FLIGHT:
			f = deserialize_flight(buff);
			printf("%s\n", f->flightCode);
			break;
		case INSERT_FLIGHT:
			printf("%s\n",buff);
			printf("%d\n",(int)*(buff+ERROR_CODE_CHAR_MAX));
			break;
		case GET_ALL_PLANES:
			pa = deserialize_plane_array(buff);
			printPlaneArray(*pa);
			break;
		case GET_ALL_RESERVATIONS:
			ra = deserialize_reservation_array(buff);
			printReservationArray(*ra);
			break;
		case INSERT_RESERVATION:
			printf("%s\n",buff);
			printf("%d\n",(int)*(buff+ERROR_CODE_CHAR_MAX));
			break;
		case INSERT_CANCELLATION:
			printf("%s\n",buff);
			printf("%d\n",(int)*(buff+ERROR_CODE_CHAR_MAX));
			break;
		case GET_RESERVATIONS_FOR_A_FLIGHT:
			sa = deserialize_seatArray(buff);
			printSeatsArray(*sa);
		case GET_RESERVATION:
			r = deserialize_reservation(buff);
			printf("%s.  %s\n",r->flightCode, r->seatNumber );
			break;
		default: 
			resBuff = malloc(ERROR_CODE_CHAR_MAX*(sizeof(char)+ sizeof(int)));
			strcpy(resBuff, ERROR_CODE);
			memcpy((resBuff+ERROR_CODE_CHAR_MAX), &error, sizeof(int));
			printf("%s\n",resBuff );
	}
}
