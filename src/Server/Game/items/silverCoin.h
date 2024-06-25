#ifndef SILVERCOIN_H
#define SILVERCOIN_H

#include "item.h"

class SilverCoin : public Item {
public:
    SilverCoin(GameMap& gameMap, Vector<uint32_t> position, uint32_t width, uint32_t height);

    void update(double deltaTime) override;

    ItemType getItemType() const { return ItemType::SILVER_COIN;}

    uint32_t getValue() const { return 10; }

    uint32_t getWidth() const { return 1; }
    uint32_t getHeight() const { return 1; }
    
};

#endif // SILVERCOIN_H
