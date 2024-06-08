#include "joinGame.h"

JoinGameDTO::JoinGameDTO(int32_t gameId, uint8_t currentPlayers):
        CommandDTO(Command::JOIN_GAME),
        playerId(playerId),
        gameId(gameId),
        currentPlayers(currentPlayers) {}

JoinGameDTO::JoinGameDTO(int32_t playerId, int32_t& gameId, CharacterType characterType):
        CommandDTO(playerId, Command::JOIN_GAME), gameId(gameId), characterType(characterType) {}

int32_t JoinGameDTO::getGameId() const { return gameId; }

CharacterType JoinGameDTO::getCharacterType() const { return characterType; }

bool JoinGameDTO::getJoined() const { return joined; }

uint8_t JoinGameDTO::getCurrentPlayers() const { return currentPlayers; }