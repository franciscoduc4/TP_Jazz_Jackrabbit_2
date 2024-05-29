#include "joinGame.h"

JoinGameDTO::JoinGameDTO(int32_t& playerId, int32_t& gameId): playerId(playerId), gameId(gameId) {}

JoinGameDTO::JoinGameDTO(bool status): CommandDTO(Command::JOIN_GAME), joined(joined) {}
