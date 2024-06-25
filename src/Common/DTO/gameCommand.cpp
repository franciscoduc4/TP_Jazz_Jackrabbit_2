#include "gameCommand.h"

GameCommandDTO::GameCommandDTO(const uint8_t& player_id,
    const Direction& moveType, const Command& cmd):
        CommandDTO(player_id, cmd), moveType(moveType) {}

Direction GameCommandDTO::getMoveType() const { return moveType; }

std::vector<char> GameCommandDTO::getData() const {
    std::vector<char> data;
    data.push_back(static_cast<char>(moveType));
    return data;
}

std::unique_ptr<DTO> GameCommandDTO::clone() const {
    return std::make_unique<GameCommandDTO>(*this);
}
