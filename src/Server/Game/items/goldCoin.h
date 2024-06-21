#ifndef GOLDCOIN_H
#define GOLDCOIN_H

#include "item.h"

class GoldCoin : public Item {
public:
    GoldCoin(GameMap& gameMap, Vector<uint32_t> position);

    void update(double deltaTime) override;
};

#endif // GOLDCOIN_H
