#include "databaseManager.c"

char * serialize_flight(tFlight * t)
{
  int bytes = 0;
  char * buff;

  char * aux = buff;

  bytes = ( FLIGHT_CODE_CHAR_MAX + ORIGIN_CHAR_MAX + DESTINATION_CHAR_MAX + DEPARTURE_TIME_CHAR_MAX + DEPARTURE_DAY_CHAR_MAX +
  ARRIVAL_TIME_CHAR_MAX + ARRIVAL_DATE_CHAR_MAX + PLANE_CODE_CHAR_MAX )*sizeof(char);

  buff = malloc(bytes);

  memcpy(aux, t->flightCode, FLIGHT_CODE_CHAR_MAX);
  aux += FLIGHT_CODE_CHAR_MAX;

  memcpy(aux, t->origin, ORIGIN_CHAR_MAX);
  aux += ORIGIN_CHAR_MAX;

  memcpy(aux, t->destination, DESTINATION_CHAR_MAX);
  aux += DESTINATION_CHAR_MAX;

  memcpy(aux, t->departureTime, DEPARTURE_TIME_CHAR_MAX);
  aux += DEPARTURE_TIME_CHAR_MAX;

  memcpy(aux, t->departureDate, DEPARTURE_DAY_CHAR_MAX);
  aux += DEPARTURE_DAY_CHAR_MAX;

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
  memcpy(res->origin, buff, DESTINATION_CHAR_MAX);
  buff += DESTINATION_CHAR_MAX;

  res->departureTime = malloc(DEPARTURE_TIME_CHAR_MAX*sizeof(char));
  memcpy(res->origin, buff, DEPARTURE_TIME_CHAR_MAX);
  buff += DEPARTURE_TIME_CHAR_MAX;

  res->departureDate = malloc(DEPARTURE_DAY_CHAR_MAX*sizeof(char));
  memcpy(res->departureDate, buff, DEPARTURE_DAY_CHAR_MAX);
  buff += DEPARTURE_DAY_CHAR_MAX;

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
