#ifndef JAZZ_H
#define JAZZ_H

#include "character.h"


class Jazz: public Character {
public:
    Jazz(GameMap& map, Vector<uint32_t> pos, uint8_t playerId, uint32_t width, uint32_t height);

    void specialAttack(float time) override;

    void update(double deltaTime) override;
};

#endif  // JAZZ_H
