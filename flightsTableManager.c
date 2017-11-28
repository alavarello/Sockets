#include "flightsTableManager.h"
#include "constants.h"
#include "structs.h"
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern sqlite3 *db;

void printFlightArray(tFlightArray flightArray){
  int i;
  for(i = 0; i<flightArray.size; i++){

    printf("FlighCode: %s\n", flightArray.flightArray[i]->flightCode);
    printf("O:%s  D:%s\n", flightArray.flightArray[i]->origin,flightArray.flightArray[i]->destination);
    printf("DT:%s  DD:%s\n", flightArray.flightArray[i]->departureTime, flightArray.flightArray[i]->departureDate);
    printf("AT:%s  AD:%s\n", flightArray.flightArray[i]->arrivalTime,flightArray.flightArray[i]->arrivalDate);

  }
}


tFlight** expandFLightArray(tFlight ** flightArray, long size){
	int i;
	flightArray = realloc(flightArray, (size*sizeof(tFlight*)));

	for(i = 0; i < size; i++){
		flightArray[i] = malloc(sizeof(tFlight));
    flightArray[i]->flightCode = malloc(sizeof(char)*FLIGHT_CODE_CHAR_MAX);
    flightArray[i]->origin = malloc(sizeof(char)*ORIGIN_CHAR_MAX);
    flightArray[i]->destination = malloc(sizeof(char)*DESTINATION_CHAR_MAX);
    flightArray[i]->departureTime = malloc(sizeof(char)*DEPARTURE_TIME_CHAR_MAX);
    flightArray[i]->arrivalTime = malloc(sizeof(char)*ARRIVAL_TIME_CHAR_MAX);
    flightArray[i]->arrivalDate = malloc(sizeof(char)*ARRIVAL_DATE_CHAR_MAX);
    flightArray[i]->departureDate = malloc(sizeof(char)*DEPARTURE_DATE_CHAR_MAX);
    flightArray[i]->planeCode = malloc(sizeof(char)*PLANE_CODE_CHAR_MAX);
	}
	return flightArray;
}

int getNumberOfFLighst(){
	int rc, numberOfFlights;
	sqlite3_stmt *res;
	//getting the number of flights
    char * sqlFLightCount = "SELECT count(*) FROM flights";
    rc = sqlite3_prepare_v2(db, sqlFLightCount, -1, &res, 0);
    sqlite3_step(res);
    numberOfFlights = sqlite3_column_int(res, 0);
    sqlite3_finalize(res);
    return numberOfFlights;
}


tFlightArray getFlightArray(){
	char *err_msg = 0;
    sqlite3_stmt *res;
    tFlight** flightArray = NULL; 
    int rc, numberOfFlights, i;
    tFlightArray* flightArrayStruct;


    //ESTO tiene que ser atomico;
    numberOfFlights = getNumberOfFLighst();

    //getting the flights
    char *sql = "SELECT * FROM flights";
       
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    //------------------
   	
   	flightArray = expandFLightArray(flightArray, numberOfFlights);
    i = 0;
    while(sqlite3_step(res) == SQLITE_ROW) {
      
      strcpy(flightArray[i]->flightCode,(char*)sqlite3_column_text(res, FLIGHT_CODE_COLUMN));
      strcpy(flightArray[i]->origin,(char*)sqlite3_column_text(res, ORIGIN_COLUMN));
      strcpy(flightArray[i]->destination,(char*)sqlite3_column_text(res, DESTINATION_COLUMN));
      strcpy(flightArray[i]->departureTime,(char*)sqlite3_column_text(res, DEPARTURE_TIME_COLUMN));
      strcpy(flightArray[i]->arrivalTime,(char*)sqlite3_column_text(res, ARRIVAL_TIME_COLUMN));
      strcpy(flightArray[i]->planeCode,(char*)sqlite3_column_text(res, PLANE_CODE_COLUMN));
      strcpy(flightArray[i]->departureDate,(char*)sqlite3_column_text(res, DEPARTURE_DATE_COLUMN));
      strcpy(flightArray[i]->arrivalDate,(char*)sqlite3_column_text(res, ARRIVAL_DATE_COLUMN));
      i++; 
    } 
    sqlite3_finalize(res);
    flightArrayStruct = malloc(sizeof(tFlightArray));
    flightArrayStruct->flightArray = flightArray;
    flightArrayStruct->size = numberOfFlights;
    return *flightArrayStruct;
}


int getFlight(char * flight_code)
{
  char * sql = "SELECT * FROM FLIGHTS WHERE flight_code LIKE ?;";
  sqlite3_stmt * res;
  int rc;

  rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

  if(rc != SQLITE_OK)
  {
    return ERROR;
  }

  sqlite3_bind_text(res, 1, flight_code, -1, NULL);

  rc = sqlite3_step(res);

  if(rc == SQLITE_ROW)
  {
     printf("Flight Code: %s\n", sqlite3_column_text(res, 0));
     printf("Origin: %s\n", sqlite3_column_text(res, 1));
     printf("Destination: %s\n", sqlite3_column_text(res, 2));
     printf("Departure time: %s\n", sqlite3_column_text(res, 3));
     printf("Departure date: %s\n", sqlite3_column_text(res, 4));
     printf("Arrival time: %s\n", sqlite3_column_text(res, 5));
     printf("Arrival date: %s\n", sqlite3_column_text(res, 6));
     printf("Model: %s\n", sqlite3_column_text(res, 7));

  }

  sqlite3_finalize(res);
  return OK;

}

int insert_flight(char * flight_code, char * origin, char * destination, char * departure_time, char * departure_date, char * arrival_time, char * arrival_date, char * model) {

  char * sql = "INSERT INTO FLIGHTS VALUES(?,?,?,?,?,?,?,?);";
  sqlite3_stmt * res;
  int rc;
  char * err_msg;

  rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

  if(rc != SQLITE_OK)
  {
    return ERROR;
  }

  sqlite3_bind_text(res, 1, flight_code, -1, NULL);
  sqlite3_bind_text(res, 2, origin, -1, NULL);
  sqlite3_bind_text(res, 3, destination, -1, NULL);
  sqlite3_bind_text(res, 4, departure_time, -1, NULL);
  sqlite3_bind_text(res, 5, departure_date, -1, NULL);
  sqlite3_bind_text(res, 6, arrival_time, -1, NULL);
  sqlite3_bind_text(res, 7, arrival_date, -1, NULL);
  sqlite3_bind_text(res, 8, model, -1, NULL);

  rc = sqlite3_step(res);

  if(rc != SQLITE_DONE)
  {
    printf("An error has occured\n");
    return ERROR;
  }

  sqlite3_finalize(res);

  return OK;

}