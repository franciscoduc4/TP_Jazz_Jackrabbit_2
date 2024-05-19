#ifndef LOBBY_COMMANDS_H
#define LOBBY_COMMANDS_H

#include <cstdint>

enum class LobbyCommands : uint8_t {
    JOIN_GAME = 0x02,    // "join"
    CREATE_GAME = 0x03,  // "create"
    LIST_GAMES = 0x04,   // "list"
    START_GAME = 0x05    // "start"
};

#endif  // LOBBY_COMMANDS_H
