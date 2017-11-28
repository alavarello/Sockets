#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "constants.h"
#include "planesTableManager.h"
#include "flightsTableManager.h"
#include "reservationAndCancelationManager.h"
#include "structs.h"

//gcc databaseManager.c planesTableManager.c flightsTableManager.c reservationAndCancelationManager.c -o databaseManager  -lsqlite3 -std=c99

//for insatling the database in the terminal:
//sqlite3 flightsDataBase.db
//.read script.sql
//For inserting values in the terminal:
//sqlite3 flightsDataBase.db
//.read insert_data.sql
//For removing values in the terminal:
//sqlite3 flightsDataBase.db
//.read delete.sql
//For removing the tables in the terminal:
//sqlite3 flightsDataBase.db
//.read drop.sql

//.exit for exiting the sqlite3 terminal



 sqlite3 *db;

int main(int argc, char* argv[]) {
   char *zErrMsg = 0;
   int rc;
   char *createVuelo;
   tFlightArray flightArray;
   tPlaneArray planeArray;
   tReservationArray reservationsArray;

   /* Open database */
   rc = sqlite3_open("flightsDataBase.db", &db);
   
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stdout, "Opened database successfully\n");
   }
  
  // insert_plane("Boeing 777", 50, 3,2,3);
  // insert_flight("AA954", "EZE", "MIA", "00:30", "01/01/2017", "04:20", "02/01/2017", "Boeing 777");
  // insert_reservation("AA954", "30C", "AAA451802", "John Doe", "DWUAIP");
  // insert_reservation("AA954", "41C", "AAA451802", "John Doe", "DWUAIR");
  // insert_reservation("AA954", "4C", "AAA451802", "John Doe", "DWUAIS");
  // insert_reservation("AA954", "1C", "AAA451802", "John Doe", "DWUAID");
  // insert_reservation("AA954", "40A", "AAA451802", "John Doe", "DWUANT");
  // insert_reservation("AA954", "40B", "AAA451802", "John Doe", "DWUAIL");
  // insert_reservation("AA954", "40D", "AAA451802", "John Doe", "DWUAIA");
  // insert_reservation("AA954", "29E", "AAA451802", "John Doe", "DWUAIQ");
  getReservationsSeats("AA954");

  // insert_cancellation("DWUAIT");
  // getFlight("AA954"); //Getting the flight with flight code AA954
  // getReservation("DWUAIT"); //Getting the reservation with reservation code DWUAIT
   
  // flightArray = getFlightArray();
  // printFlightArray(flightArray);

  // planeArray = getPlaneArray();
  // printPlaneArray(planeArray);

  // reservationsArray = getReservationArray();
  // printReservationArray(reservationsArray);

  // reservationsArray = getCancelationArray();
  // printReservationArray(reservationsArray);

   
   sqlite3_close(db);
   printf("Close database successfully\n");
   return 0;
}
