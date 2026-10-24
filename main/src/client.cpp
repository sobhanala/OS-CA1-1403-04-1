#include <stdio.h>

#include "utils.hpp"
#include "clienthelper.hpp"
#include "defs.hpp"

int main(int argc, char* argv[])
{
    struct sockaddr_in server_addr;
    struct sockaddr_in broadcast_addr;
    int server_fd = socket_by_cli(argc, argv, &server_addr, SOCK_STREAM);
    if(connect(server_fd,
        (const struct sockaddr*)(&server_addr),
        sizeof(server_addr)) == -1)
    {
        perror("FAILED: connect on client error");
    }
    int broadcast_fd = setup_broadcast(BROAD_ADDR.c_str(),
                                        BROAD_PORT.c_str(),
                                        &broadcast_addr);

    run_client(server_fd, broadcast_fd, &broadcast_addr);
}