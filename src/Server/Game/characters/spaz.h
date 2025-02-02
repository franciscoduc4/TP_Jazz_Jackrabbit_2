#ifndef SPAZ_H
#define SPAZ_H

#include "character.h"

class Spaz: public Character {
public:
    Spaz(GameMap& map, Vector<uint32_t> pos, uint8_t playerId, uint32_t width, uint32_t height);

    void realizeSpecialAttack(float time) override;

    void update(double deltaTime) {};
};

#endif  // SPAZ_H
