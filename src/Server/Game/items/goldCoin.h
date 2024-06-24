#ifndef GOLDCOIN_H
#define GOLDCOIN_H

#include "item.h"

class GoldCoin : public Item {
public:
    GoldCoin(GameMap& gameMap, Vector<uint32_t> position, uint32_t width, uint32_t height);

    void update(double deltaTime) override;

    ItemType getItemType() const { return ItemType::GOLD_COIN; }

    uint32_t getValue() const { return 30; }
};

#endif // GOLDCOIN_H
