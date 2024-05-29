#ifndef LOBBY_COMMANDS_H
#define LOBBY_COMMANDS_H

#include <cstdint>

enum class LobbyCommands : uint8_t {
    JOIN_GAME = 0x02,  // "join"
    CREATE_GAME,  // "create"
    LIST_GAMES,   // "list"
    START_GAME  // "start"
};

#endif  // LOBBY_COMMANDS_H
