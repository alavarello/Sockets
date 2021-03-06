
#include "semaphores.h"

sem_t * openSemaphore(char * s)
{
    sem_t * sem;
    char * semKey= malloc(MAX_SMAPHORE_NAME * sizeof(char));

    semKey[0] = 0;

    strcat(semKey,s);

    sem = sem_open (semKey, O_CREAT, 0644, 1); 

    if(sem==SEM_FAILED){
        printf("Error opening semaphore named %s\n", s);
    }
    
    sem_unlink (semKey); 

    return sem;
}

sem_t * openProcessSemaphore(char * s)
{
    sem_t * sem;
    char * semKey= malloc(MAX_SMAPHORE_NAME * sizeof(char));

    semKey[0] = 0;

    strcat(semKey,s);

    sem = sem_open (semKey, O_CREAT, 0644, MAX_PROCESSES); 

    if(sem==SEM_FAILED){
        printf("Error opening semaphore named %s\n", s);
    }
    
    sem_unlink (semKey); 

    return sem;
}
