#ifndef GEM_H
#define GEM_H

#include "item.h"

class Gem : public Item {
public:
    Gem(GameMap& gameMap, Vector<uint32_t> position);

    void update(double deltaTime) override;

    ItemType getItemType() const { return ItemType::GEM;}
};

#endif // GEM_H
