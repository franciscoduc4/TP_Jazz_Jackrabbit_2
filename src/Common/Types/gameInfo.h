#ifndef GAME_INFO_H_
#define GAME_INFO_H_

#include <string>

struct GameInfo {
    uint8_t id;
    std::string name;
    uint8_t maxPlayers;
    uint8_t currentPlayers;
    bool ableToJoin;
    std::string mapName;

    GameInfo(): id(-1), maxPlayers(-1), currentPlayers(-1), ableToJoin(false) {}
    GameInfo(const uint8_t& gameId, std::string name, const uint8_t& maxPlayers,
             const uint8_t& currentPlayers):
            id(gameId),
            name(std::move(name)),
            maxPlayers(maxPlayers),
            currentPlayers(currentPlayers),
            mapName("invalid") {
        this->ableToJoin = (maxPlayers > currentPlayers);
    }

    GameInfo(const uint8_t& gameId, std::string name, const uint8_t& maxPlayers,
             const uint8_t& currentPlayers, std::string mapName):
            id(gameId),
            name(std::move(name)),
            maxPlayers(maxPlayers),
            currentPlayers(currentPlayers),
            mapName(mapName) {
        this->ableToJoin = (maxPlayers > currentPlayers);
    }

    uint8_t getGameId() const { return id; }
    std::string getGameName() const { return name; }
    uint8_t getMaxPlayers() const { return maxPlayers; }
    uint8_t getCurrentPlayers() const { return currentPlayers; }
    bool isAbleToJoin() const { return ableToJoin; }
    std::string getMapName() const { return mapName; }

    void updateCurrentPlayers(const uint8_t& players) {
        currentPlayers = players;
        this->ableToJoin = (maxPlayers > currentPlayers);
    }
};

#endif  // GAME_INFO_H_
