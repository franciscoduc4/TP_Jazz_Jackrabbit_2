#ifndef CREATE_GAME_DTO_H_
#define CREATE_GAME_DTO_H_

#include <cstdint>
#include <string>

#include "../Types/character.h"
#include "../Types/gameMode.h"

#include "command.h"

class CreateGameDTO: public CommandDTO {
private:
    std::string episodeName;
    uint32_t episodeId;
    GameMode gameMode;
    uint8_t maxPlayers;
    CharacterType characterType;
    std::string gameName;
    uint32_t gameId;
    GameMode mode;

public:
    explicit CreateGameDTO(const uint32_t& gameId);

    CreateGameDTO(const uint32_t& playerId, std::string episodeName, uint8_t maxPlayers,
                  CharacterType character, std::string gameName, uint32_t gameId);

    std::string getEpisodeName() const;

    uint32_t getEpisodeId() const;

    uint32_t getGameId() const;

    uint8_t getMaxPlayers() const;

    CharacterType getCharacterType() const;

    std::string getGameName() const;

    std::vector<char> getData() const;

    GameMode getGameMode() const;

    virtual ~CreateGameDTO() {}
};


#endif  // CREATE_GAME_DTO_H_
