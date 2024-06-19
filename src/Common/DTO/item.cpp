#include "item.h"

ItemDTO::ItemDTO(const uint32_t& x, const uint32_t& y, const ItemType& type) :
        GameElementDTO(ElementType::ITEM),
        x(x),
        y(y),
        type(type){}


uint32_t ItemDTO::getX() const { return x; }
    
uint32_t ItemDTO::getY() const { return y; }

ItemType ItemDTO::getType() const { return type; }
