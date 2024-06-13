#include "createGame.h"

#include <utility>

#include "../maps/mapsManager.h"


CreateGameDTO::CreateGameDTO(const uint32_t& gameId): gameId(gameId) {}

CreateGameDTO::CreateGameDTO(uint32_t mapId, uint8_t maxPlayers,
                             CharacterType characterType, std::string gameName, uint32_t gameId):
        CommandDTO(Command::CREATE_GAME),
        mapId(mapId),
        mapName(MapsManager::getMapNameById(mapId)),
        maxPlayers(maxPlayers),
        characterType(characterType),
        gameName(std::move(gameName)),
        gameId(gameId) {
    this->mode = (maxPlayers == 1) ? GameMode::SINGLE_PLAYER : GameMode::PARTY_MODE;
}

CreateGameDTO::CreateGameDTO(uint32_t mapId, std::string mapName, uint8_t maxPlayers,
        CharacterType characterType, std::string gameName, uint32_t gameId):
        CommandDTO(Command::CREATE_GAME),
        mapId(mapId),
        mapName(std::move(mapName)),
        maxPlayers(maxPlayers),
        characterType(characterType),
        gameName(std::move(gameName)),
        gameId(gameId) {
    this->mode = (maxPlayers == 1) ? GameMode::SINGLE_PLAYER : GameMode::PARTY_MODE;
}

CreateGameDTO::CreateGameDTO(const uint32_t& playerId, uint32_t mapId, std::string mapName, uint8_t maxPlayers,
                             CharacterType characterType, std::string gameName, uint32_t gameId):
        CommandDTO(playerId, Command::CREATE_GAME),
        mapId(mapId),
        mapName(std::move(mapName)),
        maxPlayers(maxPlayers),
        characterType(characterType),
        gameName(std::move(gameName)),
        gameId(gameId) {
    this->mode = (maxPlayers == 1) ? GameMode::SINGLE_PLAYER : GameMode::PARTY_MODE;
}

std::string CreateGameDTO::getMapName() const { return mapName; }

uint32_t CreateGameDTO::getMapId() const { return mapId; }

uint32_t CreateGameDTO::getGameId() const { return gameId; }

uint8_t CreateGameDTO::getMaxPlayers() const { return maxPlayers; }

CharacterType CreateGameDTO::getCharacterType() const { return characterType; }

std::string CreateGameDTO::getGameName() const { return gameName; }

GameMode CreateGameDTO::getGameMode() const { return mode; }

std::vector<char> CreateGameDTO::getData() const {
    std::vector<char> data;
    data.push_back(static_cast<char>(mapName.size()));
    data.insert(data.end(), mapName.begin(), mapName.end());
    data.push_back(static_cast<char>(maxPlayers));
    data.push_back(static_cast<char>(characterType));
    data.push_back(static_cast<char>(gameName.size()));
    data.insert(data.end(), gameName.begin(), gameName.end());
    return data;
}
