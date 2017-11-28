#include <stdio.h>
#include <string.h>
#include "constants.h"
#include "structs.h"
#include <sqlite3.h>
#include "insertTest.h"
#include "flightsTableManager.h"
#include <assert.h>

 sqlite3 *db;

 int main(int argc, char* argv[]) {
   char *zErrMsg = 0;
   int rc;
   /* Open database */
   rc = sqlite3_open("test.db", &db);
   
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stdout, "Opened database successfully\n");
   }
  
   //INSERT TESTS
   insertFlight();
   insertSameFlight();
   insertFlightNullPK();
   
   sqlite3_close(db);
   printf("Close database successfully\n");
   return 0;
}
