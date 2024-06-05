#ifndef ITEM_DTO_H_
#define ITEM_DTO_H_


#include "gameElement.h"

class ItemDTO: public GameElementDTO {
private:
    uint16_t x;
    uint16_t y;

public:
    ItemDTO(uint16_t x, uint16_t y);
    uint16_t getX() const;
    uint16_t getY() const;


    Sprite getSprite() const;

};

#endif  // ITEM_DTO_H_
