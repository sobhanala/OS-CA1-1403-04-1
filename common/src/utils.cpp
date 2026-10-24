#include "utils.hpp"

#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

int socket_by_cli(int argc, char* argv[],
    struct sockaddr_in* addr_info, int socktype)
{
    // file.out ipaddr port
    if(argc != 3)
    {
        perror("ILLEGAL: Arguments not enough");
        exit(1);
    }

    return socket_by_strings(argv[1], argv[2], addr_info, socktype);
}

int socket_by_strings(const char* ipaddr, const char* port,
    struct sockaddr_in* addr_info, int socktype)
{
    int sock_fd, opt = 1;
    addr_info->sin_family = AF_INET;
    if((sock_fd = socket(PF_INET, socktype, 0)) == -1)
        perror("FAILED: Socket was not created");

    if(setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
        perror("FAILED: Making socket reusable failed");

    if(setsockopt(sock_fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)) == -1)
        perror("FAILED: Making socket reusable port failed");

    if(inet_pton(AF_INET, ipaddr, &(addr_info->sin_addr)) == -1)
        perror("FAILED: Input ipv4 address invalid");
    
    char* port_check;
    addr_info->sin_port = htons(strtol(port, &port_check, 10));
    if(port_check == NULL)
        perror("ILLEGAL: Port invalid");
    
    memset(addr_info->sin_zero, 0, sizeof(addr_info->sin_zero));

    return sock_fd;
}

int accept_client(int server_fd)
{
    int client_fd;
    struct sockaddr_in client_socket;
    int cli_addr_len = sizeof(client_socket);
    client_fd = accept(server_fd,(struct sockaddr*) &client_socket,
                (socklen_t*)&cli_addr_len);

    if(client_fd == -1)
        perror("Error Accepting Connection");

    return client_fd;
}

int setup_broadcast(const char* ipaddr, const char* port,
    struct sockaddr_in* addr_info)
{
    int broadcast = 1;
    int broadcast_fd = socket_by_strings(ipaddr,
                                        port,
                                        addr_info,
                                        SOCK_DGRAM);

    if(setsockopt(broadcast_fd, SOL_SOCKET,
        SO_BROADCAST, &broadcast, sizeof(broadcast)) == -1)
    {
        perror("FAILED: Setup broadcast socket");
    }
    return broadcast_fd;
}