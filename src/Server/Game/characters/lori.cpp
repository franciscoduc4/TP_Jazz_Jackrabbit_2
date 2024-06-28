#include "lori.h"
#include "../gameMap.h"
#include "../enemies/enemy.h"
#include <iostream>

Lori::Lori(GameMap& gameMap, Vector<uint32_t> pos, uint8_t playerId, uint32_t width, uint32_t height)
    : Character(gameMap, pos, playerId, CharacterType::LORI, ServerConfig::getLoriHorizontalSpeed(),
                ServerConfig::getLoriSprintSpeed(), ServerConfig::getLoriVerticalSpeed(),
                ServerConfig::getLoriJumpHeight(), ServerConfig::getLoriShootCooldownTime(), width, height) {}


void Lori::realizeSpecialAttack(float time) {
    Vector<uint32_t> pos = getPosition();
    pos.x += getDirection() == Direction::RIGHT ? getWidth() : -getWidth();

    uint32_t rangeX = ServerConfig::getLoriSpecialAttackRangeX();
    uint32_t rangeY = ServerConfig::getLoriSpecialAttackRangeY();

    auto entities = gameMap.getObjectsInAreaRange(pos, rangeX, rangeY);
    for (auto& entity : entities) {
        if (entity->getType() == EntityType::ENEMY) {
            auto enemy = std::dynamic_pointer_cast<Enemy>(entity);
            std::cout << "Lori special attack enemy detected" << std::endl;
            if (enemy) {
                enemy->recvDamage(ServerConfig::getJazzSpecialAttackDamage(), 0);
                std::cout << "[SPECIAL ATTACK] Jazz golpea al enemigo ID: " << static_cast<int>(enemy->getId())
                          << std::endl;
                if (enemy->isDead()) {
                    score += enemy->getPointsValue();
                    gameMap.removeEnemy(enemy->getId());
                }
            }
        }
    }
}

