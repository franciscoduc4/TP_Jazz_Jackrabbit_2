#ifndef MOVE_DTO_H
#define MOVE_DTO_H

#include "../Types/move.h"

#include "command.h"

class MoveDTO: public CommandDTO {
private:
    Move moveType;

public:
    MoveDTO(int32_t& player_id, Move moveType);

    Move getMoveType() const;
};

#endif  // MOVE_DTO_H
