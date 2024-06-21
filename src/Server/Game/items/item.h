#ifndef ITEMS_ITEM_H
#define ITEMS_ITEM_H

#include "../entity.h"
#include "../../../Common/vector.h"
#include "../../../Common/Types/item.h"

class GameMap;

class Item : public Entity {
public:
    Item(GameMap& gameMap, Vector<uint32_t> position);

    virtual void update(double deltaTime) override = 0;
};

#endif // ITEM_H
