#include "startGame.h"

StartGameDTO::StartGameDTO(int32_t& playerId, int32_t& gameId):
        CommandDTO(Command::START_GAME), gameId(gameId) {}

int32_t StartGameDTO::getGameId() const { return gameId; }