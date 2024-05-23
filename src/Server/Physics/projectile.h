#ifndef PROJECTILE_H_
#define PROJECTILE_H_


#include "../../Common/Models/vector.h"
#include <string>
// #include "character.h"

class Projectile {
private:
    Vector position;
    Vector velocity;
    int damage;
    bool active;

public:
    Projectile(Vector startPosition, Vector startVelocity, int damage):
            position(startPosition), velocity(startVelocity), damage(damage) {}

    void update(float deltaTime) {
        position += velocity * deltaTime;
        // Lógica adicional para detectar colisiones y desactivar el proyectil
    }

    // void onCollision(Character& target) {
    //     target.takeDamage(damage);
    //     //implemetnar logica para destruir el proyectil
    // }

    bool isColliding(Vector targetPosition, Vector targetSize) const {
        return (position.x < targetPosition.x + targetSize.x && position.x > targetPosition.x &&
                position.y < targetPosition.y + targetSize.y && position.y > targetPosition.y);
    }

    Vector getPosition() const { return position; }

    int getDamage() const { return damage; }

    bool isActive() const { return active; }

    void setInactive() { active = false; }

    std::string serialize() const {
        return std::to_string(position.x) + " " + std::to_string(position.y) + " " +
               std::to_string(velocity.x) + " " + std::to_string(velocity.y) + " " +
               std::to_string(damage) + " " + std::to_string(active);
    }
};
#endif  // PROJECTILE_H_
