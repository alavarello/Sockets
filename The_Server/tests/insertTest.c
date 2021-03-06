
#include <sqlite3.h>
#include <stdio.h>
#include <assert.h>
#include "reservationAndCancelationManager.h"
#include "planesTableManager.h"
#include "flightsTableManager.h"

void insertFlight(){
 int res = insert_flight("AA954", "EZE", "MIA", "00:30", "01/01/2017", "04:20", "02/01/2017", "Boeing 777");
 assert(res==SQLITE_OK);
 printf("INSERT FLIGHT TEST: OK\n");
}

void insertSameFlight(){
insert_flight("AA955", "EZE", "MIA", "00:30", "01/01/2017", "04:20", "02/01/2017", "Boeing 777");
int res = insert_flight("AA955", "EZE", "MIA", "00:30", "01/01/2017", "04:20", "02/01/2017", "Boeing 777");
assert(res==SQLITE_CONSTRAINT);
printf("INSERT SAME FLIGHT TEST: OK\n");
}

void insertFlightNullPK(){
	int res = insert_flight(NULL, "EZE", "MIA", "00:30", "01/01/2017", "04:20", "02/01/2017", "Boeing 777");
	assert(res==SQLITE_CONSTRAINT);
	printf("INSERT FLIGHT NULL PK TEST: OK\n");
}

void insertFlightWithInvalidModel(){
	int res = insert_flight(NULL, "EZE", "MIA", "00:30", "01/01/2017", "04:20", "02/01/2017", "HFJfiwoj");
	assert(res==SQLITE_CONSTRAINT);
	printf("INSERT FLIGHT WITH INVALID MODEL TEST: OK\n");
}	

void insertPlane(){
	int res = insert_plane("Boeing 777", 50, 3, 2, 3);
	assert(res==SQLITE_OK);
 	printf("INSERT PLANE TEST: OK\n");
}

void insertSamePlane(){
	int res = insert_plane("Boeing 444", 50, 3, 2, 3);
	assert(res==SQLITE_OK);
	res = insert_plane("Boeing 444", 50, 3, 2, 3);
	assert(res==SQLITE_CONSTRAINT);
 	printf("INSERT SAME PLANE TEST: OK\n");
}

void insertPlaneNullPK(){
	int res = insert_plane(NULL, 50, 3, 2, 3);
	assert(res==SQLITE_CONSTRAINT);
 	printf("INSERT PLANE NULL PK TEST: OK\n");
}

void insertReservation(){
	int res = insert_reservation("AR136","01A", "John Doe");
	assert(res==SQLITE_OK);
 	printf("INSERT RESERVATION TEST: OK\n");
}

void insertSameReservation(){
	int res = insert_reservation("AR136","01B", "John Doe");
	assert(res==SQLITE_OK);
	res = insert_reservation("AR136","01B", "John Doe");

	assert(res==SQLITE_CONSTRAINT_PRIMARYKEY);
 	printf("INSERT SAME RESERVATION TEST: OK\n");
}

void insertReservationNullPK(){
	int res = insert_reservation(NULL,"01B", "John Doe");
	assert(res==SQLITE_CONSTRAINT_NOTNULL);
	res = insert_reservation("AR1364",NULL, "John Doe");
	assert(res==SQLITE_CONSTRAINT_NOTNULL);
	res = insert_reservation(NULL,NULL, "John Doe");
	assert(res==SQLITE_CONSTRAINT_NOTNULL);
	printf("INSERT RESERVATION NULL PK TEST: OK\n");
}


void insertCancellation(){
	insert_reservation("AR136","01C", "John Doe");
	int res = insert_cancellation("AR136","01C");
	assert(res==SQLITE_OK);
 	printf("INSERT CANCELATION TEST: OK\n");
}









