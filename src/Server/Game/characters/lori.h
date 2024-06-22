#ifndef LORI_H
#define LORI_H

#include "character.h"

class Lori: public Character {
public:
    Lori(GameMap& map, Vector<uint32_t> pos, uint8_t playerId, uint32_t width, uint32_t height);

    void specialAttack(float time) override;

    void update(double deltaTime) override;
};

#endif  // LORI_H
