#ifndef GOLDCOIN_H
#define GOLDCOIN_H

#include "item.h"

class GoldCoin : public Item {
public:
    GoldCoin(GameMap& gameMap, Vector<uint32_t> position);

    void update(double deltaTime) override;

    ItemType getItemType() const { return ItemType::GOLD_COIN; }
};

#endif // GOLDCOIN_H
