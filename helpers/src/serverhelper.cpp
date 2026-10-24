#include "serverhelper.hpp"

#include <unistd.h>
#include <poll.h>
#include <vector>
#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unordered_map>

#include "defs.hpp"
#include "utils.hpp"
#include "role.hpp"

using namespace std;

typedef struct pollfd pollfd;

void run_server(int server_fd)
{
    unordered_map<int, Role*> client_roles;
    vector<pollfd> pfds = {pollfd{server_fd, POLLIN, 0}};
    // init_room(pfds)   
    while(1)
    {
        if(poll(pfds.data(), (nfds_t)(pfds.size()), -1) == -1)
            perror("FAILED: Poll");

        for(size_t i = 0; i < pfds.size(); ++i)
        {
            if(pfds[i].revents & POLLIN) 
            {
                if(pfds[i].fd == server_fd)
                {
                    handle_new_user(pfds,
                                   server_fd,
                                   client_roles);
                }
                // menu, room report
                // or broadcast (voting)
                else 
                {
                    handle_response(pfds[i].fd,
                                    client_roles.at(pfds[i].fd));
                }
            }
        }
    }
}

void handle_new_user(vector<pollfd> &pfds,
                    int server_fd,
                    unordered_map<int, Role*> &client_roles)
{
    int new_fd = accept_client(server_fd);
    if(new_fd != -1)
    {
        send(new_fd, NEW_USER_MENU.c_str(), strlen(NEW_USER_MENU.c_str()), 0);
        pfds.push_back(pollfd{new_fd, POLLIN, 0});
        write(1, NEW_CONNECTION.c_str(), strlen(NEW_CONNECTION.c_str()));
        client_roles.insert(std::pair<int, Role*>{new_fd, new Role(ROLE_NOT_CHOSEN)});
    }
}

void handle_response(int client_fd, Role* role)
{
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    recv(client_fd, buffer, BUFFER_SIZE, 0);
    Role* chosen_role = check_role(role, buffer);
    if(chosen_role != nullptr)
    {
        role->server_handle(buffer, client_fd);
        return;
    }
    Role* temp_role = role;
    role = chosen_role;
    delete temp_role;
}