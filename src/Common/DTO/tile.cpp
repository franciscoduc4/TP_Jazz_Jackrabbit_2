#include "tile.h"

TileDTO::TileDTO(uint16_t x, uint16_t y) : 
    x(x), y(y) {}

uint16_t TileDTO::getX() const { return x; }

uint16_t TileDTO::getY() const { return y; }


