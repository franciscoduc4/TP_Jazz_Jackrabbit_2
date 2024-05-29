#ifndef CREATE_GAME_DTO_H_
#define CREATE_GAME_DTO_H_

#include <cstdint>
#include <string>

#include "command.h"
#include "episode.h"
#include "gameMode.h"

class CreateGameDTO: public CommandDTO {
private:
    int32_t playerId;
    Episode episodeName;
    GameMode gameMode;
    int32_t gameId;
    uint8_t maxPlayers;

public:
    explicit CreateGameDTO(int32_t gameId);

    CreateGameDTO(int32_t playerId, Episode episodeName, GameMode gameMode, uint8_t maxPlayers);

    int32_t getPlayerId();

    Episode getEpisodeName();

    GameMode getGameMode();

    int32_t getGameId();

    uint8_t getMaxPlayers();

    virtual ~CreateGameDTO() {}
};


#endif  // CREATE_GAME_DTO_H_