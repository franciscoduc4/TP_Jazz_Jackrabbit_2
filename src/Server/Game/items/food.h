#ifndef FOOD_H
#define FOOD_H

#include "item.h"

class Food : public Item {
public:
    Food(GameMap& gameMap, Vector<uint32_t> position);

    void update(double deltaTime) override;
};

#endif // FOOD_H
