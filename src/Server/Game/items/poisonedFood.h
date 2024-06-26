#ifndef POISONED_FOOD_H
#define POISONED_FOOD_H

#include "item.h"

class PoisonedFood : public Item {
public:
    PoisonedFood(GameMap& gameMap, Vector<uint32_t> position, uint32_t width, uint32_t height);

    void update(double deltaTime) override;

    ItemType getItemType() const override  { return ItemType::POISONED_FOOD;}

    uint32_t getValue() const override { return ServerConfig::getItemFoodValue(); }
    uint32_t getWidth() const override { return ServerConfig::getItemFoodWidth(); }
    uint32_t getHeight() const override { return ServerConfig::getItemFoodHeight(); }
};

#endif // FOOD_H
