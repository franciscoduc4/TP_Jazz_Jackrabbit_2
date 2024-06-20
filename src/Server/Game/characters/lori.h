#ifndef LORI_H
#define LORI_H

#include "character.h"

class Lori: public Character {
public:
    Lori(uint8_t playerId, Vector<uint32_t> position);
};

#endif  // LORI_H
