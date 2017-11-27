#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <strings.h>

#define ERROR -1
#define OK 0

int insert_flight(char * flight_code, char * origin, char * destination, char * departure_time, char * departure_date, char * arrival_time, char * arrival_date, char * model);
int insert_plane(char * model, int rows, int left, int middle, int right);
int insert_reservation(char * flight_code, char * seat, char * passport, char * name, char * reservation_code);
int insert_cancellation(char * reservation);

sqlite3 * db;

int main(int argc, char const *argv[])
{

  //Main should be erased, it was only meant for testing purposes

  sqlite3_open("flights.db", &db);


  insert_plane("Boeing 777", 50, 3,2,3);
  insert_flight("AA954", "EZE", "MIA", "00:30", "01/01/2017", "04:20", "02/01/2017", "Boeing 777");
  insert_reservation("AA954", "40C", "AAA451802", "John Doe", "DWUAIT");
  insert_cancellation("DWUAIT");

  return 0;
}

int insert_plane(char * model, int rows, int left, int middle, int right)
{

  char * sql = "INSERT INTO PLANES VALUES(?,?,?,?,?);";
  sqlite3_stmt * res;
  int rc;
  char * err_msg;

  rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

  if(rc != SQLITE_OK)
  {
    return ERROR;
  }

  sqlite3_bind_text(res, 1, model, -1, NULL);
  sqlite3_bind_int(res, 2, rows);
  sqlite3_bind_int(res, 3, left);
  sqlite3_bind_int(res, 4, middle);
  sqlite3_bind_int(res, 5, right);

  rc = sqlite3_step(res);

  if(rc != SQLITE_DONE)
  {
    printf("An error has occured\n");
    return ERROR;
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

int insert_reservation(char * flight_code, char * seat, char * passport, char * name, char * reservation_code)
{

  char * sql = "INSERT INTO RESERVATIONS VALUES(?,?,?,?,?);";
  sqlite3_stmt * res;
  int rc;
  char * err_msg;

  rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

  if(rc != SQLITE_OK)
  {
    return ERROR;
  }

  sqlite3_bind_text(res, 1, flight_code, -1, NULL);
  sqlite3_bind_text(res, 2, seat, -1, NULL);
  sqlite3_bind_text(res, 3, passport, -1, NULL);
  sqlite3_bind_text(res, 4, name, -1, NULL);
  sqlite3_bind_text(res, 5, reservation_code, -1, NULL);

  rc = sqlite3_step(res);

  if(rc != SQLITE_DONE)
  {
    printf("An error has occured\n");
    return ERROR;
  }

  sqlite3_finalize(res);

  return OK;

}

int insert_cancellation(char * reservation)
{
    char * sql = "INSERT INTO CANCELATIONS SELECT * FROM RESERVATIONS WHERE reservation_code LIKE ?;";
    sqlite3_stmt * res;
    int rc;

    sqlite3_prepare_v2(db, sql, -1, &res, 0);

    sqlite3_bind_text(res, 1, reservation, -1, NULL);

    rc = sqlite3_step(res);

    if(rc != SQLITE_DONE)
    {
      printf("An error has occured\n");
      return ERROR;
    }

    sqlite3_finalize(res);

    //delete_reservation(char * reservation); Should be called to avoid data being in both tables at the same time

    return OK;

}
