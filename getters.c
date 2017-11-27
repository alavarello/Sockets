#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <strings.h>

#define ERROR -1
#define OK 0

sqlite3 * db;
int getFlight(char * flight_code);
int getReservation(char * reservation_code);

int main(int argc, char const *argv[])
{

  //Main should be erased, it was only meant for testing purposes

  sqlite3_open("flights.db", &db); //Change database name to your database to test

  getFlight("AA954"); //Getting the flight with flight code AA954
  getReservation("DWUAIT"); //Getting the reservation with reservation code DWUAIT

  return 0;
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

int getReservation(char * reservation_code)
{
  char * sql = "SELECT * FROM RESERVATIONS WHERE reservation_code LIKE ?;";
  sqlite3_stmt * res;
  int rc;

  rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

  if(rc != SQLITE_OK)
  {
    return ERROR;
  }

  sqlite3_bind_text(res, 1, reservation_code, -1, NULL);

  rc = sqlite3_step(res);

  if(rc == SQLITE_ROW)
  {
    printf("Flight Code: %s\n", sqlite3_column_text(res, 0));
    printf("Seat: %s\n", sqlite3_column_text(res, 1));
    printf("Passport: %s\n", sqlite3_column_text(res, 2));
    printf("Name: %s\n", sqlite3_column_text(res, 3));
    printf("Reservation Code: %s\n", sqlite3_column_text(res, 4));
  }

   sqlite3_finalize(res);
   return OK;

}
