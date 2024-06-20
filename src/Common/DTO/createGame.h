#ifndef CREATE_GAME_DTO_H_
#define CREATE_GAME_DTO_H_

#include <cstdint>
#include <string>
#include <vector>

#include "../Types/character.h"
#include "../Types/gameMode.h"

#include "command.h"

class CreateGameDTO: public CommandDTO {
private:
    uint8_t mapId;
    uint8_t maxPlayers;
    CharacterType characterType;
    std::string gameName;
    uint8_t gameId;
    GameMode mode;

public:
    explicit CreateGameDTO(const uint8_t& gameId);

    CreateGameDTO(uint8_t mapId, uint8_t maxPlayers, CharacterType character, std::string gameName);


    CreateGameDTO(const uint8_t& playerId, uint8_t mapId, uint8_t maxPlayers,
                  CharacterType character, std::string gameName);


    uint8_t getMapId() const;

    uint8_t getGameId() const;

    uint8_t getMaxPlayers() const;

    CharacterType getCharacterType() const;

    std::string getGameName() const;

    std::vector<char> getData() const;

    GameMode getGameMode() const;

    virtual std::unique_ptr<DTO> clone() const override;

    virtual ~CreateGameDTO() {}
};


#endif  // CREATE_GAME_DTO_H_
