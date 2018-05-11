#include <stdio.h>    /* Pour printf, perror */
#include <stdlib.h>   /* Pour exit, EXIT_SUCCESS, EXIT_FAILURE */
#include <sys/sem.h>  /* Pour semget, semctl, semop */
#include <errno.h>    /* Pour errno */
#include <sys/stat.h> /* Pour S_IRUSR, S_IWUSR */

#include "semaphore.h"

/* Fonction de creation d'un tableau de semaphores */
int create_semaphore(int semaphore_key, int size) {
    int semaphore_identifier;
    if((semaphore_identifier=semget((key_t)semaphore_key, size, S_IRUSR | S_IWUSR | IPC_CREAT | IPC_EXCL))==-1) {
        perror("Erreur lors de la creation du tableau de semaphores ");
        exit(EXIT_FAILURE);
    }
    return semaphore_identifier;
}

/* Fonction de suppression d'un tableau de semaphores */
void delete_semaphore(int semaphore_identifier) {
    if(semctl(semaphore_identifier, 0, IPC_RMID)==-1) {
        perror("Erreur lors de la suppresion du tableau de semaphores ");
        exit(EXIT_FAILURE);
    }
}

/* Fonction de recuperation d'un tableau de semaphores */
int get_semaphore(int semaphore_key) {
    int semaphore_identifier;
    if((semaphore_identifier=semget((key_t)semaphore_key, 0, 0))==-1) {
        perror("Erreur lors de la recuperation du tableau de semaphores ");
        exit(EXIT_FAILURE);
    }
    return semaphore_identifier;
}

/* Fonction d'initialisation d'un tableau de semaphores */
void initialise_semaphore(int semaphore_identifier, unsigned short *semaphore_value) {
    if(semctl(semaphore_identifier, 0, SETALL, semaphore_value)==-1) {
        perror("Erreur lors de l'initialisation des semaphores ");
        exit(EXIT_FAILURE);
    }
}

/* Fonction de mise à jour d'un semaphore */
void update_semaphore(int semaphore_identifier, struct sembuf *buffer) {
    if(semop(semaphore_identifier, buffer, 1)==-1) {
        perror("Erreur lors de l'operation sur le semaphore ");
        exit(EXIT_FAILURE);
    }
}

/* Fonction d'un buffer de modification d'un semaphore */
struct sembuf create_operation_buffer(int semaphore_numero, int semaphore_operation, int semaphore_flag) {
    struct sembuf operation_buffer;
    operation_buffer.sem_num=semaphore_numero;
    operation_buffer.sem_op=semaphore_operation;
    operation_buffer.sem_flg=semaphore_flag;
    return operation_buffer;
}