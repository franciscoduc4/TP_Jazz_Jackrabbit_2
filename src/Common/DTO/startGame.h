#ifndef START_GAME_DTO_H_
#define START_GAME_DTO_H_

#include <string>
#include <vector>

#include "command.h"

class StartGameDTO: public CommandDTO {
private:
    uint8_t gameId;
    bool gameIdSet;

public:
    StartGameDTO();
    explicit StartGameDTO(const uint8_t& gameId);
    StartGameDTO(uint8_t& playerId, uint8_t& gameId);
    void setGameId(uint8_t gameId);
    uint8_t getGameId() const;
    std::vector<char> getData() const override;
    virtual std::unique_ptr<DTO> clone() const override;
};

#endif  // START_GAME_DTO_H_
