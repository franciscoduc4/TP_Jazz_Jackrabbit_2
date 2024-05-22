#ifndef PHYSICS_H_
#define PHYSICS_H_

#include "vector.h"
#include "character.h"
#include "platform.h"
#include "projectile.h"
#include "enemy.h"
#include <vector>

class Physics {
public:
    static void update(Character& character, const std::vector<Platform>& platforms, 
    loat deltaTime) {
        character.update(deltaTime);

        for (const auto& platform : platforms) {
            if (platform.isColliding(character)) {
                // Resolver colisión
                Vector charPos = character.getPosition();
                charPos.y = platform.getPosition().y + platform.getSize().y;
                character.setPosition(charPos);
                character.setVelocity({character.getVelocity().x, 0});
                character.land();
            }
        }
    }

    static void handleProjectileCollisions(std::vector<Projectile>& projectiles, 
        std::vector<Enemy>& enemies) {
        for (auto& projectile : projectiles) {
            if (!projectile.getIsActive()) continue;

            for (auto& enemy : enemies) {
                if (!enemy.getIsAlive()) continue;

                if (isColliding(projectile, enemy)) {
                    enemy.takeDamage(projectile.getDamage());
                    projectile.deactivate();
                }
            }
        }
    }

private:
    static bool isColliding(const Projectile& projectile, const Enemy& enemy) {
        Vector projPos = projectile.getPosition();
        Vector enemyPos = enemy.getPosition();
        // Asumimos que el proyectil y el enemigo tienen un tamaño de 1x1
        return (projPos.x < enemyPos.x + 1 && projPos.x + 1 > enemyPos.x &&
                projPos.y < enemyPos.y + 1 && projPos.y + 1 > enemyPos.y);
    }
};


#endif // PHYSICS_H_

