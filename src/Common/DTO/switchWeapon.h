#ifndef SWITCH_WEAPON_DTO_H_
#define SWITCH_WEAPON_DTO_H_

#include "../Types/weapon.h"

#include "command.h"

class SwitchWeaponDTO: public CommandDTO {
private:
    WeaponType type;

public:
    SwitchWeaponDTO(uint8_t& playerId, WeaponType type);
    WeaponType getWeaponType() const;
    virtual std::unique_ptr<DTO> clone() const override;
};

#endif  // SWITCH_WEAPON_H_