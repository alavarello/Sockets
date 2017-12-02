#ifndef SERVER_PARSER_H
#define SERVER_PARSER_H 

char * parseAndExecute(char * buff);
char * sendAllFLights();
char * sendFlight(char * flightCode);
char * sendAllPlanes();
char * sendAllReservations();
char * sendAllCancellations();
char * sendReservationForAFLight(char * flightCode);
char * sendReservation(char * flightCode, char * seat);
char * insertFlight(char * buff);
char * insertReservation(char * buff);

#endif