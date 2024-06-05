#ifndef TILE_DTO_H_
#define TILE_DTO_H_

#include "../sprite.h"

#include "gameElement.h"

class TileDTO: public GameElementDTO {
private:
    uint16_t x;
    uint16_t y;
    Sprite currentSprite;

public:
    TileDTO(uint16_t x, uint16_t y, const Sprite& currentSprite);
    uint16_t getX() const;
    uint16_t getY() const;
    Sprite getSprite() const;
    //~TileDTO();
};

#endif  // TILE_DTO_H_
