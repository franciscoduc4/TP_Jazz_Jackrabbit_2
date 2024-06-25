#ifndef TILE_DTO_H_
#define TILE_DTO_H_

#include "../../Common/sprite.h"
#include "../Types/obstacles.h"
#include "gameElement.h"

class TileDTO: public GameElementDTO {
private:
    uint32_t x;
    uint32_t y;
    ObstacleType obstacleType;

    
public:
    TileDTO(const uint32_t& x, const uint32_t& y, const ObstacleType& obstacleType);
    uint32_t getX() const;
    uint32_t getY() const;
    ObstacleType getObstacleType() { return obstacleType;}
    virtual std::unique_ptr<DTO> clone() const override;

};

#endif  // TILE_DTO_H_
