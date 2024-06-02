#include "switchWeapon.h"

SwitchWeaponDTO::SwitchWeaponDTO(uint8_t weaponId): weaponId(weaponId) {}

uint8_t SwitchWeaponDTO::getWeaponType() const { return weaponId; }