#ifndef ITEMS_ITEM_H
#define ITEMS_ITEM_H

#include "../entity.h"
#include "../../../Common/vector.h"
#include "../../../Common/Types/item.h"
#include "../../../Common/DTO/item.h"
#include "../../../Common/Config/ServerConfig.h"


class GameMap;
class Item : public Entity {
private:
    Vector<uint32_t> position;
public:
    Item(GameMap& gameMap, Vector<uint32_t> position, uint32_t width, uint32_t height);

    void update(double deltaTime) override;

    ItemDTO getDTO();

    virtual ItemType getItemType() const = 0;
    virtual uint32_t getValue() const = 0;
    virtual uint32_t getWidth() const = 0;
    virtual uint32_t getHeight() const = 0;

    
};

#endif // ITEMS_ITEM_H
