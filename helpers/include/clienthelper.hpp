#ifndef _CLIENTHELPER_H_
#define _CLIENTHELPER_H_

#include <poll.h>
#include <netinet/in.h>
#include <vector>

typedef struct pollfd pollfd;

void run_client(int server_fd, int br_fd, sockaddr_in* broad_addr);

void handle_client_input(int target_fd);

void handle_voting(int br_fd, struct sockaddr_in* broad_addr);

void response_handle(int &target_fd, int rec_fd,
    std::vector<pollfd> &pfds, int server_fd);

void server_handle(char* rec_buffer, int server_fd);

void room_handle(char* rec_buffer, int room_fd);

#endif