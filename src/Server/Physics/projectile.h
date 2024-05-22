#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "vector.h"
//#include "character.h"

class Projectile {
    private:
        Vector position;
        Vector velocity;
        int damage;
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
        Vector getPosition() const {
            return position;
        }

        int getDamage() const {
            return damage;
        }

};
#endif // PROJECTILE_H_
