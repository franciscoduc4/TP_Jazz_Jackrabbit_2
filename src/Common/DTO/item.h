#ifndef ITEM_H_
#define ITEM_H_

#include "gameElement.h"
#include "../sprite.h"

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
        ~ItemDTO();
};

#endif // ITEM_H_
