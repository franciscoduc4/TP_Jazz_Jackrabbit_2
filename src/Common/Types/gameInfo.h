#ifndef GAME_INFO_H_
#define GAME_INFO_H_

#include <string>
#include <utility>

#include "../../Common/maps/mapsManager.h"

struct GameInfo {
    uint8_t id;
    std::string name;
    uint8_t maxPlayers;
    uint8_t currentPlayers;
    bool ableToJoin;
    uint8_t mapId;
    std::string mapName;

    GameInfo(): id(-1), maxPlayers(-1), currentPlayers(-1), ableToJoin(false), mapId(-1) {}
    GameInfo(const uint8_t& gameId, std::string name, const uint8_t& maxPlayers,
             const uint8_t& currentPlayers):
            id(gameId),
            name(std::move(name)),
            maxPlayers(maxPlayers),
            currentPlayers(currentPlayers),
            mapId(-1),
            mapName("") {
        this->ableToJoin = (maxPlayers > currentPlayers);
    }

    GameInfo(const uint8_t& gameId, std::string name, const uint8_t& maxPlayers,
             const uint8_t& currentPlayers, uint8_t mapId):
            id(gameId),
            name(std::move(name)),
            maxPlayers(maxPlayers),
            currentPlayers(currentPlayers),
            mapId(mapId) {
        this->ableToJoin = (maxPlayers > currentPlayers);
        updateMapName(MapsManager::getMapNameById(mapId));
    }

    uint8_t getGameId() const { return id; }
    std::string getGameName() const { return name; }
    uint8_t getMaxPlayers() const { return maxPlayers; }
    uint8_t getCurrentPlayers() const { return currentPlayers; }
    bool isAbleToJoin() const { return ableToJoin; }
    uint8_t getMapId() const { return mapId; }
    std::string getMapName() const { return mapName; }

    void updateGameId(const uint8_t& gameId) { id = gameId; }
    void updateGameName(std::string name) { this->name = std::move(name); }
    void updateMaxPlayers(const uint8_t& players) {
        maxPlayers = players;
        this->ableToJoin = (maxPlayers > currentPlayers);
    }
    void updateCurrentPlayers(const uint8_t& players) {
        currentPlayers = players;
        this->ableToJoin = (maxPlayers > currentPlayers);
    }
    void updateMapId(const uint8_t& mapId) {
        this->mapId = mapId;
        updateMapName(MapsManager::getMapNameById(mapId));
    }
    void updateMapName(std::string mapName) { 
        if (mapName.find('.') != std::string::npos) {
            std::string ext = mapName.substr(mapName.rfind('.'));
            if (ext == ".yaml" || ext == ".yml") {
                mapName = mapName.substr(0, mapName.rfind('.'));
            }
        }
        this->mapName = std::move(mapName);
    }
    
};

#endif  // GAME_INFO_H_
