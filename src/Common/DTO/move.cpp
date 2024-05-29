#include "move.h"

MoveDTO::MoveDTO(int32_t& player_id, Move moveType):
        CommandDTO(player_id, Command::RUN), moveType(moveType) {}

Move MoveDTO::getMoveType() { return moveType; }
