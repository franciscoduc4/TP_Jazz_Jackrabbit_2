#include "joinGame.h"

JoinGameDTO::JoinGameDTO(int32_t& playerId, int32_t& gameId): 
    playerId(playerId), gameId(gameId){}

JoinGameDTO::JoinGameDTO(bool status): CommandDTO(Command::JOIN_GAME), joined(status) {}

int32_t JoinGameDTO::getGameId() const { return gameId; }

bool JoinGameDTO::getJoined() const { return joined; }
