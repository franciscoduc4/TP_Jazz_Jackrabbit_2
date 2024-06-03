#include "character.h"


std::unique_ptr<Character> Character::createCharacter(const std::string& characterType) {
    if (characterType == "Jazz") {
        return std::make_unique<Jazz>();
    } else if (characterType == "Spaz") {
        return std::make_unique<Spaz>();
    } else if (characterType == "Lori") {
        return std::make_unique<Lori>();
    }
    return nullptr;
}
