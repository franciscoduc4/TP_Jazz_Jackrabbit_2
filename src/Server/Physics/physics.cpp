#include "physics.h"


void Physics::update(std::shared_ptr<GameStatus> gameStatus, float deltaTime) {
    for (auto& character: gameStatus->getCharacters()) {
        character->update(deltaTime);
        handleCollisions(character, gameStatus);
    }

    for (auto& enemy: gameStatus->getEnemies()) {
        enemy->update(deltaTime);
    }

    handleProjectiles(gameStatus, deltaTime);
}

void Physics::handleCollisions(std::shared_ptr<Character> character,
                               std::shared_ptr<GameStatus> gameStatus) {
    // Collision with obstacles
    for (const auto& obstacle: gameStatus->getObstacles()) {
        if (obstacle->isColliding(character)) {
            character->takeDamage(obstacle->getDamage());
        }
    }

    // Collision with platforms
    for (const auto& platform: gameStatus->getPlatforms()) {
        if (platform->isColliding(character)) {
            character->land();
        }
    }
}

void Physics::handleProjectiles(std::shared_ptr<GameStatus> gameStatus, float deltaTime) {
    auto& projectiles = gameStatus->getProjectiles();

    for (auto& projectile: projectiles) {
        projectile->update(deltaTime);
        for (auto& enemy: gameStatus->getEnemies()) {
            if (projectile->isColliding(enemy->getSize(), enemy->getPosition())) {
                enemy->takeDamage(projectile->getDamage());
                projectile->setInactive();
            }
        }
    }

    projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(),
                                     [](auto& projectile) { return !projectile->isActive(); }),
                      projectiles.end());
}
