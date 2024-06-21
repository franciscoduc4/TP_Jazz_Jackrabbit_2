#ifndef TILE_DTO_H_
#define TILE_DTO_H_

#include "../../Common/sprite.h"

#include "gameElement.h"

class TileDTO: public GameElementDTO {
private:
    uint32_t x;
    uint32_t y;
    
public:
    TileDTO(const uint32_t& x, const uint32_t& y);
    uint32_t getX() const;
    uint32_t getY() const;
    virtual std::unique_ptr<DTO> clone() const override;

};

#endif  // TILE_DTO_H_
