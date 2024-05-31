#ifndef CREATE_GAME_DTO_H_
#define CREATE_GAME_DTO_H_

#include <cstdint>
#include <string>

#include "../Types/character.h"
#include "../Types/episode.h"
#include "../Types/gameMode.h"

#include "command.h"

class CreateGameDTO: public CommandDTO {
private:
    int32_t playerId;
    Episode episodeName;
    GameMode gameMode;
    int32_t gameId;
    uint8_t maxPlayers;
    Character character;
    std::string gameName;

public:
    explicit CreateGameDTO(int32_t gameId);

    CreateGameDTO(int32_t playerId, Episode episodeName, GameMode gameMode, uint8_t maxPlayers,
                  Character character, std::string gameName);

    int32_t getPlayerId() const;

    Episode getEpisodeName() const;

    GameMode getGameMode() const;

    int32_t getGameId() const;

    uint8_t getMaxPlayers() const;

    Character getCharacter() const;

    std::string getGameName() const;

    virtual ~CreateGameDTO() {}
};


#endif  // CREATE_GAME_DTO_H_
