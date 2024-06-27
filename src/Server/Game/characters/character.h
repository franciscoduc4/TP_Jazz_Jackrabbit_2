#ifndef PLAYER_CHARACTER_H
#define PLAYER_CHARACTER_H

#include <cstdint>
#include <memory>
#include <vector>

#include "../../../Common/Config/ServerConfig.h"
#include "../../../Common/DTO/player.h"
#include "../../../Common/Types/character.h"
#include "../../../Common/Types/direction.h"
#include "../../../Common/Types/entity.h"
#include "../entity.h"
#include "../items/item.h"
#include "../weapons/blaster.h"
#include "../weapons/bouncer.h"
#include "../weapons/freezer.h"
#include "../weapons/rfMissile.h"
#include "../weapons/weapon.h"
#include "states/damage.h"
#include "states/dead.h"
#include "states/idle.h"
#include "states/intoxicated.h"
#include "states/jumping.h"
#include "states/moving.h"
#include "states/shooting.h"
#include "states/specialAttack.h"
#include "states/state.h"

class GameMap;
class Enemy;
class Obstacle;

class Character: public Entity, public std::enable_shared_from_this<Character> {
protected:
    CharacterType type;
    GameMap& gameMap;

    uint8_t maxHealth;
    float reviveTime;
    uint8_t maxRevived;
    uint8_t movesPerCell;
    uint8_t timesRevived;

    float respawnTime;
    float damageTime;
    float intoxicatedTime;
    float shootCooldownTime;

    Vector<float> currentSpeed;
    Vector<float> currentAcceleration;

    float verticalSpeed;
    float sprintSpeed;
    float horizontalSpeed;
    float jumpHeight;

    std::unique_ptr<Weapon> currentWeapon = std::make_unique<Blaster>();
    std::unique_ptr<State> state;

    bool jumping = false;
    bool onGround = false;
    bool sprinting = false;

    bool isIntoxicated = false;

    uint8_t initialYJump = 0;
    uint32_t score = 0;

    uint32_t width;
    uint32_t height;

public:
    /** Constructor del personaje */
    Character(GameMap& gameMap, Vector<uint32_t> pos, uint8_t playerId, CharacterType type,
              float horizontalSpeed, float sprintSpeed, float verticalSpeed, float jumpHeight,
              float shootCooldownTime, uint32_t width, uint32_t height);

    /** Poner al personaje en estado de reposo */
    void idle(float time);
    
    /** Recibir daño con tiempo especificado */
    void recvDamage(uint8_t damage, float time) override;
    
    /** Actualizar el estado del personaje */
    void update(float time);
    
    /** Disparar */
    void shoot(float time);
    
    /** Establecer el estado del personaje */
    void setState(std::unique_ptr<State> newState);

    /** Verificar si un punto está en un triángulo */
    bool isPointInTriangle(const Vector<uint32_t>& p, const Vector<uint32_t>& v1,
                           const Vector<uint32_t>& v2, const Vector<uint32_t>& v3);
    
    /** Actualizar con tiempo en doble precisión */
    void update(double deltaTime);
    
    /** Manejar la colisión con un enemigo */
    void handleEnemyCollision(const std::shared_ptr<Enemy>& enemy);
    
    /** Manejar la colisión con un obstáculo */
    void handleObstacleCollision(const std::shared_ptr<Obstacle>& obstacle);
    
    /** Manejar la colisión con una escalera */
    void handleLadderCollision(const std::shared_ptr<Obstacle>& obstacle);
    
    /** Manejar la colisión con otro personaje */
    void handleCharacterCollision(const std::shared_ptr<Character>& character);

    /** Mover el personaje hacia la derecha con tiempo especificado */
    void moveRight(double time);
    
    /** Correr hacia la derecha */
    void sprintRight(float time);
    
    /** Mover el personaje hacia la izquierda con tiempo especificado */
    void moveLeft(double time);
    
    /** Correr hacia la izquierda */
    void sprintLeft(float time);
    
    /** Mover el personaje hacia abajo con tiempo especificado */
    void moveDown(float time);
    
    /** Saltar con tiempo especificado */
    void jump(float time);
    
    /** Correr */
    void sprint(float time);
    
    /** Manejar colisiones */
    void handleCollisions(const std::shared_ptr<Entity>& entity);


    /** Hacer que el personaje se vuelva intoxicado */
    void becomeIntoxicated(float duration);
    
    /** Manejar la muerte del personaje */
    void die(float respawnTime) override;
    
    /** Revivir al personaje */
    void revive(float time);

    /** Recoger un ítem */
    void collectItem(const std::shared_ptr<Item>& item);
    
    /** Curar al personaje */
    void heal(uint8_t amount);
    
    /** Recoger puntos por eliminar un enemigo */
    void collectPointsForEnemy(uint32_t value);

    /** Obtener los objetivos a disparar */
    std::vector<std::shared_ptr<Entity>> getTargets();
    
    /** Cambiar el arma del personaje */
    void switchWeapon(WeaponType type);

    /** Recibir daño */
    void recvDamage(uint8_t damage);
    
    /** Mover el personaje hacia la derecha */
    void moveRight();
    
    /** Mover el personaje hacia la izquierda */
    void moveLeft();
    
    /** Mover el personaje hacia abajo */
    void moveDown();
    
 
    /** Aplicar gravedad */
    void applyGravity(float time);

    /** Verificar si el personaje está intoxicado */
    bool characIsIntoxicated() const;
    
    /** Obtener el tiempo de intoxicación del personaje */
    float getIntoxicatedTime() const;

    /** Obtener el tipo de personaje */
    CharacterType getCharacterType();

    /** Obtener el tipo de arma del personaje */
    WeaponType getCurrentWeaponType();

    /** Obtener la velocidad horizontal del personaje */
    float getHorizontalSpeed() const { return horizontalSpeed; }

    /** Obtener el DTO del personaje */
    PlayerDTO getDTO() const;

    /** Verificar si el personaje está saltando */
    bool isJumping() { return jumping; }
    
    /** Verificar si el personaje ha aterrizado */
    bool hasLanded();
    
    /** Verificar si el personaje está en el suelo */
    bool isOnGround() const;

    /** Verificar si el personaje está corriendo */
    bool isMoving() const { return currentSpeed.x != 0 || currentSpeed.y != 0;}

    /** Obtener el ancho del personaje */
    uint32_t getWidth() const;
    
    /** Obtener la altura del personaje */
    uint32_t getHeight() const;

    /** Establecer si el personaje está en el suelo */
    void setOnGround(bool onGround);
    
    /** Establecer si el personaje está corriendo */
    void setSprinting(bool sprinting);

    /** Reiniciar la puntuación del personaje */
    void resetScore();

    /** Obtener la puntuación del personaje */
    void specialAttack(float time);
    virtual void specialAttack() = 0;
};

#endif  // PLAYER_CHARACTER_H
