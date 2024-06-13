#ifndef START_GAME_DTO_H_
#define START_GAME_DTO_H_

#include <string>
#include <vector>

#include "command.h"

class StartGameDTO: public CommandDTO {
private:
    uint32_t gameId;

public:
    explicit StartGameDTO(const uint32_t& gameId);
    StartGameDTO(uint32_t& playerId, uint32_t& gameId);
    uint32_t getGameId() const;
    std::vector<char> getData() const override;
};

#endif  // START_GAME_DTO_H_
