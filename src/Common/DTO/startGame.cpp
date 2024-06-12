#include "startGame.h"

#include <cstring>
#include <vector>

#include <netinet/in.h>

StartGameDTO::StartGameDTO() : CommandDTO(Command::START_GAME), gameId(-1) {}

StartGameDTO::StartGameDTO(const uint32_t& gameId):
        CommandDTO(Command::START_GAME), gameId(gameId) {}

StartGameDTO::StartGameDTO(uint32_t& playerId, uint32_t& gameId):
        CommandDTO(playerId, Command::START_GAME), gameId(gameId) {}

uint32_t StartGameDTO::getGameId() const { return gameId; }

std::vector<char> StartGameDTO::getData() const {
    if (gameId == -1) {
        return std::vector<char>();
    }
    uint32_t network_gameId = htonl(gameId);
    std::vector<char> data(sizeof(uint32_t));
    memcpy(reinterpret_cast<void*>(data[0]), &network_gameId, sizeof(uint32_t));
    return data;
}
