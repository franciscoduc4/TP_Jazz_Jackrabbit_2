#include "tile.h"

TileDTO::TileDTO(const uint32_t& x, const uint32_t& y) :
        GameElementDTO(ElementType::TILE), x(x), y(y) {}

uint32_t TileDTO::getX() const { return x; }

uint32_t TileDTO::getY() const { return y; }

std::unique_ptr<DTO> TileDTO::clone() const {
    return std::make_unique<TileDTO>(*this);
}
