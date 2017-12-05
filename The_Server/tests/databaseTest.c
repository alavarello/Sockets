#include <stdio.h>
#include <string.h>
#include "constants.h"
#include "structs.h"
#include <sqlite3.h>
#include "insertTest.h"
#include "getTest.h"
#include <assert.h>

 sqlite3 *db;

 void deleteFLights(){
   int rc, numberOfFlights;
   sqlite3_stmt *res;
   //getting the number of flights
    char * sqlFLightCount = "DELETE FROM FLIGHTS;";
    rc = sqlite3_prepare_v2(db, sqlFLightCount, -1, &res, 0);
     if(rc != SQLITE_OK)
    {
      fprintf(stderr, "%s\n",sqlite3_errmsg(db));
      return;
    }
    sqlite3_step(res);
    numberOfFlights = sqlite3_column_int(res, 0);
    sqlite3_finalize(res);
    return;
 }

 void deletePlanes(){
   int rc, numberOfFlights;
   sqlite3_stmt *res;
   //getting the number of flights
    char * sqlFLightCount = "DELETE FROM PLANES;";
    rc = sqlite3_prepare_v2(db, sqlFLightCount, -1, &res, 0);
     if(rc != SQLITE_OK)
    {
      fprintf(stderr, "%s\n",sqlite3_errmsg(db));
      return;
    }
    sqlite3_step(res);
    numberOfFlights = sqlite3_column_int(res, 0);
    sqlite3_finalize(res);
    return;
}
void deleteReservations(){
   int rc, numberOfFlights;
   sqlite3_stmt *res;
   //getting the number of flights
    char * sqlFLightCount = "DELETE FROM RESERVATIONS;";
    rc = sqlite3_prepare_v2(db, sqlFLightCount, -1, &res, 0);
     if(rc != SQLITE_OK)
    {
      fprintf(stderr, "%s\n",sqlite3_errmsg(db));
      return;
    }
    sqlite3_step(res);
    numberOfFlights = sqlite3_column_int(res, 0);
    sqlite3_finalize(res);
    return;
}
void deleteCancelations(){
   int rc, numberOfFlights;
   sqlite3_stmt *res;
   //getting the number of flights
    char * sqlFLightCount = "DELETE FROM CANCELATIONS;";
    rc = sqlite3_prepare_v2(db, sqlFLightCount, -1, &res, 0);
     if(rc != SQLITE_OK)
    {
      fprintf(stderr, "%s\n",sqlite3_errmsg(db));
      return;
    }
    sqlite3_step(res);
    numberOfFlights = sqlite3_column_int(res, 0);
    sqlite3_finalize(res);
    return;
}

 void deleteTablesValues(){
   deleteCancelations();
   deleteReservations();
   deletePlanes();
   deleteFLights();
 }

 int main(int argc, char* argv[]) {
   int rc;
   /* Open database */
   rc = sqlite3_open("test.db", &db);
   
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stdout, "Opened database successfully\n");
   }
   printf("ANTES\n");
   deleteTablesValues();
   printf("DESPUES\n");
   //INSERT TESTS
   insertFlight();
   insertSameFlight();
   insertFlightNullPK();
   insertFlightWithInvalidModel();
   insertPlane();
   insertSamePlane();
   insertPlaneNullPK();
   insertReservation();
   insertSameReservation();
   insertReservationNullPK();
   insertCancellation();

   deleteTablesValues();

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
