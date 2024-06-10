#include "createGame.h"

#include <utility>

CreateGameDTO::CreateGameDTO(const int32_t& gameId): gameId(gameId) {}

CreateGameDTO::CreateGameDTO(Episode episodeName,
                             uint8_t maxPlayers, CharacterType characterType, std::string gameName,
                             int32_t gameId):
        CommandDTO(-1,Command::CREATE_GAME),
        episodeName(episodeName),
        maxPlayers(maxPlayers),
        characterType(characterType),
        gameName(std::move(gameName)),
        gameId(gameId) {
    this->mode = (maxPlayers == 1) ? GameMode::SINGLE_PLAYER : GameMode::PARTY_MODE;
}

CreateGameDTO::CreateGameDTO(const int32_t& playerId, Episode episodeName,
                             uint8_t maxPlayers, CharacterType characterType, std::string gameName,
                             int32_t gameId):
        CommandDTO(playerId,Command::CREATE_GAME),
        episodeName(episodeName),
        maxPlayers(maxPlayers),
        characterType(characterType),
        gameName(std::move(gameName)),
        gameId(gameId) {
    this->mode = (maxPlayers == 1) ? GameMode::SINGLE_PLAYER : GameMode::PARTY_MODE;
}

Episode CreateGameDTO::getEpisodeName() const { return episodeName; }

int32_t CreateGameDTO::getGameId() const { return gameId; }

uint8_t CreateGameDTO::getMaxPlayers() const { return maxPlayers; }

CharacterType CreateGameDTO::getCharacterType() const { return characterType; }

std::string CreateGameDTO::getGameName() const { return gameName; }

GameMode CreateGameDTO::getGameMode() const { return mode; }

std::vector<char> CreateGameDTO::getData() const {
    std::vector<char> data;
    data.push_back(static_cast<char>(episodeName));
    data.push_back(static_cast<char>(maxPlayers));
    data.push_back(static_cast<char>(characterType));
    data.push_back(static_cast<char>(gameName.size()));
    data.insert(data.end(), gameName.begin(), gameName.end());
    return data;
}
