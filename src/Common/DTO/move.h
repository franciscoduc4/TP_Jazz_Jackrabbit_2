#ifndef MOVE_DTO_H
#define MOVE_DTO_H

#include <vector>

#include "../Types/direction.h"

#include "command.h"

class MoveDTO: public CommandDTO {
private:
    Direction moveType;

public:
    MoveDTO(uint32_t& player_id, Direction moveType);

    Direction getMoveType() const;

    std::vector<char> getData() const override;
};

#endif  // MOVE_DTO_H
