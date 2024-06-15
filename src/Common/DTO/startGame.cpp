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
    uint8_t network_gameId = htonl(gameId);
    std::vector<char> data(sizeof(uint8_t));
    memcpy(reinterpret_cast<void*>(data[0]), &network_gameId, sizeof(uint8_t));
    return data;
}
