#include "clienthelper.hpp"

#include <vector>
#include <poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#include "role.hpp"
#include "defs.hpp"

using namespace std;

#define STDIN 0

void run_client(int server_fd, int br_fd, sockaddr_in* broad_addr)
{
    vector<pollfd> pfds = {
        pollfd{server_fd, POLLIN, 0},
        pollfd{STDIN, POLLIN, 0},
        pollfd{br_fd, POLLIN, 0}
        };
    
    int target_fd = server_fd;

    while(1)
    {
        if(poll(pfds.data(), (nfds_t)(pfds.size()), -1) == -1)
            perror("FAILED: Poll");

        for(size_t i = 0; i < pfds.size(); ++i)
        {
            if(pfds[i].revents & POLLIN) 
            {
                // input from user
                if(pfds[i].fd == STDIN)
                {
                    handle_client_input(target_fd);
                }
                // menu, room report
                // or broadcast (voting)
                else if(pfds[i].fd == br_fd)
                {
                    handle_voting(br_fd, broad_addr);
                }
                else // Receive from server or room
                {
                    response_handle(target_fd,
                                    pfds[i].fd,
                                    pfds,
                                    server_fd);
                }
            }
        }
    }
}

void handle_client_input(int target_fd)
{
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    read(STDIN, buffer, BUFFER_SIZE);
    send(target_fd, buffer, BUFFER_SIZE, 0);
}

void handle_voting(int br_fd, struct sockaddr_in* broad_addr)
{
    char* buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    socklen_t broad_addr_len = sizeof(broad_addr);
    if(recvfrom(br_fd, buffer, BUFFER_SIZE, 0, (sockaddr*)(broad_addr),
        (socklen_t*)(&broad_addr_len)) <= 0)
    {
        perror("FAILED: receive voting broadcast");
    }
    write(STDOUT, buffer, BUFFER_SIZE);
}

void response_handle(int &target_fd, int rec_fd,
    std::vector<pollfd> &pfds, int server_fd)
{
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    read(rec_fd, buffer, BUFFER_SIZE);
    if(rec_fd == server_fd) // from server
    {
        server_handle(buffer, server_fd);
    }
    else // from room
    {
        room_handle(buffer, rec_fd);
    }
}

void server_handle(char* rec_buffer, int server_fd)
{
    write(STDOUT, rec_buffer, strlen(rec_buffer));
    // TODO: Handle voting - getting port of the room
}

void room_handle(char* rec_buffer, int room_fd)
{
    write(STDOUT, rec_buffer, strlen(rec_buffer));
}