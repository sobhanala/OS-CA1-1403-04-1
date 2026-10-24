#ifndef _UTILS_H_
#define _UTILS_H_

#include <netinet/in.h>

int socket_by_cli(int argc, char* argv[],
    struct sockaddr_in* addr_info, int socktype);

int socket_by_strings(const char* ipaddr, const char* port,
    struct sockaddr_in* addr_info, int socktype);

int accept_client(int server_fd);

int setup_broadcast(const char* ipaddr, const char* port,
    struct sockaddr_in* addr_info);

#endif