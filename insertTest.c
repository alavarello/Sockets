
#include <sqlite3.h>
#include <stdio.h>
#include <assert.h>

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

}	

void insertPlane(){

}

void insertSamePlane(){

}

void insertPlaneNullPK(){

}

void insertReservation(){

}

void insertSameReservation(){

}

void insertReservationNullPK(){

}

void insertReservationWithInvalidFlightCode(){

}


void insertCancelation(){

}

void insertSameCancelation(){

}

void insertCancelationNullPK(){

}

void insertCancelationWithInvalidFlightCode(){

}







