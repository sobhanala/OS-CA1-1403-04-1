#ifndef _PLAYER_ENTITY_H_
#define _PLAYER_ENTITY_H_

#include "role.hpp"

class Player : public Role
{
public:
    Player(RoleSate role_state, int role_id) : Role(role_state)
        {m_role_id = role_id;}
    
    void server_handle(char* buffer, int myfd);
};


#endif