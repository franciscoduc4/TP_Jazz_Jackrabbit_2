#ifndef JOIN_GAME_DTO_H_
#define JOIN_GAME_DTO_H_

#include <string>

#include "command.h"

class JoinGameDTO: public CommandDTO {
private:
    int32_t playerId;
    int32_t gameId;
    bool joined;

public:
    JoinGameDTO(int32_t& playerId, int32_t& gameId);
    explicit JoinGameDTO(bool joined);
    int32_t getGameId();
    bool getJoined();
};

#endif  // JOIN_GAME_DTO_H_
