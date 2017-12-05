#ifndef SEMAPHORES_H
#define SEMAPHORES_H 

#include <sys/types.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include <string.h>
#include <fcntl.h>

#define MAX_PROCESSES 20

sem_t * openSemaphore(char * s);
sem_t * openProcessSemaphore(char * s);

#endif

