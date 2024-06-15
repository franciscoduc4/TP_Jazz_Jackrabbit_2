#include "startGame.h"

#include <cstring>
#include <vector>

#include <netinet/in.h>

StartGameDTO::StartGameDTO(): CommandDTO(Command::START_GAME) {}

StartGameDTO::StartGameDTO(const uint8_t& gameId):
        CommandDTO(Command::START_GAME), gameId(gameId) {}

StartGameDTO::StartGameDTO(uint8_t& playerId, uint8_t& gameId):
        CommandDTO(playerId, Command::START_GAME), gameId(gameId) {}

uint8_t StartGameDTO::getGameId() const { return gameId; }

std::vector<char> StartGameDTO::getData() const {
    if (gameId == -1) {
        return std::vector<char>();
    }
    std::vector<char> data;
    data.resize(sizeof(uint8_t));
    data.push_back(static_cast<char>(gameId));
    return data;
}
