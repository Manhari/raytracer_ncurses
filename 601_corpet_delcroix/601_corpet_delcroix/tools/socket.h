#ifndef __SOCKET_H__
#define __SOCKET_H__

#define SERVER          0
#define CLIENT          1

#define TCP             0
#define UDP             1

/***********
   GLOBAL
***********/

/*  BOTH  */

int create_socket(int);
void create_address(struct sockaddr_in*, char*, int, int);
void close_socket(int);

/* CLIENT */

/* SERVER */

void bind_socket(int, struct sockaddr_in*);
void read_message(int client_file_descriptor, char *message, size_t size, int protocol);

/***********
    TCP
***********/

/*  BOTH  */

/* CLIENT */

/* SERVER */

void listen_socket(int);
void wait_message(int, int);

/***********
    UDP
***********/

/*  BOTH  */

/* CLIENT */

/* SERVER */


#endif