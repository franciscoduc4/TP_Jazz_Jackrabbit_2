#ifndef CHARACTER_TYPE_DTO_H_
#define CHARACTER_TYPE_DTO_H_

#include "../Types/character.h"

#include "command.h"

class CharacterTypeDTO: public CommandDTO {
private:
    CharacterType& characterType;

public:
    CharacterTypeDTO(int32_t& playerId, CharacterType& characterType);

    CharacterType getCharacter() const;

    virtual ~CharacterTypeDTO();
};

#endif  // CHARACTER_TYPE_DTO_H_
