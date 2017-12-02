#include "constants.h"
#include <sqlite3.h>
#include "structs.h"
#include "reservationAndCancelationManager.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include "semaphores.h"
#include <semaphore.h>
#include <string.h>

#define NUMBER_OF_SEATS_TO_EXPAND 10

extern sqlite3 *db;

tReservation** expanReservationArray(tReservation** reservationsArray, long size)
{
  int i;
  reservationsArray = malloc(size*sizeof(tReservation*));
  for(i=0; i<size; i++)
  {
    reservationsArray[i] = malloc(sizeof(tReservation));
    reservationsArray[i]->flightCode = malloc(sizeof(char)*FLIGHT_CODE_CHAR_MAX);
    reservationsArray[i]->seatNumber = malloc(sizeof(char)*SEAT_NUMBER_CHAR_MAX);
    reservationsArray[i]->userName = malloc(sizeof(char)*USER_NAME_CHAR_MAX);
  }
  return reservationsArray;
}

char ** exapndSeatsArray(char** seatsArray, int* size)
{
  int i;
  (*size) += NUMBER_OF_SEATS_TO_EXPAND;
  seatsArray = reallocf(seatsArray, (*size)*sizeof(char*));
  if(seatsArray == NULL)
  {
    return NULL;
    //Free and size back to how it was before
  }
  for(i = ((*size) - NUMBER_OF_SEATS_TO_EXPAND ); i< NUMBER_OF_SEATS_TO_EXPAND; i++){
    seatsArray[i] = malloc(sizeof(char)*SEAT_NUMBER_CHAR_MAX);
  }
  return seatsArray;
}

tSeatsArray * getReservationsSeats(char * flightCode)
{
  int rc, numberOfRowsInTable, size = 0, aux = 0;
  sqlite3_stmt *res;
  tSeatsArray * seatsArrayStruct = malloc(sizeof(tSeatsArray));
  char ** seatsArray = NULL;
  char *sql ="SELECT seat FROM RESERVATIONS NATURAL JOIN FLIGHTS WHERE flight_code = ?";
  rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
  if(rc != SQLITE_OK)
  {
    fprintf(stderr, "%s\n",sqlite3_errmsg(db));
    return NULL;
  }
  sqlite3_bind_text(res, 1, flightCode, -1, NULL);
  seatsArray = exapndSeatsArray(seatsArray, &size);
  while(sqlite3_step(res) == SQLITE_ROW){
    if(size==aux)
    {
      seatsArray = exapndSeatsArray(seatsArray, &size);
    }
    strcpy(seatsArray[aux] ,(char*)sqlite3_column_text(res, 0));
    aux++;
  }
  if(size==aux)
  {
    seatsArray=exapndSeatsArray(seatsArray, &size);
  }
  seatsArrayStruct->reservedSeats = seatsArray;
  seatsArrayStruct->size = aux;
  return seatsArrayStruct;
}

int getNumberOfReservationOrCancelations(char* table)
{
  int rc, numberOfRowsInTable;
  sqlite3_stmt *res;
  //getting the number of flights
  char *sqlPlaneCount;
  if(!strcmp(table, "RESERVATIONS"))
  {
    sqlPlaneCount = "SELECT count(*) FROM RESERVATIONS";
  }
  else
  {
    sqlPlaneCount = "SELECT count(*) FROM CANCELATIONS";
  }
  
    rc = sqlite3_prepare_v2(db, sqlPlaneCount, -1, &res, 0);
    if(rc != SQLITE_OK)
  {
    fprintf(stderr, "%s\n",sqlite3_errmsg(db));
    return -1;
  }
    sqlite3_bind_text(res, 1, table, -1, NULL);
    sqlite3_step(res);
    numberOfRowsInTable = sqlite3_column_int(res, 0);
    sqlite3_finalize(res);
    return numberOfRowsInTable;
}

tReservationArray * getReservationOrCancelationArray(char* table){
  char *err_msg = 0;
  sqlite3_stmt * res;
  tReservation** reservationsArray = NULL;
  tReservationArray* reservationsArrayStruct; 
  int rc, numberOfRowsInTable, i;

  sem_t * sem;
  char *sql;
  if(!strcmp(table, "RESERVATIONS"))
  {
    sql = "SELECT * FROM RESERVATIONS";
    sem = openSemaphore(RESERVATION_SEMAPHORE);
    sem_wait(sem);
  }
  else
  {
    sql = "SELECT * FROM CANCELATIONS";
    sem = openSemaphore(CANCELLATION_SEMAPHORE);
    sem_wait(sem);
  }
  numberOfRowsInTable = getNumberOfReservationOrCancelations(table);
  if(numberOfRowsInTable == -1)
  {
      return NULL;
  }
  
  rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
  //----------------------

  if(rc != SQLITE_OK)
  {
    fprintf(stderr, "%s\n",sqlite3_errmsg(db));
    return NULL;
  }

  reservationsArray = expanReservationArray(reservationsArray, numberOfRowsInTable);
  i = 0;
  while(sqlite3_step(res) == SQLITE_ROW) 
  {
    strcpy(reservationsArray[i]->flightCode ,(char*)sqlite3_column_text(res, FLIGHT_CODE_COLUMN));
    strcpy(reservationsArray[i]->seatNumber ,(char*)sqlite3_column_text(res, SEAT_NUMBER_COLUMN));
    strcpy(reservationsArray[i]->userName ,(char*)sqlite3_column_text(res, USER_NAME_COLUMN));
    i++;
  }

  sqlite3_finalize(res);
  sem_post(sem);
  reservationsArrayStruct = malloc(sizeof(tReservationArray));
  reservationsArrayStruct->size = numberOfRowsInTable;
  reservationsArrayStruct->reservationsArray = reservationsArray;
  return reservationsArrayStruct;

}

