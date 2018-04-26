#include "message.h"

message_t create_message(char message_content, long message_sender, int message_type) {
    message_t message;
    if(strlen(message_content)<CONTENT_SIZE) {
        strcpy(message.content,message.content);
        message.sender=message_sender;
        message.type=message_type;
    } else {
        fprintf(stderr, "Taille de message trop grande\n");
        return EXIT_FAILURE;
    }
    return message;
}

void read_message(message_t) {
    printf("{MESSAGE -> FROM %i; TYPE %i; CONTENT %s}\n", message->sender, message->type, message->content);
}