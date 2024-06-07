#include "item.h"

ItemDTO::ItemDTO(uint16_t x, uint16_t y, ItemType type): 
        x(x),
        y(y),
        type(type){}


uint16_t ItemDTO::getX() const { return x; }
    
uint16_t ItemDTO::getY() const { return y; }

ItemType ItemDTO::getType() const { return type; }
