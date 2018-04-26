#ifndef __MESSAGE_H__
#define __MESSAGE_H__

/* Type de messages */
#define ANSWER			0
#define REQUEST			1
#define START			2
#define STOP			3

/* Type de l'emetteur */
#define CLIENT			0
#define CONTROLER		1
#define VISUALIZER		2

/* Taille du contenu */
#define CONTENT_SIZE	255

/* Structure utilisee pour les messages */
typedef struct {
  long type;
  int sender;
  char content[CONTENT_SIZE];
} message_t;

message_t create_message(long, int, char*);
void read_message(message_t);

#endif
