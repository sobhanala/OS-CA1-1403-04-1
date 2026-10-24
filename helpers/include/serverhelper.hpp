#ifndef _SERVERHELPER_H_
#define _SERVERHELPER_H_

class Role;

#include <vector>
#include <poll.h>
#include <unordered_map>

using namespace std;

void run_server(int server_fd);

void handle_new_user(vector<pollfd> &pfds,
                    int server_fd,
                    unordered_map<int, Role*> &client_roles);

void handle_response(int client_fd, Role* role);

#endif