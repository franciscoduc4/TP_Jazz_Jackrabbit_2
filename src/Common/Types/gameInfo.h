#ifndef GAME_INFO_H_
#define GAME_INFO_H_

#include <string>

struct GameInfo {
    uint32_t id;
    std::string name;
    uint32_t maxPlayers;
    uint32_t currentPlayers;
    bool ableToJoin;
    std::string mapName;

    GameInfo() : id(-1), maxPlayers(-1), currentPlayers(-1), ableToJoin(false){}
    GameInfo(const uint32_t& gameId, std::string name, const uint32_t& maxPlayers, const uint32_t& currentPlayers):
            id(gameId),
            name(std::move(name)),
            maxPlayers(maxPlayers),
            currentPlayers(currentPlayers),
            mapName("invalid") {
        this->ableToJoin = (maxPlayers > currentPlayers);
            }

    GameInfo(const uint32_t& gameId, std::string name, const uint32_t& maxPlayers, const uint32_t& currentPlayers, std::string mapName):
            id(gameId),
            name(std::move(name)),
            maxPlayers(maxPlayers),
            currentPlayers(currentPlayers),
            mapName(mapName) {
        this->ableToJoin = (maxPlayers > currentPlayers);
    }

    uint32_t getGameId() const { return id; }
    std::string getGameName() const { return name; }
    uint32_t getMaxPlayers() const { return maxPlayers; }
    uint32_t getCurrentPlayers() const { return currentPlayers; }
    bool isAbleToJoin() const { return ableToJoin; }
    std::string getMapName() const { return mapName; }

    void updateCurrentPlayers(const uint32_t& players) {
        currentPlayers = players;
        this->ableToJoin = (maxPlayers > currentPlayers);
    }

};

#endif  // GAME_INFO_H_