void printReservationArray(tReservationArray reservationsArray)
{
  int i;
  printf("RESERVATION ARRAY: SIZE:%d\n",reservationsArray.size);
  for (i = 0; i < reservationsArray.size; ++i)
  {
   printf("FC:%s\n",reservationsArray.reservationsArray[i]->flightCode);
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

tReservationArray * getReservationArray()
{
  return getReservationOrCancelationArray("RESERVATIONS");
}

tReservationArray * getCancelationArray()
{
 return getReservationOrCancelationArray("CANCELATIONS");
}


tReservation * getReservation(char * flightCode, char * seat)
{
  char * sql = "SELECT * FROM RESERVATIONS WHERE flight_code LIKE ? AND seat LIKE ?;";
  sqlite3_stmt * res;
  int rc;
  tReservation * reservation = malloc(sizeof(tReservation));
  reservation->flightCode = malloc(sizeof(char)*FLIGHT_CODE_CHAR_MAX);
  reservation->seatNumber = malloc(sizeof(char)*SEAT_NUMBER_CHAR_MAX);
  reservation->userName = malloc(sizeof(char)*USER_NAME_CHAR_MAX);
  rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

  if(rc != SQLITE_OK)
  {
    fprintf(stderr, "%s\n",sqlite3_errmsg(db));
    return NULL;
  }

  sqlite3_bind_text(res, 1, flightCode, -1, NULL);
  sqlite3_bind_text(res, 2, seat, -1, NULL);
  rc = sqlite3_step(res);

  if(rc == SQLITE_ROW)
  { 
    strcpy(reservation->flightCode ,(char*)sqlite3_column_text(res, FLIGHT_CODE_COLUMN));
    strcpy(reservation->seatNumber ,(char*)sqlite3_column_text(res, SEAT_NUMBER_COLUMN));
    strcpy(reservation->userName ,(char*)sqlite3_column_text(res, USER_NAME_COLUMN));
  }
  else if(rc == SQLITE_DONE)
  {
    //THERE IS NO RESERVATION
    return NULL;
  }
  else
  {
    fprintf(stderr, "%s\n",sqlite3_errmsg(db));
    return NULL;
  }

   sqlite3_finalize(res);
   return reservation;

}


int insert_reservation(char * flight_code, char * seat, char * name)
{

  char * sql = "INSERT INTO RESERVATIONS VALUES(?,?,?);";
  sqlite3_stmt * res;
  int rc;
  char * err_msg;
  sem_t * sem;

  sem = openSemaphore(RESERVATION_SEMAPHORE);
  sem_wait(sem);

  rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

  if(rc != SQLITE_OK)
  {
    fprintf(stderr, "%s\n",sqlite3_errmsg(db));
    return sqlite3_errcode(db);
  }

  sqlite3_bind_text(res, 1, flight_code, -1, NULL);
  sqlite3_bind_text(res, 2, seat, -1, NULL);
  sqlite3_bind_text(res, 3, name, -1, NULL);
  
  rc = sqlite3_step(res);

  if(rc != SQLITE_DONE)
  {
    fprintf(stderr, "%s\n",sqlite3_errmsg(db));
    return sqlite3_errcode(db);
  }

  sqlite3_finalize(res);
  sem_post(sem);
  sem_close(sem);
  return SQLITE_OK;

}

int delete_reservation(char * flight_code, char * seat){
  char * sql = "DELETE FROM RESERVATIONS WHERE seat LIKE ? AND flight_code LIKE ?;";
  sqlite3_stmt * res;
  int rc;
  sem_t * sem;
  sem = openSemaphore(RESERVATION_SEMAPHORE);
  sem_wait(sem);



  rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

  if(rc != SQLITE_OK)
  {
    fprintf(stderr, "%s\n",sqlite3_errmsg(db));
    return sqlite3_errcode(db);
  }

  sqlite3_bind_text(res, 2, flight_code, -1, NULL);
  sqlite3_bind_text(res, 1, seat, -1, NULL);
  rc = sqlite3_step(res);

  if(rc != SQLITE_DONE)
  {
    fprintf(stderr, "%s\n",sqlite3_errmsg(db));
    return sqlite3_errcode(db);
  }

  sqlite3_finalize(res);
}


int insert_cancellation(char * seat, char * flightCode)
{
  char * sql = "INSERT INTO CANCELATIONS SELECT * FROM RESERVATIONS WHERE seat LIKE ? AND flight_code LIKE ?;";
  sqlite3_stmt * res;
  int rc;
  sem_t * sem;

  sem = openSemaphore(CANCELLATION_SEMAPHORE);
  sem_wait(sem);
  sqlite3_prepare_v2(db, sql, -1, &res, 0);

  if(rc != SQLITE_OK)
  {
    fprintf(stderr, "%s\n",sqlite3_errmsg(db));
    return sqlite3_errcode(db);
  }
  sqlite3_bind_text(res, 1, seat, -1, NULL);
  sqlite3_bind_text(res, 2, flightCode, -1, NULL);

  rc = sqlite3_step(res);

  if(rc != SQLITE_DONE)
  {
    fprintf(stderr, "%s\n",sqlite3_errmsg(db));
    return sqlite3_errcode(db);
  }

  sqlite3_finalize(res);
  sem_post(sem);
  sem_close(sem);
  delete_reservation(flightCode, seat);// Should be called to avoid data being in both tables at the same time

  return SQLITE_OK;

}