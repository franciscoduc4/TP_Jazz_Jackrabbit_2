#ifndef SILVERCOIN_H
#define SILVERCOIN_H

#include "item.h"

class SilverCoin : public Item {
public:
    SilverCoin(GameMap& gameMap, Vector<uint32_t> position);

    void update(double deltaTime) override;

    ItemType getItemType() const { return ItemType::SILVER_COIN;}
    
};

#endif // SILVERCOIN_H
