#include "joinGame.h"

JoinGameDTO::JoinGameDTO(int32_t& playerId, int32_t& gameId, Character character):
        playerId(playerId), gameId(gameId), character(character) {}

JoinGameDTO::JoinGameDTO(bool status): CommandDTO(Command::JOIN_GAME), joined(status) {}

int32_t JoinGameDTO::getGameId() const { return gameId; }

Character JoinGameDTO::getCharacter() const { return character; }

bool JoinGameDTO::getJoined() const { return joined; }
