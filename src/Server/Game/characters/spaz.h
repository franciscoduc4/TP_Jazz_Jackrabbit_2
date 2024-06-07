#ifndef SPAZ_H
#define SPAZ_H

#include "character.h"

class Spaz: public Character {
public:
    Spaz(GameMap& map, Vector<int16_t> pos, int16_t characterId);

    void specialAttack(float time) override;
};

#endif  // SPAZ_H
