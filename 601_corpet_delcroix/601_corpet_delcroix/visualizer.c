/* Definitions */

/* Include des bibliotheques natives utilises */
#include <math.h>               /* */
#include <ncurses.h>            /* */
#include <signal.h>             /* */
#include <stdio.h>              /* */
#include <stdlib.h>             /* */
#include <time.h>               /* */

/* Include de nos fichiers d'en-tete */
#include "tools/queue.h"          /* */

/* Variables globales */



/* Fonctions propres au cvisualiseur */

void handler(int code) {
    if(code==SIGINT || code==SIGSEGV) {
        /* Affichage du code du signal reçu*/
        printf("SIGNAL %i reçu\n", code);

        exit(EXIT_SUCCESS);
    } else {
        exit(EXIT_FAILURE);
    }
}

void show_command_synthax(char *program_name) {
    fprintf(stderr,"%s [QUEUE_KEY]\n", program_name);
    fprintf(stderr,"\tWhere :\n\t[QUEUE_KEY] is the key of the message queue\n");
}

/* Programme principal du client */
int main(int argc, char *argv[]) {
    message_t message;
    int queue_identifier=0, queue_key=0;

     /* Verification des donnees passees en argument de la commande ./client */
    if(argc<2) {
        fprintf(stderr,"Too few argument to execute %s\n", argv[0]);
        show_command_synthax(argv[0]);
        exit(EXIT_FAILURE);
    } else if (argc>2) {
        fprintf(stderr,"Too many argument to execute %s\n", argv[0]);
        show_command_synthax(argv[0]);
        exit(EXIT_FAILURE);
    } else if (atoi(argv[1])<0) {
        fprintf(stderr,"Invalid argument : %s\n", argv[1]);
        show_command_synthax(argv[0]);
        exit(EXIT_FAILURE);
    }

    queue_key=argv[1];

    queue_identifier=get_queue(queue_key);
    receive_queue(queue_identifier, &message, START);

/*Au démarrage, le visualiseur se met en attente d’un message dans la file de messages de la part du contrôleur qui lui
indique que la simulation débute. Dès que c’est le cas, il peut récupérer la scène depuis le segment de mémoire
partagée. Il peut ensuite envoyer les requêtes aux clients. Il affiche le résultat au fur-et-à-mesure (une fois que tous
les clients connectés ont répondu). La scène peut ne pas être complète si tous les clients ne sont pas connectés. Par
exemple, si la scène est découpée en 4 parties et qu’un seul client est connecté, un quart de la scène sera visible.
À tout moment, le visualiseur peut recevoir des messages dans la file de messagesindiquant la mise en pause ou l’arrêt
de la simulation.*/
    
    return EXIT_SUCCESS;
}