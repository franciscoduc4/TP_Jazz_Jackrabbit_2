#ifndef JOIN_GAME_DTO_H_
#define JOIN_GAME_DTO_H_

#include <string>
#include <memory>

#include "../Types/character.h"

#include "command.h"
#include "dto.h"

class JoinGameDTO: public CommandDTO {
private:
    uint8_t gameId;
    CharacterType characterType;
    uint8_t currentPlayers;
    bool joined;

public:
    JoinGameDTO(const uint8_t& gameId, CharacterType characterType);
    JoinGameDTO(const uint8_t& gameId, const uint8_t& currentPlayers);
    JoinGameDTO(const uint8_t& playerId, const uint8_t& gameId, CharacterType characterType);
    JoinGameDTO(const uint8_t& playerId, const uint8_t& gameId, const uint8_t& currentPlayers);
    JoinGameDTO(const uint8_t& playerId, const uint8_t& gameId, const uint8_t& currentPlayers,
                CharacterType characterType);
    explicit JoinGameDTO(bool joined);
    uint8_t getGameId() const;
    CharacterType getCharacterType() const;
    uint8_t getCurrentPlayers() const;
    bool getJoined() const;
    std::vector<char> getData() const;

    virtual std::unique_ptr<DTO> clone() const override;
};

#endif  // JOIN_GAME_DTO_H_
