#ifndef ITEM_DTO_H_
#define ITEM_DTO_H_

#include "../sprite.h"

#include "gameElement.h"
#include "../Types/item.h"

class ItemDTO: public GameElementDTO {
private:
    uint32_t x;
    uint32_t y;
    ItemType type;

public:
    ItemDTO(const uint32_t& x, const uint32_t& y, const ItemType& type);
    uint32_t getX() const;
    uint32_t getY() const;
    ItemType getType() const;

};

#endif  // ITEM_DTO_H_
