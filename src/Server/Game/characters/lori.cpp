#include "lori.h"
#include "../gameMap.h"
#include "../enemies/enemy.h"
#include <iostream>

Lori::Lori(GameMap& gameMap, Vector<uint32_t> pos, uint8_t playerId, uint32_t width, uint32_t height)
    : Character(gameMap, pos, playerId, CharacterType::LORI, ServerConfig::getLoriHorizontalSpeed(),
                ServerConfig::getLoriSprintSpeed(), ServerConfig::getLoriVerticalSpeed(),
                ServerConfig::getLoriJumpHeight(), ServerConfig::getLoriShootCooldownTime(), width, height) {}


void Lori::specialAttack() {
    std::cout << "[SPECIAL ATTACK] Lori realiza una patada de corto alcance" << std::endl;
    Vector<uint32_t> pos = getPosition();
    pos.x += getDirection() == Direction::RIGHT ? getWidth() : -getWidth(); // Ajuste según la dirección

    auto entities = gameMap.getObjectsInAreaRange(pos, 20); // Obtiene entidades en el rango de ataque
    for (auto& entity : entities) {
        if (entity->getType() == EntityType::ENEMY) {
            auto enemy = std::dynamic_pointer_cast<Enemy>(entity);
            if (enemy) {
                enemy->recvDamage(80, 0); // Asigna un valor de daño adecuado
                std::cout << "[SPECIAL ATTACK] Lori patea al enemigo ID: " << static_cast<int>(enemy->getId()) << std::endl;
            }
        }
    }
}

void Lori::update(double deltaTime) {
    // Implementar lógica específica de actualización para Lori si es necesario
}
