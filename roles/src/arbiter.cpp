#include "arbiter.hpp"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "defs.hpp"

void Arbiter::server_handle(char* buffer, int myfd)
{
    if(m_role_state == ROLE_NOT_CHOSEN)
        perror("ILLEGAL: For subclass of role");
    else
    {
        char buffer[BUFFER_SIZE];
        memset(buffer, 0, BUFFER_SIZE);
        read(myfd, buffer, BUFFER_SIZE);
        // TODO
    }
}