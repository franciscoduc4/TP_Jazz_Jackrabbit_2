#ifndef JAZZ_H
#define JAZZ_H

#include "character.h"


class Jazz: public Character {
public:
    Jazz(uint8_t playerId, Vector<uint32_t> position);
};

#endif  // JAZZ_H
