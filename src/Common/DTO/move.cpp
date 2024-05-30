#include "move.h"

MoveDTO::MoveDTO(int32_t& player_id, Move moveType):
CommandDTO(player_id, Command::MOVE), moveType(moveType) {}

Move MoveDTO::getMoveType() const { return moveType; }
