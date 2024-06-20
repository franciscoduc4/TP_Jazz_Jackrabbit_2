#ifndef SPAZ_H
#define SPAZ_H

#include "character.h"

class Spaz: public Character {
public:
    Spaz(uint8_t playerId, Vector<uint32_t> position);
};

#endif  // SPAZ_H
