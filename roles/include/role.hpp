#ifndef _ENTITY_H_
#define _ENTITY_H_

// Role Specifiers
const int NO_ROLE = 0;
const int BLUE_ROLE = 4;
const int RED_ROLE = 1;
const int SPECT_ROLE = 2;
const int ARB_ROLE = 3;

typedef enum RoleSate {
    ROLE_NOT_CHOSEN,
    ROLE_CHOSEN,
} RoleState;


class Role
{
protected:
    RoleState m_role_state = ROLE_NOT_CHOSEN;
    int m_role_id = NO_ROLE;

public:
    Role(RoleState role_state) : m_role_state(role_state)
        {}

    Role* choose_role(int role);
    
    virtual void server_handle(char* buffer, int myfd);

    friend Role* check_role(Role* role, char* buffer);
};

#endif