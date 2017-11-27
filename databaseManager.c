#include <sqlite3.h>
#include <stdio.h>


//for compilation gcc databse.c -o database -lsqlite3 -std=c99
//for executing the database in the terminal sqlite3

sqlite3 *db;

#define FLIGHT_ARRAY_BITS_EXPANSION (sizeof(tFlight*)*FLIGHT_ARRAY_NUMBER_EXPANSION);
#define FLIGHT_ARRAY_NUMBER_EXPANSION 7;

#define FLIGHT_CODE_COLUMN 0; 
#define ORIGIN_COLUMN 1; 
#define DESTINATION_COLUMN 2;
#define DEPARTURETIME_COLUMN 3; 
#define ARRIVAL_TIME_COLUMN 4;
#define PLANE_CODE 5;


#define MODEL_COLUMN 0; 
#define ROWS_COLUMN 1; 
#define LEFT_COLUMN 2; 
#define MIDDLE_COLUMN 3; 
#define RIGHT_COLUMN 4; 

#define FLIGHT_CODE_COLUMN 0; 
#define SEAT_NUMBER_COLUMN 1; 
#define PASSPORT_COLUMN 2; 
#define USER_NAME_COLUMN 3; 
#define RESERVATION_CODE_COLUMN 4;


typedef struct {
	char flightCode[6];
	char* origin;
	char* destination;
	char departureTime[6];
	char arrivalTime[6];
	char planeCode[6];  

} tFlight; 


typedef struct{
	tFlight ** flightArray;
	long size;
}tFlighArray;

typedef struct {
	char* model;
	int rows;
	int left;
	int middle;
	int right;
}tPlain;

//supports (2^(64)-1) reservations 
typedef struct {
	char flightCode[6];
	char seatNumber[4];
	char* passport;
	char* userName;
	unsigned long long int reservationCode;
}tReservation;


tFlight** expandFLightArray(tFlight ** flightArray, long size){
	int i;
	flightArray = realloc(flightArray, FLIGHT_ARRAY_EXPANSION);

	for(i = 0; i < size, i++){
		flightArray[i] = malloc(sizeof(tFlight));
	}
	return flightArray;
}

int getNumberOfFLighst(){
	int rc, numberOfFlights;
	sqlite3_stmt *res;
	//getting the number of flights
    char * sqlFLightCount = "SELECT count(*) FROM flight"
     rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (rc == SQLITE_OK) {   
        sqlite3_bind_int(res, 1, 3);
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    return sqlite3_column_int(res, 0);
}


tFlighArray getFLightArray(){
	char *err_msg = 0;
    sqlite3_stmt *res;
    tFlight** flightArray = NULL; 
    int rc, numberOfFlights, i;
    tFlighArray flightArrayStruct;


    //ESTO tiene que ser atomico;
    numberOfFlights = getNumberOfFLighst();


    //getting the flights
    char *sql = "SELECT * FROM flight";
       
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
   
    if (rc == SQLITE_OK) {
        
        sqlite3_bind_int(res, 1, 3);
    } else {
        
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    //------------------
   	
   	flightArray = expandFLightArray(flightArray, numberOfFlights);
    i = 0;
    while(sqlite3_step(res) == SQLITE_ROW) {
      flightArray[i] = sqlite3_column_text(res, FLIGHT_CODE_COLUMN);
      flightArray[i] = sqlite3_column_text(res, ORIGIN_COLUMN);
      flightArray[i] = sqlite3_column_text(res, DESTINATION_COLUMN);
      flightArray[i] = sqlite3_column_text(res, DEPARTURETIME_COLUMN);
      flightArray[i] = sqlite3_column_text(res, ARRIVAL_TIME_COLUMN);
      flightArray[i] = sqlite3_column_text(res, PLANE_CODE);
      i++; 
    } 

    sqlite3_finalize(res);
    sqlite3_close(db);
    flightArrayStruct = malloc(sizeof(tFlighArray));
    flightArrayStruct.flightArray = flightArray;
    flightArrayStruct.size = numberOfFlights;
    return flightArrayStruct;
}




int main(int argc, char* argv[]) {
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *createVuelo;

   /* Open database */
   rc = sqlite3_open("test.db", &db);
   
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stdout, "Opened database successfully\n");
   }

   /* Create SQL statement */
   sql = "CREATE TABLE COMPANY("  \
         "ID INT PRIMARY KEY     NOT NULL," \
         "NAME           TEXT    NOT NULL," \
         "AGE            INT     NOT NULL," \
         "ADDRESS        CHAR(50)," \
         "SALARY         REAL );";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Table created successfully\n");
   }
   sqlite3_close(db);
   return 0;
}
