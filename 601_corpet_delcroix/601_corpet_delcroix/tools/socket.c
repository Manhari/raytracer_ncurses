#include <arpa/inet.h>  /* Pour IPPROTO_TCP, sockaddr_in */
#include <errno.h>      /* Pour errno */
#include <stdio.h>      /* Pour printf, fprintf, perror */
#include <stdlib.h>     /* Pour exit, EXIT_SUCCESS, EXIT_FAILURE */
#include <sys/socket.h> /* Pour socket */
#include <sys/time.h>   /* Pour time */
#include <sys/types.h>  /* Pour getpid et pid_t */
#include <string.h>     /* Pour memset */
#include <unistd.h>     /* Pour close */

#include "socket.h"

/* Fonction de creation d'une socket */
int create_socket(int protocol) {
    int file_descriptor;
    if(protocol==TCP) {
        if((file_descriptor=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
            perror("Erreur lors de la creation de la socket TCP ");
            exit(EXIT_FAILURE);
        }
    } else if(protocol==UDP) {
        if((file_descriptor=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
            perror("Erreur lors de la creation de la socket UDP ");
            exit(EXIT_FAILURE);
        }
    } else {
        fprintf(stderr,"Protocole invalide ou non pris en charge\n");
        exit(EXIT_FAILURE);
    }
    return file_descriptor;
}

/* Fonction de suppression d'une socket */
void create_address(struct sockaddr_in *host_address_struct, char *host_address_string, int port, int type) {
    memset(host_address_struct, 0, sizeof(struct sockaddr_in));
    host_address_struct->sin_family = AF_INET;
    host_address_struct->sin_port = htons(port);
    if(type==SERVER) {
        host_address_struct->sin_addr.s_addr = htonl(INADDR_ANY);
    } else if(type==CLIENT) {
        if(inet_pton(AF_INET, host_address_string, &(host_address_struct->sin_addr)) != 1) {
            perror("Erreur lors de la conversion de l'adresse ");
            exit(EXIT_FAILURE);
        }
    }
}

/* Fonction de lecture d'un message dans une socket */
void read_message(int client_file_descriptor, char *message, size_t size, int protocol) {
    if(protocol==TCP) {
        if(read(client_file_descriptor, &size, sizeof(size_t))==-1) {
            perror("Erreur lors de la lecture de la taille du message ");
            exit(EXIT_FAILURE);
        }
        if(read(client_file_descriptor, message, sizeof(char)*size)==-1) {
            perror("Erreur lors de la lecture de la taille du message ");
            exit(EXIT_FAILURE);
        }
    } else if(protocol==UDP) {
        printf("{%i -> Server waiting connection}\n",getpid());
        if(recvfrom(client_file_descriptor, &size, sizeof(size_t), 0, NULL, NULL)==-1) {
            perror("Erreur lors de la reception de la taille du message ");
            exit(EXIT_FAILURE);
        }
        if(recvfrom(client_file_descriptor, message, sizeof(char)*size, 0, NULL, NULL)==-1) {
            perror("Erreur lors de la reception du message ");
            exit(EXIT_FAILURE);
        }
    } else {
        fprintf(stderr,"Protocole invalide ou non pris en charge\n");
        exit(EXIT_FAILURE);
    }
    printf("{%i -> Server receive \"%s\"}\n", getpid(), message);
}

/* Fonction de fermeture d'une socket */
void close_socket(int file_descriptor) {
    if(close(file_descriptor)==-1) {
        perror("Erreur lors de la fermeture de la socket ");
        exit(EXIT_FAILURE);
    }
}

/* Fonction de nommage d'une socket */
void bind_socket(int file_descriptor, struct sockaddr_in *address) {
    if(bind(file_descriptor, (struct sockaddr*)address, sizeof(struct sockaddr_in))==-1) {
        perror("Erreur lors du nommage de la socket ");
        exit(EXIT_FAILURE);
    }
}


/* Fonction de mise en ecoute d'une socket */
void listen_socket(int file_descriptor) {
    if(listen(file_descriptor, 1)==-1) {
        perror("Erreur lors de la mise en mode passif ");
        exit(EXIT_FAILURE);
    }
}


/* Fonction d'attente de connexion d'une socket */
void wait_connection_socket(int server_file_descriptor, int client_file_descriptor) {
    printf("{%i -> Server waiting connections}\n",getpid());
    if((client_file_descriptor=accept(server_file_descriptor, NULL, NULL))==-1) {
        perror("Erreur lors de la demande de connexion ");
        exit(EXIT_FAILURE);
    }
}