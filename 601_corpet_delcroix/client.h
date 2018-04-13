#ifndef __CLIENT_H__
#define __CLIENT_H__

#define _POSIX_C_SOURCE 199309L

#define DEFAULT_MSG_SIZE 1024
#define DEFAULT_UDP_PORT 2048

void handler();
void show_command_synthax(char*);

#endif