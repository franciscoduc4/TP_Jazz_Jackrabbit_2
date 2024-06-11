#include "startGame.h"

StartGameDTO::StartGameDTO(const uint32_t& gameId):
        CommandDTO(Command::START_GAME), gameId(gameId) {}

StartGameDTO::StartGameDTO(uint32_t& playerId, uint32_t& gameId):
        CommandDTO(playerId, Command::START_GAME), gameId(gameId) {}

uint32_t StartGameDTO::getGameId() const { return gameId; }