#ifndef LOBBY_COMMANDS_H
#define LOBBY_COMMANDS_H

#include <cstdint>

enum class LobbyCommands : uint8_t {
<<<<<<< HEAD:src/Common/Constants/lobbyCommands.h
    JOIN_GAME = 0x02,  // "join"
    CREATE_GAME,  // "create"
    LIST_GAMES,   // "list"
    START_GAME  // "start"
=======
    INVALID_CMD = 0x00,
    JOIN_GAME = 0x02,
    CREATE_GAME,
    LIST_GAMES,
    START_GAME
>>>>>>> client:Common/Constants/lobbyCommands.h
};

#endif  // LOBBY_COMMANDS_H
