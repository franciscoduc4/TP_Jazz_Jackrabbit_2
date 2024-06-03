#include "item.h"

ItemDTO::ItemDTO(uint16_t x, uint16_t y, const Sprite& currentSprite):
        x(x), y(y), currentSprite(currentSprite) {}

uint16_t ItemDTO::getX() const { return x; }

uint16_t ItemDTO::getY() const { return y; }

Sprite ItemDTO::getSprite() const { return currentSprite; }

ItemDTO::~ItemDTO() {}