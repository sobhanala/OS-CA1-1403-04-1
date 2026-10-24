#ifndef _SPECTATOR_ENTITY_H_
#define _SPECTATOR_ENTITY_H_

#include "role.hpp"

class Spectator : public Role
{
public:
    Spectator(RoleSate role_state, int role_id) : Role(role_state) 
        {m_role_id = role_id;}

    void server_handle(char* buffer, int myfd);
};

#endif