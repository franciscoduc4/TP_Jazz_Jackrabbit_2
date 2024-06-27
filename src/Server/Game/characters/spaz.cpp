#include "spaz.h"
#include "../gameMap.h"
#include "../enemies/enemy.h"
#include <iostream>

// #define CONFIG ServerConfig::getInstance()


Spaz::Spaz(GameMap& gameMap, Vector<uint32_t> pos, uint8_t playerId, uint32_t width, uint32_t height)
    : Character(gameMap, pos, playerId, CharacterType::SPAZ, ServerConfig::getSpazHorizontalSpeed(),
                ServerConfig::getSpazSprintSpeed(), ServerConfig::getSpazVerticalSpeed(),
                ServerConfig::getSpazJumpHeight(), ServerConfig::getLoriShootCooldownTime(), width, height) {}


void Spaz::specialAttack() {
    std::cout << "[SPECIAL ATTACK] Spaz realiza una patada lateral" << std::endl;
    float distance = getHorizontalSpeed() * 3.0f;
    Vector<uint32_t> pos = getPosition();
    Direction dir = getDirection();

    // Mueve a Spaz en la dirección actual
    if (dir == Direction::LEFT) {
        pos.x -= distance;
    } else if (dir == Direction::RIGHT) {
        pos.x += distance;
    }

    // Ajustar el rango de búsqueda de enemigos
    uint32_t attackRange = 80;  // Ajusta este valor según sea necesario

    // Obtiene las entidades en el área de la nueva posición
    auto entities = gameMap.getObjectsInAreaRange(pos, attackRange);
    for (auto& entity : entities) {
        if (entity->getType() == EntityType::ENEMY) {
            auto enemy = std::dynamic_pointer_cast<Enemy>(entity);
            enemy->recvDamage(50, 0); // Asigna un valor de daño adecuado
            std::cout << "[SPECIAL ATTACK] Spaz golpea al enemigo ID: " << static_cast<int>(enemy->getId()) << std::endl;
        }
    }

    // Actualiza la posición de Spaz
    setPosition(pos);
}

void Spaz::update(double deltaTime) {
    // Lógica de actualización específica de Spaz, si es necesario
}
