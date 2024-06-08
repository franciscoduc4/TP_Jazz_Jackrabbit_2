#ifndef LORI_H
#define LORI_H

#include "character.h"

class Lori: public Character {
public:
    Lori(GameMap& map, Vector<int16_t> pos, int16_t characterId);

    void specialAttack(float time) override;
};

#endif  // LORI_H
