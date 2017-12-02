//structs.h

#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct {
	char* flightCode;
	char* origin;
	char* destination;
	char* departureTime;
  char* departureDate;
	char* arrivalTime;
  char* arrivalDate;
	char* planeCode;  

} tFlight; 


typedef struct{
	tFlight ** flightArray;
	long size;
}tFlightArray;

typedef struct {
	char* model;
	int rows;
	int left;
	int middle;
	int right;
}tPlane;

typedef struct{
  tPlane ** planeArray;
  long size;
}tPlaneArray;



typedef struct {
	char* flightCode;
	char* seatNumber;
	char* userName;
}tReservation;

typedef struct{
  tReservation ** reservationsArray;
  long size;
}tReservationArray;


typedef struct {
	char ** reservedSeats;
	int size;
}tSeatsArray;

#endif