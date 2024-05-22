#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "vector.h"
#include "weapon.h"


class Character {
protected:
    Vector position;
    Vector velocity;
    Vector acceleration;
    Vector size;  // ancho x alto
    bool isJumping;
    float gravity;
    bool isFalling;
    float jumpForce;
    bool isRunning;
    int health;
    int maxHealth;
    std::vector<std::shared_ptr<Weapon>> weapons;
    int currentWeaponIndex;

public:
    Character():
            position(0, 0),
            velocity(0, 0),
            acceleration(0, 0),
            size(size),
            isJumping(false),
            gravity(-9.8f),
            isFalling(false),
            jumpForce(15.0f),
            isRunning(false),
            health(health),
            maxHealth(100),
            currentWeaponIndex(0) {}

    virtual ~Character() = default;

    static std::unique_ptr<Character> createCharacter(const std::string& characterType);

    void applyGravity() {
        if (isJumping) {
            acceleration.y = gravity;
        }
    }

    void handleCollisions() {
        if (position.y < 0) {
            position.y = 0;
            velocity.y = 0;
            isJumping = false;
        }
        if (position.x < 0) {
            position.x = 0;
            velocity.x = 0;
        }
    }

    virtual void update(float deltaTime) {
        applyGravity();
        velocity += acceleration * deltaTime;
        position += velocity * deltaTime;
        // Reset acceleration
        acceleration = Vector(0, 0);
    }

    void jump() {
        if (!isJumping && !isFalling) {
            velocity.y = -jumpForce;
            isJumping = true;
        }
    }

    void move(float direction) { velocity.x = direction * (isRunning ? 2.0f : 1.0f); }

    void startRunning() { isRunning = true; }

    void stopRunning() { isRunning = false; }

    void takeDamage(int damage) {
        health -= damage;
        if (health <= 0) {
            die();
        }
    }

    void die() {
        // respawn
        health = maxHealth;
        position = Vector(0, 0);
        isJumping = false;
        isFalling = false;
        isRunning = false;
    }

    Vector getPosition() const { return position; }

    void setPosition(const Vector& pos) { position = pos; }

    Vector getVelocity() const { return velocity; }

    void setVelocity(const Vector& vel) { velocity = vel; }

    void land() { isJumping = false; }

    void addWeapon(std::shared_ptr<Weapon> weapon) { weapons.push_back(weapon); }

    void switchWeapon(int index) {
        if (index >= 0 && index < weapons.size()) {
            currentWeaponIndex = index;
        }
    }

    std::unique_ptr<Projectile> shoot(float currentTime, Vector direction) {
        if (!weapons.empty()) {
            return weapons[currentWeaponIndex]->shoot(position, direction, currentTime);
        }
        return nullptr;
    }

    Vector getSize() const { return size; }

    virtual void specialAttack() = 0;
};

// Definición de las clases específicas
class Jazz: public Character {
public:
    void specialAttack() override {
        // Implementar habilidad especial de Jazz
    }
};

class Spaz: public Character {
public:
    void specialAttack() override {
        // Implementar habilidad especial de Spaz
    }
};

class Lori: public Character {
public:
    Lori(){};
    void specialAttack() override {
        // Implementar habilidad especial de Lori
    }
};

#endif  // CHARACTER_H_
