#include "jazz.h"
#include "../gameMap.h"
#include "../enemies/enemy.h"
#include <iostream>

Jazz::Jazz(GameMap& gameMap, Vector<uint32_t> pos, uint8_t playerId, uint32_t width, uint32_t height)
    : Character(gameMap, pos, playerId, CharacterType::JAZZ, ServerConfig::getJazzHorizontalSpeed(),
                ServerConfig::getJazzSprintSpeed(), ServerConfig::getJazzVerticalSpeed(),
                ServerConfig::getJazzJumpHeight(), ServerConfig::getJazzShootCooldownTime(), width, height) {}


void Jazz::specialAttack() {
    std::cout << "[SPECIAL ATTACK] Jazz realiza un puñetazo hacia arriba" << std::endl;
    // Hacer que Jazz salte hacia arriba
    if (!isJumping()) {
        jumping = true;
        currentSpeed.y = -jumpHeight; // Ajuste para el salto
    }

    Vector<uint32_t> attackPos = getPosition();
    attackPos.y -= getHeight(); // Ajuste para el ataque hacia arriba
    std::cout << "[SPECIAL ATTACK] Posición de ataque: " << attackPos.x << ", " << attackPos.y << std::endl;

    auto entities = gameMap.getObjectsInVerticalRange(attackPos, 300); 
    std::cout << "[SPECIAL ATTACK] Enemigos en rango: " << entities.size() << std::endl;
    
    for (auto& entity : entities) {
        if (entity->getType() == EntityType::ENEMY) {
            auto enemy = std::dynamic_pointer_cast<Enemy>(entity);
            if (enemy) {
                enemy->recvDamage(400, 0); // Asigna un valor de daño adecuado
                std::cout << "[SPECIAL ATTACK] Jazz golpea al enemigo ID: " << static_cast<int>(enemy->getId()) << std::endl;
            }
        }
    }
}

void Jazz::update(double deltaTime) {
    // Implementar lógica específica de actualización para Jazz si es necesario
}
