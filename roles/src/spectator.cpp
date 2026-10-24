#include "spectator.hpp"

#include <stdio.h>

void Spectator::server_handle(char* buffer, int myfd)
{
    if(m_role_state == ROLE_NOT_CHOSEN)
        perror("ILLEGAL: For subclass of role");
    else
    {
        // TODO
    }
}