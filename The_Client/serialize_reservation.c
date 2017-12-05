#include "structs.h"
#include "constants.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "freeMemory.h"

char * serialize_reservation(tReservation * t)
{
  int bytes = 0;
  char * buff, * aux;


  bytes = (FLIGHT_CODE_CHAR_MAX + SEAT_NUMBER_CHAR_MAX + USER_NAME_CHAR_MAX)*sizeof(char);

  buff = malloc(bytes);

  MALLOC_CHECK(buff);

  aux = buff;

  memcpy(aux, t->flightCode, FLIGHT_CODE_CHAR_MAX);
  aux += FLIGHT_CODE_CHAR_MAX;

  memcpy(aux, t->seatNumber, SEAT_NUMBER_CHAR_MAX);
  aux += SEAT_NUMBER_CHAR_MAX;

  memcpy(aux, t->userName, USER_NAME_CHAR_MAX);
  aux += USER_NAME_CHAR_MAX;

  return buff;

}

tReservation * deserialize_reservation(char * buff)
{

  tReservation * res = malloc(sizeof(tReservation));

  MALLOC_CHECK(res);

  res->flightCode = malloc(FLIGHT_CODE_CHAR_MAX*sizeof(char));
  memcpy(res->flightCode, buff, FLIGHT_CODE_CHAR_MAX);
  buff += FLIGHT_CODE_CHAR_MAX;

  res->seatNumber = malloc(SEAT_NUMBER_CHAR_MAX*sizeof(char));
  memcpy(res->seatNumber, buff, SEAT_NUMBER_CHAR_MAX);
  buff += SEAT_NUMBER_CHAR_MAX;

  res->userName = malloc(USER_NAME_CHAR_MAX*sizeof(char));
  memcpy(res->userName, buff, USER_NAME_CHAR_MAX);
  buff += USER_NAME_CHAR_MAX;

  return res;

}

char * serialize_reservation_array(tReservationArray * reservationArray)
{
  int bytes = 0, i;
  char * buff, * aux, *reservation;


  bytes = (FLIGHT_CODE_CHAR_MAX + SEAT_NUMBER_CHAR_MAX + USER_NAME_CHAR_MAX)*sizeof(char);

  buff = malloc(reservationArray->size*bytes + sizeof(long));

  MALLOC_CHECK(buff);

  aux = buff;
  memcpy(aux, &(reservationArray->size), sizeof(long));
  aux += sizeof(long);

  for(i = 0; i < reservationArray->size; i++){

    reservation = serialize_reservation(reservationArray->reservationsArray[i]);
    memcpy(aux, reservation, bytes);
    free(reservation);
    aux += bytes;
  }
  return buff;
}

tReservationArray * deserialize_reservation_array(char * buff)
{
  int i, bytes;
  tReservationArray * res = malloc(sizeof(tReservation));

  MALLOC_CHECK(res);
  
  memcpy(&(res->size), buff, sizeof(long));
  buff += sizeof(long);

  bytes = (FLIGHT_CODE_CHAR_MAX + SEAT_NUMBER_CHAR_MAX + USER_NAME_CHAR_MAX)*sizeof(char);


  res->reservationsArray = malloc(res->size*sizeof(tReservation*));

  for(i = 0; i< res->size; i++){
    res->reservationsArray[i] = deserialize_reservation(buff);
    buff += bytes;
  }
  return res;
}
