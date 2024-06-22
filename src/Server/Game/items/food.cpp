#include "food.h"

Food::Food(GameMap& gameMap, Vector<uint32_t> position, uint32_t width, uint32_t height)
    : Item(gameMap, position, width, height) {}

void Food::update(double deltaTime) {
    // Implementar lógica específica para Food
}
