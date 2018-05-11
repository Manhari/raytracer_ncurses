#include <errno.h>      /* Pour errno */
#include <stdio.h>      /* Pour printf, fprintf, perror */
#include <stdlib.h>     /* Pour exit, EXIT_SUCCESS, EXIT_FAILURE */

#include "message.h"

/* Fonction de creation d'une structure message_t */
message_t create_message(char *message_content, long message_sender, int message_type) {
    message_t message;
    if(strlen(message_content)<CONTENT_SIZE) {
        strcpy(message.content,message.content);
        message.sender=message_sender;
        message.type=message_type;
    } else {
        fprintf(stderr, "Taille de message trop grande\n");
        exit(EXIT_FAILURE);
    }
    return message;
}

/* Fonction d'affichage du contenu d'une structure message_t */
void read_message(message_t message) {
    printf("{MESSAGE -> FROM %i; TYPE %i; CONTENT %s}\n", message.sender, message.type, message.content);
}