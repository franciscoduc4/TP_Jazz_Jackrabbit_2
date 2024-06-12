#include "createGame.h"

#include <utility>

CreateGameDTO::CreateGameDTO(const uint32_t& gameId): gameId(gameId) {}

CreateGameDTO::CreateGameDTO(const uint32_t& playerId, std::string episodeName, uint8_t maxPlayers,
                             CharacterType characterType, std::string gameName, uint32_t gameId):
        CommandDTO(playerId, Command::CREATE_GAME),
        episodeName(episodeName),
        maxPlayers(maxPlayers),
        characterType(characterType),
        gameName(std::move(gameName)),
        gameId(gameId) {
    this->mode = (maxPlayers == 1) ? GameMode::SINGLE_PLAYER : GameMode::PARTY_MODE;
}

std::string CreateGameDTO::getEpisodeName() const { return episodeName; }

uint32_t CreateGameDTO::getEpisodeId() const { return episodeId; }

uint32_t CreateGameDTO::getGameId() const { return gameId; }

uint8_t CreateGameDTO::getMaxPlayers() const { return maxPlayers; }

CharacterType CreateGameDTO::getCharacterType() const { return characterType; }

std::string CreateGameDTO::getGameName() const { return gameName; }

GameMode CreateGameDTO::getGameMode() const { return mode; }

std::vector<char> CreateGameDTO::getData() const {
    std::vector<char> data;
    data.push_back(static_cast<char>(episodeName.size()));
    data.insert(data.end(), episodeName.begin(), episodeName.end());
    data.push_back(static_cast<char>(maxPlayers));
    data.push_back(static_cast<char>(characterType));
    data.push_back(static_cast<char>(gameName.size()));
    data.insert(data.end(), gameName.begin(), gameName.end());
    return data;
}
