//structs.h

#ifndef STRUCTS_H
#define STRUCTS_H

#define FLIGHT_CODE_COLUMN 0
#define ORIGIN_COLUMN 1
#define DESTINATION_COLUMN 2
#define DEPARTURETIME_COLUMN 3
#define ARRIVAL_TIME_COLUMN 4
#define PLANE_CODE 5

#define MAX_BUFFER 100


#define MODEL_COLUMN 0 
#define ROWS_COLUMN 1 
#define LEFT_COLUMN 2 
#define MIDDLE_COLUMN 3 
#define RIGHT_COLUMN 4 

#define FLIGHT_CODE_COLUMN 0 
#define SEAT_NUMBER_COLUMN 1
#define PASSPORT_COLUMN 2
#define USER_NAME_COLUMN 3
#define RESERVATION_CODE_COLUMN 4
#define MAX_FLIGHTS 200

#define CLEAN_BUFFER while(getchar()!='\n')

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

