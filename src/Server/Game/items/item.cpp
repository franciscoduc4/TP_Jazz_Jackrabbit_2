#include "item.h"
Item::Item(GameMap& gameMap, Vector<uint32_t> position, uint32_t width, uint32_t height)
    : Entity(position, 0, 1, Direction::UP, EntityType::ITEM), position(position) {}

    
void Item::update(double deltaTime) {
    // Do nothing
}

ItemDTO Item::getDTO() {
    return ItemDTO{position.x, position.y, getItemType()};
}
