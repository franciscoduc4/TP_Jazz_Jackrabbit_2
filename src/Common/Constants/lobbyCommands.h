#ifndef LOBBY_COMMANDS_H
#define LOBBY_COMMANDS_H

#include <cstdint>

enum class LobbyCommands : uint8_t {
    INVALID_CMD = 0x00,
    JOIN_GAME = 0x02,
    CREATE_GAME,
    LIST_GAMES,
    START_GAME
};

#endif  // LOBBY_COMMANDS_H
