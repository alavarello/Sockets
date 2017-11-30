#include <sqlite3.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "reservationAndCancelationManager.h"
#include "planesTableManager.h"
#include "flightsTableManager.h"


void getFlightArrayWith0Elements(){
	tFlightArray * t = getFlightArray();
	assert(t->size == 0);
	assert(t->flightArray != NULL);
	printf("GET FLIGHT ARRAY WITH 0 ELEMENTS TEST: OK\n");
}
void getFlightArrayWith1Element(){
	insert_flight("AA954", "EZE", "MIA", "00:30", "01/01/2017", "04:20", "02/01/2017", "Boeing 777");
	tFlightArray * t = getFlightArray();
	assert(t->size == 1);
	assert(t->flightArray != NULL);
	assert(strcmp(t->flightArray[0]->flightCode, "AA954") == 0);
	printf("GET FLIGHT ARRAY WITH 1 ELEMENTS TEST: OK\n");
}
void getFlightArrayTest(){
	insert_flight("AA955", "EZE", "MIA", "00:30", "01/01/2017", "04:20", "02/01/2017", "Boeing 777");
	insert_flight("AA956", "EZE", "MIA", "00:30", "01/01/2017", "04:20", "02/01/2017", "Boeing 777");
	insert_flight("AA957", "EZE", "MIA", "00:30", "01/01/2017", "04:20", "02/01/2017", "Boeing 777");
	insert_flight("AA958", "EZE", "MIA", "00:30", "01/01/2017", "04:20", "02/01/2017", "Boeing 777");
	insert_flight("AA959", "EZE", "MIA", "00:30", "01/01/2017", "04:20", "02/01/2017", "Boeing 777");
	tFlightArray * t = getFlightArray();
	assert(t->size == 6); //cunting the one in the getPlaneArrayWith1Element
	assert(t->flightArray != NULL);
	assert(strcmp(t->flightArray[0]->flightCode, "AA954") == 0);
	assert(strcmp(t->flightArray[1]->flightCode, "AA955") == 0);
	assert(strcmp(t->flightArray[2]->flightCode, "AA956") == 0);
	assert(strcmp(t->flightArray[3]->flightCode, "AA957") == 0);
	assert(strcmp(t->flightArray[4]->flightCode, "AA958") == 0);
	assert(strcmp(t->flightArray[5]->flightCode, "AA959") == 0);
	printf("GET FLIGHT ARRAY TEST: OK\n");

}


void getExistingFlight(){
	insert_flight("BB300", "EZE", "MIA", "00:30", "01/01/2017", "04:20", "02/01/2017", "Boeing 777");
	tFlight * t = getFlight("BB300");
	assert(t != NULL);
	assert(strcmp(t->flightCode, "BB300") == 0);
	printf("GET EXISTING FLIGHT  TEST: OK\n");
}
void getFlightThatDoesntExist(){
	tFlight * t = getFlight("ssss");
	assert(t == NULL);
	printf("GET FLIGHT THAT DOESN'T EXIST TEST: OK\n");
}


void getPlaneArrayWith0Elements(){
	tPlaneArray * t = getPlaneArray();
	assert(t->size == 0);
	assert(t->planeArray != NULL);
	printf("GET PLANE ARRAY WITH 0 ELEMENTS TEST: OK\n");
}
void getPlaneArrayWith1Element(){
	insert_plane("Boeing 777", 50, 3, 2, 3);
	tPlaneArray * t = getPlaneArray();
	assert(t->size == 1);
	assert(t->planeArray != NULL);
	assert(strcmp(t->planeArray[0]->model, "Boeing 777") == 0);
	printf("GET PLANE ARRAY WITH 1 ELEMENTS TEST: OK\n");
}
void getPlaneArrayTest(){
	insert_plane("Boeing 778", 50, 3, 2, 3);
	insert_plane("Boeing 779", 50, 3, 2, 3);
	insert_plane("Boeing 780", 50, 3, 2, 3);
	tPlaneArray * t = getPlaneArray();
	assert(t->size == 4);
	assert(t->planeArray != NULL);
	assert(strcmp(t->planeArray[0]->model, "Boeing 777") == 0);
	assert(strcmp(t->planeArray[1]->model, "Boeing 778") == 0);
	assert(strcmp(t->planeArray[2]->model, "Boeing 779") == 0);
	assert(strcmp(t->planeArray[3]->model, "Boeing 780") == 0);
	printf("GET PLANE ARRAY TEST: OK\n");
}


