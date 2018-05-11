#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <errno.h>
#include <sys/stat.h>

#include "segment.h"

/* Fonction de creation d'un segment de memoire partagee */
int create_segment(int shared_memory_key, int shared_memory_size) {
    int shared_memory_identifier;
    if((shared_memory_identifier=shmget((key_t)shared_memory_key, sizeof(int)*shared_memory_size, S_IRUSR | S_IWUSR | IPC_CREAT | IPC_EXCL))==-1) {
        if(errno==EEXIST)
        {
            fprintf(stderr, "Le segment de memoire partagee (cle=%d) existe deja\n", shared_memory_key);
            exit(EXIT_FAILURE);
        } else {
            perror("Erreur lors de la creation du segment de memoire ");
            exit(EXIT_FAILURE);
        }
    }
    return shared_memory_identifier;
}

/* Fonction de creation d'un segment de memoire partagee */
void delete_segment(int shared_memory_identifier) {
    if(shmctl(shared_memory_identifier, IPC_RMID, 0) == -1) {
        perror("Erreur lors de la suppression du segment de memoire partagee ");
        exit(EXIT_FAILURE);
    }
}

/* Fonction de recuperation d'un segment de memoire partagee */
int get_segment(int shared_memory_key) {
    int shared_memory_identifier;
    if((shared_memory_identifier=shmget((key_t)shared_memory_key, 0, 0))==-1) {
        perror("Erreur lors de la recuperation du segment de memoire ");
        exit(EXIT_FAILURE);
    }
    return shared_memory_identifier;
}

/* Fonction d'attachement d'un segment de memoire partagee */
void* bind_segment(int shared_memory_identifier) {
    void *shared_memory_address;
    if((shared_memory_address=shmat(shared_memory_identifier, NULL, 0))==(void*)-1) {
        perror("Erreur lors de l'attachement du segment de memoire partagee ");
        exit(EXIT_FAILURE);
    }
    return shared_memory_address;
}

/* Fonction de dettachement d'un segment de memoire partagee */
void unbind_segment(void *shared_memory_address) {
    if(shmdt(shared_memory_address)==-1) {
        perror("Erreur lors du detachement ");
        exit(EXIT_FAILURE);
    }
}