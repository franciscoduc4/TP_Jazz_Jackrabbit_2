#ifndef CREATE_GAME_DTO_H_
#define CREATE_GAME_DTO_H_

#include <cstdint>
#include <string>

#include "../Types/character.h"
#include "../Types/gameMode.h"
#include <vector>

#include "command.h"

class CreateGameDTO: public CommandDTO {
private:
    uint32_t mapId;
    uint8_t maxPlayers;
    CharacterType characterType;
    std::string gameName;
    uint32_t gameId;
    GameMode mode;

public:
    explicit CreateGameDTO(const uint32_t& gameId);

    CreateGameDTO(uint32_t mapId, uint8_t maxPlayers,
                  CharacterType character, std::string gameName);


    CreateGameDTO(const uint32_t& playerId, uint32_t mapId, uint8_t maxPlayers,
                  CharacterType character, std::string gameName);


    uint32_t getMapId() const;

    uint32_t getGameId() const;

    uint8_t getMaxPlayers() const;

    CharacterType getCharacterType() const;

    std::string getGameName() const;

    std::vector<char> getData() const;

    GameMode getGameMode() const;

    virtual ~CreateGameDTO() {}
};


#endif  // CREATE_GAME_DTO_H_
