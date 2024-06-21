
#include "obstacle.h"

Obstacle::Obstacle(GameMap& gameMap, Vector<uint32_t> position) : Entity{{0,0}, 0, 0, Direction::UP, EntityType::OBSTACLE} {}

// No es necesario implementar update aquí, ya que es una clase abstracta.

