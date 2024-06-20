#include "character.h"

Character::Character(uint8_t playerId, CharacterType type, Vector<uint32_t> position):
        Entity(position, playerId, ServerConfig::getCharacterInitialHealth(), Direction::RIGHT,
               EntityType::CHARACTER),
        type(type),
        position(std::make_unique<Position>(position)),
        movement() {}

void Character::update(Direction direction) { movement.accelerate(direction); }

void Character::move() { movement.move(position); }

PlayerDTO Character::getDTO() const {
    std::cout << "Position getX: " << position->getX() << " getY: " << position->getY() << "\n";
    return PlayerDTO{position->getX(),          position->getY(), id, health, 0, 0, type,
                     CharacterStateEntity::IDLE};
}