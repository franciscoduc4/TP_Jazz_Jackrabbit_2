#include "spaz.h"
#include "../gameMap.h"
#include "../enemies/enemy.h"
#include <iostream>

// #define CONFIG ServerConfig::getInstance()


Spaz::Spaz(GameMap& gameMap, Vector<uint32_t> pos, uint8_t playerId, uint32_t width, uint32_t height)
    : Character(gameMap, pos, playerId, CharacterType::SPAZ, ServerConfig::getSpazHorizontalSpeed(),
                ServerConfig::getSpazSprintSpeed(), ServerConfig::getSpazVerticalSpeed(),
                ServerConfig::getSpazJumpHeight(), ServerConfig::getLoriShootCooldownTime(), width, height) {}


void Spaz::realizeSpecialAttack(float time) {
    float distance = getHorizontalSpeed() * ServerConfig::getSpazSpecialAttackSpeed();
    Vector<uint32_t> pos = getPosition();
    Direction dir = getDirection();

    if (dir == Direction::LEFT) {
        pos.x -= distance;
    } else if (dir == Direction::RIGHT) {
        pos.x += distance;
    }

    uint32_t rangeX = ServerConfig::getSpazSpecialAttackRangeX();
    uint32_t rangeY = ServerConfig::getSpazSpecialAttackRangeY();

    auto entities = gameMap.getObjectsInAreaRange(pos, rangeX, rangeY);
    for (auto& entity : entities) {
        if (entity->getType() == EntityType::ENEMY) {
            auto enemy = std::dynamic_pointer_cast<Enemy>(entity);
            std::cout << "Spaz special attack enemy detected" << std::endl;
            if (enemy) {
                enemy->recvDamage(ServerConfig::getJazzSpecialAttackDamage(), 0);
                std::cout << "[SPECIAL ATTACK] Spaz golpea al enemigo ID: " << static_cast<int>(enemy->getId())
                          << std::endl;
                if (enemy->isDead()) {
                    score += enemy->getPointsValue();
                    gameMap.removeEnemy(enemy->getId());
                }
            }
        }
    }
    setPosition(pos);
}
