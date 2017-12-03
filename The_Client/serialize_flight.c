
#include "structs.h"
#include "constants.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char * serialize_flight(tFlight * t)
{
  int bytes = 0;
  char * buff, * aux;

  
  bytes = ( FLIGHT_CODE_CHAR_MAX + ORIGIN_CHAR_MAX + DESTINATION_CHAR_MAX + DEPARTURE_TIME_CHAR_MAX + DEPARTURE_DATE_CHAR_MAX +
  ARRIVAL_TIME_CHAR_MAX + ARRIVAL_DATE_CHAR_MAX + PLANE_CODE_CHAR_MAX )*sizeof(char);

  buff = malloc(bytes);
  aux = buff;

  memcpy(aux, t->flightCode, FLIGHT_CODE_CHAR_MAX);
  aux += FLIGHT_CODE_CHAR_MAX;

  memcpy(aux, t->origin, ORIGIN_CHAR_MAX);
  aux += ORIGIN_CHAR_MAX;

  memcpy(aux, t->destination, DESTINATION_CHAR_MAX);
  aux += DESTINATION_CHAR_MAX;

  memcpy(aux, t->departureTime, DEPARTURE_TIME_CHAR_MAX);
  aux += DEPARTURE_TIME_CHAR_MAX;

  memcpy(aux, t->departureDate, DEPARTURE_DATE_CHAR_MAX);
  aux += DEPARTURE_DATE_CHAR_MAX;

  memcpy(aux, t->arrivalTime, ARRIVAL_TIME_CHAR_MAX);
  aux += ARRIVAL_TIME_CHAR_MAX;

  memcpy(aux, t->arrivalDate, ARRIVAL_DATE_CHAR_MAX);
  aux += ARRIVAL_DATE_CHAR_MAX;

  memcpy(aux, t->planeCode, PLANE_CODE_CHAR_MAX);

  return buff;

}

tFlight * deserialize_flight(char * buff)
{

  tFlight * res = malloc(sizeof(tFlight));

  res->flightCode = malloc(FLIGHT_CODE_CHAR_MAX*sizeof(char));
  memcpy(res->flightCode, buff, FLIGHT_CODE_CHAR_MAX);
  buff += FLIGHT_CODE_CHAR_MAX;

  res->origin = malloc(ORIGIN_CHAR_MAX*sizeof(char));
  memcpy(res->origin, buff, ORIGIN_CHAR_MAX);
  buff += ORIGIN_CHAR_MAX;

  res->destination = malloc(DESTINATION_CHAR_MAX*sizeof(char));
  memcpy(res->destination, buff, DESTINATION_CHAR_MAX);
  buff += DESTINATION_CHAR_MAX;

  res->departureTime = malloc(DEPARTURE_TIME_CHAR_MAX*sizeof(char));
  memcpy(res->departureTime, buff, DEPARTURE_TIME_CHAR_MAX);
  buff += DEPARTURE_TIME_CHAR_MAX;

  res->departureDate = malloc(DEPARTURE_DATE_CHAR_MAX*sizeof(char));
  memcpy(res->departureDate, buff, DEPARTURE_DATE_CHAR_MAX);
  buff += DEPARTURE_DATE_CHAR_MAX;

  res->arrivalTime = malloc(ARRIVAL_TIME_CHAR_MAX*sizeof(char));
  memcpy(res->arrivalTime, buff, ARRIVAL_TIME_CHAR_MAX);
  buff += ARRIVAL_TIME_CHAR_MAX;

  res->arrivalDate = malloc(ARRIVAL_DATE_CHAR_MAX*sizeof(char));
  memcpy(res->arrivalDate, buff, ARRIVAL_DATE_CHAR_MAX);
  buff += ARRIVAL_DATE_CHAR_MAX;

  res->planeCode = malloc(PLANE_CODE_CHAR_MAX*sizeof(char));
  memcpy(res->planeCode, buff, PLANE_CODE_CHAR_MAX);

  return res;

}

char * serialize_flight_array(tFlightArray * flightArray){
  int bytes = 0, i;
  char * buff, * aux, *flight;

  
  bytes = ( FLIGHT_CODE_CHAR_MAX + ORIGIN_CHAR_MAX + DESTINATION_CHAR_MAX + DEPARTURE_TIME_CHAR_MAX + DEPARTURE_DATE_CHAR_MAX +
  ARRIVAL_TIME_CHAR_MAX + ARRIVAL_DATE_CHAR_MAX + PLANE_CODE_CHAR_MAX )*sizeof(char);

  buff = malloc(flightArray->size*bytes + sizeof(long));
  aux = buff;
  memcpy(aux, &(flightArray->size), sizeof(long));
  aux += sizeof(long);
  for(i = 0; i<flightArray->size; i++){
    flight = serialize_flight(flightArray->flightArray[i]);
    memcpy(aux, flight, bytes);
    free(flight);
    aux += bytes;
  }
  return buff;
}

tFlightArray * deserialize_flight_array(char * buff){
  int i;
  tFlightArray * res = malloc(sizeof(tFlightArray));
  memcpy(&(res->size), buff, sizeof(long));
  buff += sizeof(long);
  int bytes = ( FLIGHT_CODE_CHAR_MAX + ORIGIN_CHAR_MAX + DESTINATION_CHAR_MAX + DEPARTURE_TIME_CHAR_MAX + DEPARTURE_DATE_CHAR_MAX +
  ARRIVAL_TIME_CHAR_MAX + ARRIVAL_DATE_CHAR_MAX + PLANE_CODE_CHAR_MAX )*sizeof(char);


  res->flightArray = malloc(res->size*sizeof(tFlight*));
  for(i = 0; i< res->size; i++){
    res->flightArray[i] = deserialize_flight(buff);
    buff += bytes;
  }
  return res;
}



char * serialize_seatArray(tSeatsArray * seatArray){
char * buff = malloc((SEAT_NUMBER_CHAR_MAX*seatArray->size)+sizeof(int));
char * auxBuff = buff;
int i = 0;
memcpy(auxBuff,&(seatArray->size), sizeof(int));
auxBuff += sizeof(int);
  while(i< seatArray->size)
  {
    memcpy(auxBuff,seatArray->reservedSeats[i], SEAT_NUMBER_CHAR_MAX);
    auxBuff += SEAT_NUMBER_CHAR_MAX;
    i++;
  }
  return buff;
}

tSeatsArray * deserialize_seatArray(char* buff){
  tSeatsArray * seatArray = malloc(sizeof(tSeatsArray));
  int i = 0;
  memcpy(&(seatArray->size), buff, sizeof(int));
  buff += sizeof(int);
  seatArray->reservedSeats = malloc(sizeof(char*)*seatArray->size);
  while(i < seatArray->size){
      seatArray->reservedSeats[i] = malloc(sizeof(char)*SEAT_NUMBER_CHAR_MAX);
      memcpy(seatArray->reservedSeats[i], buff, sizeof(char)*SEAT_NUMBER_CHAR_MAX);
      buff += sizeof(char)*SEAT_NUMBER_CHAR_MAX;
      i++;
  }
  return seatArray;
}


