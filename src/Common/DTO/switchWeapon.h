#ifndef SWITCH_WEAPON_DTO_H_
#define SWITCH_WEAPON_DTO_H_

#include "command.h"

class SwitchWeaponDTO: public CommandDTO {
private:
    uint8_t weaponId;

public:
    SwitchWeaponDTO(uint8_t weaponId);
    uint8_t getWeaponType() const;
};

#endif  // SWITCH_WEAPON_H_