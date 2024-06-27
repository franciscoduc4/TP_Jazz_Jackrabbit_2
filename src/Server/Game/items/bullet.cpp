#include "bullet.h"

Bullet::Bullet(GameMap& gameMap, Vector<uint32_t> position, uint32_t width, uint32_t height):
        Item(gameMap, position, width, height) {}

void Bullet::update(double deltaTime) {}