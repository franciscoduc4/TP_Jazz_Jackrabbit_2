#ifndef SPECIAL_ATTACK_DTO_H
#define SPECIAL_ATTACK_DTO_H

#include "command.h"
#include "../Types/character.h"

class SpecialAttackDTO: public CommandDTO {
private:
    CharacterType type;

public:
    SpecialAttackDTO(uint8_t& playerId, CharacterType type);
    CharacterType getCharacterType() const;
    virtual std::unique_ptr<DTO> clone() const override;
    std::vector<char> getData() const;

};


#endif // SPECIAL_ATTACK_DTO_H