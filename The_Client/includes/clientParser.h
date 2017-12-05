#ifndef CLIENT_PARSER_H
#define CLIENT_PARSER_H 

#define GET_ALL_FLIGHTS 1
#define GET_FLIGHT 2
#define INSERT_FLIGHT 3
#define GET_ALL_PLANES 4
#define GET_ALL_RESERVATIONS 5
#define GET_ALL_CANCELATIONS 6
#define INSERT_RESERVATION 7
#define INSERT_CANCELLATION 8
#define GET_RESERVATIONS_FOR_A_FLIGHT 9
#define GET_RESERVATION 10
#define DELETE_FLIGHT 11
#define DELETE_RESERVATON 12
#define ERROR_CODE "ERROR"
#define ERROR_CODE_CHAR_MAX 6
#define ACTION_CODE_ERROR 49
#define END_PROCESS 100


void * parseRecivedMessage(int action, char * buff);
char * parseMessageToSend(int action, void * param, int * bytes);

#endif
