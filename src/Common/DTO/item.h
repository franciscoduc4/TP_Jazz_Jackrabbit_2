#ifndef ITEM_DTO_H_
#define ITEM_DTO_H_

#include <cstdint>
#include <memory>

#include "../sprite.h"
#include "dto.h"
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
    ItemType getItemType() const;

    virtual std::unique_ptr<DTO> clone() const override;
};

#endif  // ITEM_DTO_H_
