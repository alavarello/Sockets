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

#endif
