#include "tile.h"

TileDTO::TileDTO(uint16_t x, uint16_t y, const Sprite& currentSprite) : 
    x(x), y(y), currentSprite(currentSprite) {}

uint16_t TileDTO::getX() const { return x; }

uint16_t TileDTO::getY() const { return y; }

Sprite TileDTO::getSprite() const { return currentSprite; }

