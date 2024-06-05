#ifndef ITEM_DTO_H_
#define ITEM_DTO_H_

#include "../sprite.h"

#include "gameElement.h"

class ItemDTO: public GameElementDTO {
private:
    uint16_t x;
    uint16_t y;
    Sprite currentSprite;

public:
    ItemDTO(uint16_t x, uint16_t y, const Sprite& currentSprite);
    uint16_t getX() const;
    uint16_t getY() const;

    Sprite getSprite() const;
    //~ItemDTO();
};

#endif  // ITEM_DTO_H_
