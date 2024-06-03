#ifndef START_GAME_DTO_H_
#define START_GAME_DTO_H_

#include <string>

#include "command.h"

class StartGameDTO: public CommandDTO {
private:
    int32_t gameId;

public:
    explicit StartGameDTO(int32_t& playerId, int32_t& gameId);
    int32_t getGameId() const;
};

#endif  // START_GAME_DTO_H_
