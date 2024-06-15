#ifndef SPAZ_H
#define SPAZ_H

#include "character.h"

class Spaz: public Character {
public:
    Spaz(GameMap& map, Vector<uint8_t> pos, uint8_t playerId);

    void specialAttack(float time) override;
};

#endif  // SPAZ_H
