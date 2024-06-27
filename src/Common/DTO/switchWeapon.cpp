#include "switchWeapon.h"

SwitchWeaponDTO::SwitchWeaponDTO(uint8_t& playerId, WeaponType type): CommandDTO(playerId, Command::SWITCH_WEAPON), type(type) {}

WeaponType SwitchWeaponDTO::getWeaponType() const { return type; }

std::unique_ptr<DTO> SwitchWeaponDTO::clone() const {
    return std::unique_ptr<DTO>(new SwitchWeaponDTO(*this));
}

std::vector<char> SwitchWeaponDTO::getData() const {
    std::vector<char> data;
    data.push_back(static_cast<char>(type));
    return data;
}
