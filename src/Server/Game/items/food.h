#ifndef FOOD_H
#define FOOD_H

#include "item.h"

class Food : public Item {
public:
    Food(GameMap& gameMap, Vector<uint32_t> position, uint32_t width, uint32_t height);

    void update(double deltaTime) override;

    ItemType getItemType() const  { return ItemType::FOOD;}

    uint32_t getValue() const { return 10; }

    uint32_t getWidth() const { return 1; }
    uint32_t getHeight() const { return 1; }
};

#endif // FOOD_H
