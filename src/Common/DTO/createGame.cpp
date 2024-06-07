#include "createGame.h"

CreateGameDTO::CreateGameDTO(int32_t gameId): CommandDTO(Command::CREATE_GAME), gameId(gameId) {}

CreateGameDTO::CreateGameDTO(Episode episodeName, GameMode gameMode, uint8_t maxPlayers,
                             CharacterType characterType, std::string gameName):
        CommandDTO(Command::CREATE_GAME),
        episodeName(episodeName),
        gameMode(gameMode),
        maxPlayers(maxPlayers),
        characterType(characterType),
        gameName(gameName) {}

int32_t CreateGameDTO::getPlayerId() const { return playerId; }

Episode CreateGameDTO::getEpisodeName() const { return episodeName; }

GameMode CreateGameDTO::getGameMode() const { return gameMode; }

int32_t CreateGameDTO::getGameId() const { return gameId; }

uint8_t CreateGameDTO::getMaxPlayers() const { return maxPlayers; }

CharacterType CreateGameDTO::getCharacterType() const { return characterType; }

std::string CreateGameDTO::getGameName() const { return gameName; }
