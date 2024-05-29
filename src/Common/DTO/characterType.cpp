#include "characterType.h"

#include <iostream>
CharacterTypeDTO::CharacterTypeDTO(int32_t& playerId, Character character):
        CommandDTO(playerId, Command::CHARACTER_TYPE), character(character) {}

Character CharacterTypeDTO::getCharacter() const { return character; }
