#ifndef MOVE_DTO_H
#define MOVE_DTO_H

#include "../Types/direction.h"

#include "command.h"

class MoveDTO: public CommandDTO {
private:
    Direction moveType;

public:
    MoveDTO(int32_t& player_id, Direction moveType);

    Direction getMoveType() const;
};

#endif  // MOVE_DTO_H
