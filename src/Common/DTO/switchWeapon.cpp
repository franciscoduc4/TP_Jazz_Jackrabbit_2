#include "switchWeapon.h"

SwitchWeaponDTO::SwitchWeaponDTO(uint32_t& playerId, WeaponType type): type(type) {}

WeaponType SwitchWeaponDTO::getWeaponType() const { return type; }