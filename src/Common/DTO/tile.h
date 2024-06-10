#ifndef TILE_DTO_H_
#define TILE_DTO_H_

#include "../../Common/sprite.h"

#include "gameElement.h"

class TileDTO: public GameElementDTO {
private:
    uint16_t x;
    uint16_t y;
    
public:
    TileDTO(uint16_t x, uint16_t y);
    uint16_t getX() const;
    uint16_t getY() const;

};

#endif  // TILE_DTO_H_
