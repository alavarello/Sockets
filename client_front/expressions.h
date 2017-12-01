//expressions.h

#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include <stdio.h>
#include <ctype.h>
#include "getnum.h"
#include <stdlib.h>
#include "random.h"
#include <string.h>
#include <stdlib.h>
#include "Client.h"
#include "Controller.h"
#include "structs.h"

int isNumber(char c);
int isAlpha(char c);
int isValidSeatExpression(char * seat);
int checkSeatNumberFormat(char * seat ,  tFlight * currentFlight);
int getColumn(char * seat);
int getNumber(char * seat);
int isValidFlightAndPlaneCodeExpression(char * thing);
int isValidOriginDestination(char * place);
int isValidTime(char * time);
int isValidTimeHour (char n1, char n2);
int isValidTimeMinutes(char n1, char n2);
int isValidDate(char * date);
int isValidDayAndMonth(char d1, char d2, char m1, char m2, int y);
int isValidYear(char y1, char y2, char y3, char y4);

/* se supone que a la funcion de abajo hay que llamarla cuando ya se sepa que los dias y horarios que ingreso son validos */
int checkLogicalTimeDifference(char * timeDeparture, char * timeArrival, char * dateDeparture, char * dateArrival);
int dateDiff(char * big, char * small);
int timeDiff(char * timeArrival, char * timeDeparture);

#endif
