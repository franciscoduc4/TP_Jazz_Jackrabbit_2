#ifndef GAME_INFO_H_
#define GAME_INFO_H_

#include <string>

struct GameInfo {
    std::string name;
    int32_t maxPlayers;
    int32_t currentPlayers;

    // Constructor predeterminado
    GameInfo() : name(""), maxPlayers(0), currentPlayers(0) {}

    // Constructor con parámetros
    GameInfo(std::string name, int32_t maxPlayers, int32_t currentPlayers)
        : name(std::move(name)), maxPlayers(maxPlayers), currentPlayers(currentPlayers) {}
};

#endif  // GAME_INFO_H_
