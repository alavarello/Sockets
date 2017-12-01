#ifndef STRUCTS_H
#define STRUCTS_H

#define FLIGHT_CODE_COLUMN 0
#define ORIGIN_COLUMN 1
#define DESTINATION_COLUMN 2
#define DEPARTURETIME_COLUMN 3
#define ARRIVAL_TIME_COLUMN 4
#define PLANE_CODE 5}

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
#define MAX_FLIGHTS 50

#define CLEAN_BUFFER while(getchar()!='\n')


typedef struct {
	char * flightCode;
	char * origin;
	char * destination;
	char * departureTime;
	char * arrivalTime;
	char * planeCode;
	char * departureDate;
	char * arrivalDate;  

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
}tPlane;

//supports (2^(64)-1) reservations 
typedef struct {
	char flightCode[6];
	char seatNumber[4];
	char* passport;
	char* userName;
	unsigned long long int reservationCode;
}tReservation;

#endif
