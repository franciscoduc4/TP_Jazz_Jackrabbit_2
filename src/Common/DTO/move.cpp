#include "move.h"

MoveDTO::MoveDTO(int32_t& player_id, Direction moveType):
        CommandDTO(player_id, Command::MOVE), moveType(moveType) {}

Direction MoveDTO::getMoveType() const { return moveType; }
