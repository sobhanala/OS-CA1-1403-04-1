#ifndef _NOTIFS_H_
#define _NOTIFS_H_

#include <string>

// Fixed Strings
const std::string SERVER_UP = "Server Launched!\n";
const std::string NEW_USER_MENU = "Welcome to the game, please choose your role\n 1. Player of team blue\n 2. Player of team red\n 3. Spectator\n 4. Arbiter\n";
const std::string NEW_CONNECTION = "New Connection\n";


// Sizes
const size_t BUFFER_SIZE = 1024;

// Constants
const std::string BROAD_PORT = "10120";
const std::string BROAD_ADDR = "127.255.255.255";

const int GAME_TIME = 30;
const int GAME_WINDOW = 10;

// Defines
#define STDIN 0
#define STDOUT 1

#endif