#ifndef JOIN_GAME_DTO_H_
#define JOIN_GAME_DTO_H_

#include <string>

#include "../Types/character.h"

#include "command.h"

class JoinGameDTO: public CommandDTO {
private:
    int32_t playerId;
    int32_t gameId;
    CharacterType characterType;
    bool joined;

public:
    JoinGameDTO(int32_t& playerId, int32_t& gameId, CharacterType characterType);
    explicit JoinGameDTO(bool joined);
    int32_t getGameId() const;
    CharacterType getCharacterType() const;
    bool getJoined() const;
};

#endif  // JOIN_GAME_DTO_H_
