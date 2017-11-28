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


//supports (2^(64)-1) reservations 
typedef struct {
	char* flightCode;
	char* seatNumber;
	char* passport;
	char* userName;
	char* reservationCode;
}tReservation;

typedef struct{
  tReservation ** reservationsArray;
  long size;
}tReservationArray;

#endif