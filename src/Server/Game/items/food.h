#ifndef FOOD_H
#define FOOD_H

#include "item.h"

class Food : public Item {
public:
    Food(GameMap& gameMap, Vector<uint32_t> position, uint32_t width, uint32_t height);

    void update(double deltaTime) override;

    ItemType getItemType() const  { return ItemType::FOOD;}
};

#endif // FOOD_H
