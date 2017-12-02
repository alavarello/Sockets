#ifndef CLIENT_PARSER_H
#define CLIENT_PARSER_H 

char * parseRecivedMessage(int action, char * buff);
char * parseMessageToSend(int action, void * param);

#endif