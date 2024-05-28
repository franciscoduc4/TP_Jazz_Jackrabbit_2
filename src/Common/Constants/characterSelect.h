#ifndef CHARACTER_SELECT_H
#define CHARACTER_SELECT_H

#include <cstdint>

enum class CharacterSelect : uint8_t {
    INVALID = 0x00,
    JAZZ = 0x01,
    SPAZ,
    LORI
};

#endif  // CHARACTER_SELECT_H
