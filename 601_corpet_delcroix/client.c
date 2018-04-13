/* Definitions */

#define _POSIX_C_SOURCE 199309L

/* Include des bibliotheques natives utilises */
#include <signal.h>     /* */
#include <stdio.h>      /* */
#include <stdlib.h>     /* */
#include <string.h>     /* */

/* Include de nos fichiers d'en-tete */
#include "client.h"
#include "display.h"    /* Pour les fonctionnalites liees a ncurses */
#include "socket.h"     /* Pour les fonctionnalites liees au sockets */

/* Variables globales */

char *message;
int inbound_file_descriptor, outbound_file_descriptor;

/* Fonctions propres au client */
void handler(int code) {
    if(code==SIGINT || code==SIGSEGV) {
        printf("SIGNAL %i reçu\n", code);
        printf("\t- Arrêt du Serveur\n");

        printf("\t\t- Fermeture des sockets\n");
        close_socket(inbound_file_descriptor);
        close_socket(outbound_file_descriptor);

        printf("\t\t- Libération de la mémoire\n");
        free(message);

        exit(EXIT_SUCCESS);
    } else {
        exit(EXIT_FAILURE);
    }
}

void show_command_synthax(char *program_name) {
    fprintf(stderr,"%s [ADDRESS] [TCP] [UDP]\n", program_name);
    fprintf(stderr,"\tWhere :\n\t[ADDRESS] is the visualizer IPv4 address
					\n\t[TCP] is the visualizer TCP port
					\n\t[UDP] is the visualizer UDP port\n");
}

/* Programme principal du client */
int main(int argc, char *argv[]) {
    /* Declaration des variables */
	struct sigaction action;
    struct sockaddr_in host_address;
    struct sockaddr_in own_address;
    int /*visualizer_TCP, */visualizer_UDP;
    char visualizer_address[16];

    /* Verification des donnees passees en argument de la commande ./client */
    if(argc<4) {
        fprintf(stderr,"Too few argument to execute %s\n", argv[0]);
        show_command_synthax(argv[0]);
        exit(EXIT_FAILURE);
    } else if (argc>4) {
        fprintf(stderr,"Too many argument to execute %s\n", argv[0]);
        show_command_synthax(argv[0]);
        exit(EXIT_FAILURE);
    } else if (strlen(argv[1])>15) {
        fprintf(stderr,"Invalid argument : %s\n", argv[1]);
        show_command_synthax(argv[0]);
        exit(EXIT_FAILURE);
    } else if (atoi(argv[2])<1024) {
        fprintf(stderr,"Invalid argument : %s\n", argv[2]);
        show_command_synthax(argv[0]);
        exit(EXIT_FAILURE);
    } else if (atoi(argv[3])<1024) {
        fprintf(stderr,"Invalid argument : %s\n", argv[3]);
        show_command_synthax(argv[0]);
        exit(EXIT_FAILURE);
    }

    /* Initialisation des variables */
    strcpy(visualizer_address,argv[1]);
    /*visualizer_TCP=atoi(argv[2]);*/
    visualizer_UDP=atoi(argv[3]);

    /* Allocation de l'espace memoire pour le message */
    if((message=(char*)malloc(DEFAULT_MSG_SIZE*sizeof(char)))==NULL){
        perror("malloc -> erreur lors de l'allocation ");
        exit(EXIT_FAILURE);
    }

    /* Mise en place du handler */
    if((sigaction(SIGINT, &action, NULL)==-1) || (sigaction(SIGSEGV, &action, NULL)==-1)) {
        perror("sigaction(SIGINT, &action, NULL) || sigaction(SIGSEGV, &action, NULL)");
        exit(EXIT_FAILURE);
    }

    /* Creation des sockets */
    inbound_file_descriptor=create_socket(UDP);
    outbound_file_descriptor=create_socket(UDP);

    /* Creation des adresses */
    create_address(&host_address, visualizer_address, visualizer_UDP, CLIENT);
    create_address(&own_address, "127.0.0.1", DEFAULT_UDP_PORT, SERVER);

    /* Nommage de la socket de reception */
    bind_socket(inbound_file_descriptor, &own_address);

    /* Envoi d'une requete UDP au visualiseur */

    /* Attente d'une reponse UDP du visualiseur */
    read_message(inbound_file_descriptor, message, DEFAULT_MSG_SIZE, UDP);
    
    return EXIT_SUCCESS;
}