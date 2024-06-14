#include "move.h"

MoveDTO::MoveDTO(uint32_t& player_id, Direction moveType):
        CommandDTO(player_id, Command::MOVE), moveType(moveType) {}

Direction MoveDTO::getMoveType() const { return moveType; }

std::vector<char> MoveDTO::getData() const {
    std::vector<char> data;
    data.push_back(static_cast<char>(moveType));
    return data;
}
