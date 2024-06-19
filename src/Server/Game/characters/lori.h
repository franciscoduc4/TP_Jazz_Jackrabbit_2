#ifndef LORI_H
#define LORI_H

#include "character.h"

class Lori: public Character {
public:
    Lori(GameMap& map, Vector<uint32_t> pos, uint8_t playerId);

    void specialAttack(float time) override;
};

#endif  // LORI_H