void getReservationArrayWith0Elements(){
	tReservationArray * t = getReservationArray();
	assert(t->size == 0);
	assert(t->reservationsArray != NULL);
	printf("GET RESERVATION ARRAY WITH 0 ELEMENTS TEST: OK\n");
}
void getReservationArrayWith1Element(){
	insert_reservation("AR1364","01A", "John Doe");
	tReservationArray * t = getReservationArray();
	assert(t->size == 1);
	assert(t->reservationsArray != NULL);
	printf("GET RESERVATION ARRAY WITH 1 ELEMENTS TEST: OK\n");
}
void getReservationArrayTest(){
	insert_reservation("AR1364","01B", "John Doe");
	insert_reservation("AR1364","01C", "John Doe");
	insert_reservation("AR1364","01D", "John Doe");
	tReservationArray * t = getReservationArray();
	assert(t->size == 4);
	assert(t->reservationsArray != NULL);
	assert(strcmp(t->reservationsArray[0]->flightCode, "AR1364") == 0);
	assert(strcmp(t->reservationsArray[0]->flightCode, "AR1364") == 0);
	assert(strcmp(t->reservationsArray[0]->flightCode, "AR1364") == 0);
	assert(strcmp(t->reservationsArray[0]->flightCode, "AR1364") == 0);
	printf("GET RESERVATION ARRAY TEST: OK\n");

}

void getExistingReservation(){
	insert_reservation("ZZ136","01B", "John Doe");
	tReservation *  t = getReservation("ZZ136","01B");
	assert(t != NULL);
	assert(t->flightCode != "ZZ136");
	assert(t->seatNumber != "01B");
	printf("GET EXISTING RESERVATION TEST: OK\n");

}
void getReservationThatDoesntExist(){
	tReservation *  t = getReservation("ZZ136","01Z");
	assert(t == NULL);
	printf("GET RESERVATION THAT DOESN'T EXIST TEST: OK\n");
}

void getSeatArrayWith0Elements(){
	tSeatsArray * t = getReservationsSeats("DD456");
	assert(t->size == 0);
	assert(t->reservedSeats != NULL);
	printf("GET SEAT ARRAY WITH 0 ELEMENTS TEST: OK\n");
}
void getSeatArrayWith1Element(){
	insert_flight("DD456", "EZE", "MIA", "00:30", "01/01/2017", "04:20", "02/01/2017", "Boeing 777");
	insert_reservation("DD456","01A", "John Doe");
	tSeatsArray * t = getReservationsSeats("DD456");
	assert(t->size == 1);
	assert(t->reservedSeats != NULL);
	printf("GET SEAT ARRAY WITH 1 ELEMENTS TEST: OK\n");

}
void getSeatArrayTest(){
	insert_reservation("DD456","40B", "John Doe");
	insert_reservation("DD456","05C", "John Doe");
	insert_reservation("DD456","01D", "John Doe");
	tSeatsArray * t = getReservationsSeats("DD456");
	assert(t->size == 4);
	assert(t->reservedSeats != NULL);
	assert(strcmp(t->reservedSeats[0], "01A") == 0);
	assert(strcmp(t->reservedSeats[1], "01D") == 0);
	assert(strcmp(t->reservedSeats[2], "05C") == 0);
	assert(strcmp(t->reservedSeats[3], "40B") == 0);
	printf("GET SEAT ARRAY  TEST: OK\n");
}




