#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "message.h"

int create_queue(int);
void delete_queue(int);
int get_queue(int);
void receive_queue(int, message_t*, int);
void send_queue(int, message_t*);

#endif