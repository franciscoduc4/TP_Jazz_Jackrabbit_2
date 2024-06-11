#ifndef JOIN_GAME_DTO_H_
#define JOIN_GAME_DTO_H_

#include <string>

#include "../Types/character.h"

#include "command.h"

class JoinGameDTO: public CommandDTO {
private:
    uint32_t gameId;
    CharacterType characterType;
    uint8_t currentPlayers;
    bool joined;

public:
    JoinGameDTO(const uint32_t& gameId, CharacterType characterType);
    JoinGameDTO(const uint32_t& playerId, const uint32_t& gameId, CharacterType characterType);
    JoinGameDTO(const uint32_t& playerId, const uint32_t& gameId, const uint8_t& currentPlayers);
    JoinGameDTO(const uint32_t& playerId, const uint32_t& gameId, const uint8_t& currentPlayers, CharacterType characterType);
    explicit JoinGameDTO(bool joined);
    uint32_t getGameId() const;
    CharacterType getCharacterType() const;
    uint8_t getCurrentPlayers() const;
    bool getJoined() const;
    std::vector<char> getData() const;
};

#endif  // JOIN_GAME_DTO_H_
