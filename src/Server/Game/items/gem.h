#ifndef GEM_H
#define GEM_H

#include "item.h"

class Gem : public Item {
public:
    Gem(GameMap& gameMap, Vector<uint32_t> position, uint32_t width, uint32_t height);

    void update(double deltaTime) override;

    ItemType getItemType() const override { return ItemType::GEM;}

    uint32_t getValue() const override { return ServerConfig::getItemGemValue(); }
    uint32_t getWidth() const override { return ServerConfig::getItemGemWidth(); }
    uint32_t getHeight() const override { return ServerConfig::getItemGemHeight(); }
};

#endif // GEM_H
