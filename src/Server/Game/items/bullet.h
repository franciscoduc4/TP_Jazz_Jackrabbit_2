#ifndef BULLET_H
#define BULLET_H

#include "item.h"

class Bullet: public Item {
public:
    Bullet(GameMap& gameMap, Vector<uint32_t> position, uint32_t width, uint32_t height);

    void update(double deltaTime) override;

    ItemType getItemType() const override { return ItemType::BULLET; }

    uint32_t getValue() const override { return ServerConfig::getItemBulletValue(); }
    uint32_t getWidth() const override { return ServerConfig::getItemBulletWidth(); }
    uint32_t getHeight() const override { return ServerConfig::getItemBulletHeight(); }
};

#endif  // BULLET_H
