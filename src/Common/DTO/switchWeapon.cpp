#include "switchWeapon.h"

SwitchWeaponDTO::SwitchWeaponDTO(uint8_t& playerId, WeaponType type): type(type) {}

WeaponType SwitchWeaponDTO::getWeaponType() const { return type; }

std::unique_ptr<DTO> SwitchWeaponDTO::clone() const {
    return std::unique_ptr<DTO>(new SwitchWeaponDTO(*this));
}
