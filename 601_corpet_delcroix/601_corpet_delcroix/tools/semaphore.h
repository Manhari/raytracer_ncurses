#ifndef __SEMAPHORE_H__
#define __SEMAPHORE_H__

#include <sys/sem.h>  /* Pour semget, semctl, semop */

/* Fonctions */
int create_semaphore(int);
void delete_semaphore(int);
int get_semaphore(int);
void initialise_semaphore(int, unsigned short*);
void update_semaphore(int, struct sembuf*);
struct sembuf create_operation_buffer(int, int, int);

#endif