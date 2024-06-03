#include "characterType.h"

#include <iostream>
CharacterTypeDTO::CharacterTypeDTO(int32_t& playerId, CharacterType& characterType):
        CommandDTO(playerId, Command::CHARACTER_TYPE), characterType(characterType) {}

CharacterType CharacterTypeDTO::getCharacter() const { return characterType; }
