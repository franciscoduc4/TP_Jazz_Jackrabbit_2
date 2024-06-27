#include "specialAttack.h"

SpecialAttackDTO::SpecialAttackDTO(uint8_t& playerId, CharacterType type): CommandDTO(playerId, Command::SPECIAL_ATTACK), type(type) {}

CharacterType SpecialAttackDTO::getCharacterType() const {
    return type;
}

std::unique_ptr<DTO> SpecialAttackDTO::clone() const {
    return std::unique_ptr<DTO>(new SpecialAttackDTO(*this));
}

std::vector<char> SpecialAttackDTO::getData() const {
    std::vector<char> data;
    data.push_back(static_cast<char>(type));
    return data;
}