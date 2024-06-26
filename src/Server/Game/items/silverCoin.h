#ifndef SILVERCOIN_H
#define SILVERCOIN_H

#include "item.h"

class SilverCoin : public Item {
public:
    SilverCoin(GameMap& gameMap, Vector<uint32_t> position, uint32_t width, uint32_t height);

    void update(double deltaTime) override;

    ItemType getItemType() const override { return ItemType::SILVER_COIN;}

    uint32_t getValue() const override { return ServerConfig::getItemSilverCoinValue(); }
    uint32_t getWidth() const override { return ServerConfig::getItemSilverCoinWidth(); }
    uint32_t getHeight() const override { return ServerConfig::getItemSilverCoinHeight(); }
    
};

#endif // SILVERCOIN_H
