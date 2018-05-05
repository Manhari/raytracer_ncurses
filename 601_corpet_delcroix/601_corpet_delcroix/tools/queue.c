#include "queue.h"

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

void delete_queue(int queue_key) {
    int queue_identifier;
    queue_identifier=get_queue(queue_key);
    if(msgctl(queue_identifier, IPC_RMID, 0)==-1) {
        perror("delete queue ");
        exit(EXIT_FAILURE);
    }
}

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

void receive_queue(int queue_identifier, message_t *message, int message_type) {
    printf("Serveur : en attente d'une requete...\n");
    if(msgrcv(queue_key, message, sizeof(message_t)-sizeof(long), message_type, 0)==-1) {
        perror("Erreur lors de l'attente ou la reception d'un message ");
        exit(EXIT_FAILURE);
    }
}

void send_queue(int queue_identifier, message_t *message){
    if(msgsnd(queue_key, message, sizeof(message_t)-sizeof(long), 0)==-1) {
        perror("Erreur lors de l'envoi de la reponse ");
        exit(EXIT_FAILURE);
    }
}