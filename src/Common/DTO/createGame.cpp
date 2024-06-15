#include "createGame.h"

#include <utility>

#include "../maps/mapsManager.h"


CreateGameDTO::CreateGameDTO(const uint8_t& gameId):
        gameId(gameId), CommandDTO(Command::CREATE_GAME) {}

CreateGameDTO::CreateGameDTO(uint8_t mapId, uint8_t maxPlayers, CharacterType characterType,
                             std::string gameName):
        CommandDTO(Command::CREATE_GAME),
        mapId(mapId),
        maxPlayers(maxPlayers),
        characterType(characterType),
        gameName(std::move(gameName)) {
    this->mode = (maxPlayers == 1) ? GameMode::SINGLE_PLAYER : GameMode::PARTY_MODE;
}

CreateGameDTO::CreateGameDTO(const uint8_t& playerId, uint8_t mapId, uint8_t maxPlayers,
                             CharacterType characterType, std::string gameName):
        CommandDTO(playerId, Command::CREATE_GAME),
        mapId(mapId),
        maxPlayers(maxPlayers),
        characterType(characterType),
        gameName(std::move(gameName)) {
    this->mode = (maxPlayers == 1) ? GameMode::SINGLE_PLAYER : GameMode::PARTY_MODE;
}


uint8_t CreateGameDTO::getMapId() const { return mapId; }

uint8_t CreateGameDTO::getGameId() const { return gameId; }

uint8_t CreateGameDTO::getMaxPlayers() const { return maxPlayers; }

CharacterType CreateGameDTO::getCharacterType() const { return characterType; }

std::string CreateGameDTO::getGameName() const { return gameName; }

GameMode CreateGameDTO::getGameMode() const { return mode; }

std::vector<char> CreateGameDTO::getData() const {
    std::vector<char> data;
    data.push_back(static_cast<char>(maxPlayers));
    data.push_back(static_cast<char>(characterType));
    data.push_back(static_cast<char>(gameName.size()));
    data.insert(data.end(), gameName.begin(), gameName.end());
    return data;
}
