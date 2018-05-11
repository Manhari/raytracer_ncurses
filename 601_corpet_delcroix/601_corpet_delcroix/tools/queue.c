#include <errno.h>      /* Pour errno */
#include <stdio.h>      /* Pour printf, fprintf, perror */
#include <stdlib.h>     /* Pour exit, EXIT_SUCCESS, EXIT_FAILURE */
#include <sys/msg.h>    /* Pour msgget, msgsnd, msgrcv */
#include <sys/stat.h>   /* Pour S_IRUSR, S_IWUSR */

#include "queue.h"

/* Fonction de creation d'une file de messages */
int create_queue(int queue_key) {
    int queue_identifier;
    if((queue_identifier=msgget((key_t)queue_key, S_IRUSR | S_IWUSR | IPC_CREAT | IPC_EXCL))==-1) {
        if(errno==EEXIST) {
            fprintf(stderr, "Erreur : file (cle=%i) existante\n", queue_key);
        } else {
            perror("Erreur lors de la creation de la file ");
        }
        exit(EXIT_FAILURE);
    }
    return queue_identifier;
}

/* Fonction de suppression d'une de message */
void delete_queue(int queue_key) {
    int queue_identifier;
    queue_identifier=get_queue(queue_key);
    if(msgctl(queue_identifier, IPC_RMID, 0)==-1) {
        perror("delete queue ");
        exit(EXIT_FAILURE);
    }
}

/* Fonction de recuperation d'une file de messages */
int get_queue(int queue_key) {
    int queue_identifier;
    if((queue_identifier=msgget((key_t)queue_key, 0))==-1) {
        if(errno==ENOENT) {
            perror("File inexistante ");
        } else {
            perror("Erreur lors de la recuperation de la file ");
        }
        exit(EXIT_FAILURE);
    }
    return queue_identifier;
}

/* Fonction de reception d'un message_t dans une file de message */
void receive_queue(int queue_identifier, message_t *message, int message_type) {
    printf("Serveur : en attente d'une requete...\n");
    if(msgrcv(queue_identifier, message, sizeof(message_t)-sizeof(long), message_type, 0)==-1) {
        perror("Erreur lors de l'attente ou la reception d'un message ");
        exit(EXIT_FAILURE);
    }
}

/* Fonction d'envoi d'un message_t dans une file de message */
void send_queue(int queue_identifier, message_t *message){
    if(msgsnd(queue_identifier, message, sizeof(message_t)-sizeof(long), 0)==-1) {
        perror("Erreur lors de l'envoi de la reponse ");
        exit(EXIT_FAILURE);
    }
}