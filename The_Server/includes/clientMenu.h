//clientMenu.h

#ifndef CLIENT_MENU_H
#define CLIENT_MENU_H

#include <stdio.h>
#include <ctype.h>
#include "getnum.h"
#include <stdlib.h>
#include "random.h"
#include <string.h>
#include <stdlib.h>
#include "client.h"
#include "controller.h"
#include "structs.h"

int clientSession();
void readClientMenu ();
void listFlights();

#endif
