#include "character.h"

std::unique_ptr<Character> Character::createCharacter(const std::string& name) {
    if (name == "jazz") {
        return std::make_unique<Jazz>(0, 0, 100, "jazz", "idle", 0);  // id hardcoded
    } else if (name == "spaz") {
        return std::make_unique<Spaz>(0, 0, 100, "spaz", "idle", 0);
    } else if (name == "lori") {
        return std::make_unique<Lori>(0, 0, 100, "lori", "idle", 0);
    } else {
        return nullptr;
    }
}
