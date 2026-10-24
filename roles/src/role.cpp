#include "role.hpp"

#include <stdio.h>
#include <stdlib.h>

#include "player.hpp"
#include "spectator.hpp"
#include "arbiter.hpp"

Role* Role::choose_role(int role)
{
    switch(role)
    {
        case(BLUE_ROLE):
            return dynamic_cast<Role*>(new Player(ROLE_CHOSEN,role));

        case(RED_ROLE):
            return dynamic_cast<Role*>(new Player(ROLE_CHOSEN,role));

        case(SPECT_ROLE):
            return dynamic_cast<Role*>(new Spectator(ROLE_CHOSEN,role));

        case(ARB_ROLE):
            return dynamic_cast<Role*>(new Arbiter(ROLE_CHOSEN,role));
        
        default:
            return this;
    }
}

void Role::server_handle(char* buffer, int myfd)
{
    perror("ILLEGAL: Something went wrong on our end");
}

Role* check_role(Role* role, char* buffer)
{
    if(role->m_role_state != ROLE_NOT_CHOSEN)
        return nullptr;

    Role* chosen_role = role->choose_role(strtol(buffer, NULL, 10));
    if(role->m_role_id == chosen_role->m_role_id) // Wrong Choose
        perror("ILLEGAL: Invalid role has been chosen");
    else
    {
        return chosen_role;
    }
    return nullptr;
}