#ifndef JAZZ_H
#define JAZZ_H

#include "character.h"


class Jazz: public Character {
public:
    Jazz(GameMap& map, Vector<int16_t> pos, int16_t characterId);

    void specialAttack(float time) override;
};

#endif  // JAZZ_H
