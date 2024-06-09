#ifndef GAME_INFO_H_
#define GAME_INFO_H_

#include <string>

struct GameInfo {
    int32_t id;
    std::string name;
    int32_t maxPlayers;
    int32_t currentPlayers;
    bool ableToJoin;

    GameInfo() : id(-1), maxPlayers(-1), currentPlayers(-1), ableToJoin(false){}

    GameInfo(const int32_t& gameId, std::string name, const int32_t& maxPlayers, const int32_t& currentPlayers):
            id(gameId),
            name(std::move(name)),
            maxPlayers(maxPlayers),
            currentPlayers(currentPlayers) {
        this->ableToJoin = (maxPlayers > currentPlayers);
    }

    int32_t getGameId() const { return id; }
    std::string getGameName() const { return name; }
    int32_t getMaxPlayers() const { return maxPlayers; }
    int32_t getCurrentPlayers() const { return currentPlayers; }
    bool isAbleToJoin() const { return ableToJoin; }

    void updateCurrentPlayers(const int32_t& players) {
        currentPlayers = players;
        this->ableToJoin = (maxPlayers > currentPlayers);
    }

};

#endif  // GAME_INFO_H_
