#ifndef JAZZ_H
#define JAZZ_H

#include "character.h"


class Jazz: public Character {
public:
    Jazz(GameMap& map, Vector<uint8_t> pos, uint8_t playerId);

    void specialAttack(float time) override;
};

#endif  // JAZZ_H
