/* Definitions */

/* Include des bibliotheques natives utilises */
#include <signal.h>     /* */
#include <stdio.h>      /* */
#include <stdlib.h>     /* */

/* Include de nos fichiers d'en-tete */
#include "display.h"    /* Pour les fonctionnalites liees a ncurses */

/* Variables globales */

/* Fonctions propres au controler */

void handler(int code) {
}

void show_command_synthax(char *program_name) {
    fprintf(stderr,"%s [NOMBRE_D_OBJETS]\n", program_name);
    fprintf(stderr,"\tWhere :\n\t[NOMBRE_D_OBJETS] is the maximum number of object\n");
}

/* Programme principal du client */
int main(int argc, char *argv[]) {
    /* Verification des donnees passees en argument de la commande ./client */
    if(argc<2) {
        fprintf(stderr,"Too few argument to execute %s\n", argv[0]);
        show_command_synthax(argv[0]);
        exit(EXIT_FAILURE);
    } else if (argc>2) {
        fprintf(stderr,"Too many argument to execute %s\n", argv[0]);
        show_command_synthax(argv[0]);
        exit(EXIT_FAILURE);
    } else if (atoi(argv[1])==0) {
        fprintf(stderr,"Invalid argument : %s\n", argv[1]);
        show_command_synthax(argv[0]);
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
