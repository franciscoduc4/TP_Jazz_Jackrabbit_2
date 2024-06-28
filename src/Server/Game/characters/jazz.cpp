#include "jazz.h"

#include <iostream>

#include "../enemies/enemy.h"
#include "../gameMap.h"

Jazz::Jazz(GameMap& gameMap, Vector<uint32_t> pos, uint8_t playerId, uint32_t width,
           uint32_t height):
        Character(gameMap, pos, playerId, CharacterType::JAZZ,
                  ServerConfig::getJazzHorizontalSpeed(), ServerConfig::getJazzSprintSpeed(),
                  ServerConfig::getJazzVerticalSpeed(), ServerConfig::getJazzJumpHeight(),
                  ServerConfig::getJazzShootCooldownTime(), width, height) {}

void Jazz::realizeSpecialAttack(float time) {
    std::cout << "[SPECIAL ATTACK] Jazz realiza un puñetazo hacia arriba" << std::endl;

    // Realiza un salto
    this->jump(0);

    Vector<uint32_t> attackPos = getPosition();
    attackPos.y -= getHeight(); 

    uint32_t rangeX = ServerConfig::getJazzSpecialAttackRangeX();
    uint32_t rangeY = ServerConfig::getJazzSpecialAttackRangeY();

    auto entities = gameMap.getObjectsInAreaRange(attackPos, rangeX, rangeY);

    for (auto& entity : entities) {
        if (entity->getType() == EntityType::ENEMY) {
            auto enemy = std::dynamic_pointer_cast<Enemy>(entity);
            if (enemy) {
                enemy->recvDamage(ServerConfig::getJazzSpecialAttackDamage(), 0);
                std::cout << "[SPECIAL ATTACK] Jazz golpea al enemigo ID: " << static_cast<int>(enemy->getId()) << std::endl;
                if (enemy->isDead()) {
                    score += enemy->getPointsValue();
                    gameMap.removeEnemy(enemy->getId());
                }
            }
        }
    }
}
