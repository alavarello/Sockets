#include <stdio.h>
#include <string.h>
#include "constants.h"
#include "structs.h"
#include <sqlite3.h>
#include "insertTest.h"
#include "getTest.h"
#include <assert.h>

 sqlite3 *db;

 //gcc databaseTest.c insertTest.c getTest.c reservationAndCancelationManager.c flightsTableManager.c planesTableManager.c  -o databaseTest -lsqlite3 -std=c99

 int main(int argc, char* argv[]) {
   char *zErrMsg = 0;
   int rc, res;
   /* Open database */
   rc = sqlite3_open("test.db", &db);
   
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stdout, "Opened database successfully\n");
   }
  
   // //INSERT TESTS
   // insertFlight();
   // insertSameFlight();
   // insertFlightNullPK();
   // insertFlightWithInvalidModel();
   // insertPlane();
   // insertSamePlane();
   // insertPlaneNullPK();
   // insertReservation();
   // insertSameReservation();
   // insertReservationNullPK();
   // insertCancellation();
   // insertSameCancellation();
   // insertCancellationNullPK();

   //GET ELEMENTS FROM DATABASE. THIS TEST USE INSERT
   getPlaneArrayWith0Elements();
   getPlaneArrayWith1Element();
   getPlaneArrayTest();

   getFlightArrayWith0Elements();
   getFlightArrayWith1Element();
   getFlightArrayTest();
   getExistingFlight();
   getFlightThatDoesntExist();

   getReservationArrayWith0Elements();
   getReservationArrayWith1Element();
   getReservationArrayTest();
   getExistingReservation();
   getReservationThatDoesntExist();

   getSeatArrayWith0Elements();
   getSeatArrayWith1Element();
   getSeatArrayTest();

   
   sqlite3_close(db);
   printf("Close database successfully\n");
   return 0;
}
