#ifndef MOVE_DTO_H
#define MOVE_DTO_H

#include <vector>

#include "../Types/direction.h"

#include "command.h"

class GameCommandDTO : public CommandDTO {
private:
    Direction moveType;

public:
    GameCommandDTO(const uint32_t& player_id, const Direction& moveType, const Command& cmd);

    Direction getMoveType() const;

    std::vector<char> getData() const override;
};

#endif  // MOVE_DTO_H
