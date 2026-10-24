#include <stdio.h>
#include <sys/socket.h>
#include <unordered_map>
#include <unistd.h>
#include <string.h>

#include "utils.hpp"
#include "serverhelper.hpp"
#include "role.hpp"
#include "defs.hpp"

const int MAX_CONNECTIONS = 20;

int main(int argc, char* argv[])
{
    struct sockaddr_in server_addr;
    int server_fd = socket_by_cli(argc, argv, &server_addr, SOCK_STREAM);
    if(bind(server_fd, (const struct sockaddr*)(&server_addr), sizeof(server_addr)) == -1)
        perror("FAILED: Bind unsuccessfull");

    if(listen(server_fd, 20) == -1)
        perror("FAILED: Listen unsuccessfull");
        
    write(1, SERVER_UP.c_str(), strlen(SERVER_UP.c_str()));
    // init_rooms
    run_server(server_fd);
}