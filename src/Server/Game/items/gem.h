#ifndef GEM_H
#define GEM_H

#include "item.h"

class Gem : public Item {
public:
    Gem(GameMap& gameMap, Vector<uint32_t> position, uint32_t width, uint32_t height);

    void update(double deltaTime) override;

    ItemType getItemType() const { return ItemType::GEM;}

    uint32_t getValue() const { return 50; }

    uint32_t getWidth() const { return 1; }
    uint32_t getHeight() const { return 1; }
};

#endif // GEM_H
