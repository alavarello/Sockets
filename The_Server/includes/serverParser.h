#ifndef SERVER_PARSER_H
#define SERVER_PARSER_H 

char * parseAndExecute(char * buff, int * bytes);
char * sendAllFLights( int * bytes);
char * sendFlight(char * flightCode, int * bytes);
char * sendAllPlanes( int * bytes);
char * sendAllReservations( int * bytes);
char * sendAllCancellations( int * bytes);
char * sendReservationForAFLight(char * flightCode, int * bytes);
char * sendReservation(char * flightCode, char * seat,  int * bytes);
char * insertFlight(char * buff, int * bytes);
char * insertReservation(char * buff, int * bytes);

#endif