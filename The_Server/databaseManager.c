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
/*
 sqlite3 *db;
 void openDataBase(){
  int rc;
    /* Open database */

/*
   rc = sqlite3_open("flightsDataBase.db", &db);
   
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
   } else {
      fprintf(stdout, "Opened database successfully\n");
   }
 }
 */
/*
void closeDataBase(){
  sqlite3_close(db);
   printf("Close database successfully\n");
 }

 */


