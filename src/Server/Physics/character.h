#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "../../Common/Models/vector.h"
#include "weapon.h"

class Enemy;
class Obstacle;

class Character {
protected:
    int id;
    Vector position;
    Vector velocity;
    Vector acceleration;
    Vector size;  // ancho x alto
    bool jumping;
    float gravity;
    bool falling;
    float jumpForce;
    bool running;
    int health;
    int maxHealth;
    std::vector<std::shared_ptr<Weapon>> weapons;
    int currentWeaponIndex;

public:
    Character():
            id(0),
            position(0, 0),
            velocity(0, 0),
            acceleration(0, 0),
            size(size),
            jumping(false),
            gravity(-9.8f),
            falling(false),
            jumpForce(15.0f),
            running(false),
            health(health),
            maxHealth(100),
            currentWeaponIndex(0) {}

    virtual ~Character() = default;

    static std::unique_ptr<Character> createCharacter(const std::string& characterType);

    int getId() const { return id; }

    void applyGravity() {
        if (jumping) {
            acceleration.y = gravity;
        }
    }

    void handleCollisions() {
        if (position.y < 0) {
            position.y = 0;
            velocity.y = 0;
            jumping = false;
        }
        if (position.x < 0) {
            position.x = 0;
            velocity.x = 0;
        }
    }

    bool isColliding(const Vector& otherPos, const Vector& otherSize) {
        return (position.x < otherPos.x + otherSize.x &&
                position.x + size.x > otherPos.x &&
                position.y < otherPos.y + otherSize.y &&
                position.y + size.y > otherPos.y);
    }

    bool isAbove(const Vector& otherPos, const Vector& otherSize) {
        return (position.y > otherPos.y + otherSize.y &&
                position.x < otherPos.x + otherSize.x &&
                position.x + size.x > otherPos.x);
    }

    bool isOnSide(const Vector& otherPos, const Vector& otherSize) {
        return (position.y < otherPos.y + otherSize.y &&
                position.y + size.y > otherPos.y &&
                position.x < otherPos.x + otherSize.x &&
                position.x + size.x > otherPos.x);
    }

    bool isInFront(const Vector& otherPos, const Vector& otherSize) {
        return (position.x + size.x > otherPos.x &&
                position.x < otherPos.x + otherSize.x &&
                position.y < otherPos.y + otherSize.y &&
                position.y + size.y > otherPos.y);
    }

    virtual void update(float deltaTime) {
        applyGravity();
        velocity += acceleration * deltaTime;
        position += velocity * deltaTime;
        // Reset acceleration
        acceleration = Vector(0, 0);
    }

    void jump() {
        if (!jumping && !falling) {
            velocity.y = -jumpForce;
            jumping = true;
        }
    }

    void move(float direction) { velocity.x = direction * (running ? 2.0f : 1.0f); }

    void startRunning() { running = true; }

    void stopRunning() { running = false; }

    bool isJumping() const { return jumping; }

    void takeDamage(int damage) {
        health -= damage;
        if (health <= 0) {
            die();
        }
    }

    std::string serialize() const {
        return "Character " + std::to_string(position.x) + " " + std::to_string(position.y) + " " +
               std::to_string(velocity.x) + " " + std::to_string(velocity.y) + " " +
               std::to_string(health) + " " + std::to_string(jumping) + " " +
               std::to_string(running);
    }

    void die() {
        // respawn
        health = maxHealth;
        position = Vector(0, 0);
        jumping = false;
        falling = false;
        running = false;
    }

    Vector getPosition() const { return position; }

    void setPosition(const Vector& pos) { position = pos; }

    Vector getVelocity() const { return velocity; }

    void setVelocity(const Vector& vel) { velocity = vel; }

    void land() { jumping = false; }

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
        jump();
    }
};

class Spaz: public Character {
public:
    void specialAttack() override {
        move(5);
    }
};

class Lori: public Character {
public:
    void specialAttack() override {
        jump();
    }
};

#endif  // CHARACTER_H_
