#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include "constants.h"
#include <string.h>
#include <fcntl.h>

sem_t * openSemaphore(char * s)
{
    sem_t * sem;
    char * semKey= malloc(MAX_SMAPHORE_NAME * sizeof(char));

    strcat(semKey,s);


    sem = sem_open (semKey, O_CREAT, 0644, 1); 

    if(sem==SEM_FAILED){
        printf("Error opening semaphore named %s\n", s);
    }
    
    sem_unlink (semKey); 

    return sem;
}