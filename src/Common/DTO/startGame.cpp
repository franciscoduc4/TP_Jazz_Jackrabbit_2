#include "startGame.h"

#include <cstring>
#include <vector>

#include <netinet/in.h>

StartGameDTO::StartGameDTO(): CommandDTO(Command::START_GAME), gameId(), gameIdSet(false) {}

StartGameDTO::StartGameDTO(const uint8_t& gameId):
        CommandDTO(Command::START_GAME), gameId(gameId), gameIdSet(true) {}

StartGameDTO::StartGameDTO(uint8_t& playerId, uint8_t& gameId):
        CommandDTO(playerId, Command::START_GAME), gameId(gameId), gameIdSet(true) {}

void StartGameDTO::setGameId(uint8_t gameId) {
    this->gameId = gameId;
    gameIdSet = true;
}

uint8_t StartGameDTO::getGameId() const { return gameId; }

std::vector<char> StartGameDTO::getData() const {
    if (!gameIdSet) {
        return {};
    }
    std::vector<char> data;
    //data.resize(sizeof(uint8_t));
    data.push_back(static_cast<char>(gameId));
    return data;
}

std::unique_ptr<DTO> StartGameDTO::clone() const {
    return std::unique_ptr<DTO>(new StartGameDTO(*this));
}
