#ifndef ITEM_DTO_H_
#define ITEM_DTO_H_

#include "../sprite.h"

#include "gameElement.h"
#include "../Types/item.h"
class ItemDTO: public GameElementDTO {
private:
    uint16_t x;
    uint16_t y;
    ItemType type;

public:
    ItemDTO(uint16_t x, uint16_t y, ItemType type);
    uint16_t getX() const;
    uint16_t getY() const;
    ItemType getType() const;

};

#endif  // ITEM_DTO_H_
