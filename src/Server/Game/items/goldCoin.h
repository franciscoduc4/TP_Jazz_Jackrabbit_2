#ifndef GOLDCOIN_H
#define GOLDCOIN_H

#include "item.h"

class GoldCoin : public Item {
public:
    GoldCoin(GameMap& gameMap, Vector<uint32_t> position, uint32_t width, uint32_t height);

    void update(double deltaTime) override;

    ItemType getItemType() const override { return ItemType::GOLD_COIN; }

    uint32_t getValue() const override { return ServerConfig::getItemGoldCoinValue(); }
    uint32_t getWidth() const override { return ServerConfig::getItemGoldCoinWidth(); }
    uint32_t getHeight() const override { return ServerConfig::getItemGoldCoinHeight(); }
};

#endif // GOLDCOIN_H
