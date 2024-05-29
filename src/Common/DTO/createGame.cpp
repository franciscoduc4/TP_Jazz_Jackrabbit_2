#include "createGame.h"

CreateGameDTO::CreateGameDTO(int32_t gameId): CommandDTO(gameId, Command::CREATE_GAME) {}

CreateGameDTO::CreateGameDTO(int32_t playerId, Episode episodeName, GameMode gameMode,
                             uint8_t maxPlayers):
        CommandDTO(playerId, Command::CREATE_GAME),
        playerId(playerId),
        episodeName(episodeName),
        gameMode(gameMode),
        gameId(gameId),
        maxPlayers(maxPlayers) {}

int32_t CreateGameDTO::getPlayerId() { return playerId; }

Episode CreateGameDTO::getEpisodeName() { return episodeName; }

GameMode CreateGameDTO::getGameMode() { return gameMode; }

int32_t CreateGameDTO::getGameId() { return gameId; }

uint8_t CreateGameDTO::getMaxPlayers() { return maxPlayers; }
