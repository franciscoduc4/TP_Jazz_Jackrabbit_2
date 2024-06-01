#include "joinGame.h"

JoinGameDTO::JoinGameDTO(int32_t& playerId, int32_t& gameId, CharacterType characterType):
        playerId(playerId), gameId(gameId), characterType(characterType) {}

JoinGameDTO::JoinGameDTO(bool status): CommandDTO(Command::JOIN_GAME), joined(status) {}

int32_t JoinGameDTO::getGameId() const { return gameId; }

CharacterType JoinGameDTO::getCharacterType() const { return characterType; }

bool JoinGameDTO::getJoined() const { return joined; }
