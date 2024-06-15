#ifndef ENTITYSTATE_H
#define ENTITYSTATE_H
enum CharacterStateEntity : char {
    IDLE,            // El personaje está quieto
    MOVING,          // El personaje se está moviendo
    SPRINTING,       // El personaje se está moviendo rápidamente
    JUMPING,         // El personaje está saltando
    SHOOTING,        // El personaje está disparando
    SPECIAL_ATTACK,  // El personaje está realizando un ataque especial
    INTOXICATED,     // El personaje está intoxicado
    TAKING_DAMAGE,   // El personaje está recibiendo daño
    DEAD,            // El personaje está muerto
    RESPAWNING       // El personaje se está reanimando
};

enum EnemyStateEntity : char {
    ENEMY_IDLE,              // El enemigo está quieto
    ENEMY_WALKING,           // El enemigo se está moviendo
    ENEMY_JUMPING,           // El enemigo está saltando
    ENEMY_FLYING,            // El enemigo está volando
    ENEMY_ATTACKING,         // El enemigo está atacando
    ENEMY_RECEIVING_DAMAGE,  // El enemigo está recibiendo daño
    ENEMY_DEAD,              // El enemigo está muerto
    ENEMY_RESPAWNING         // El enemigo está reapareciendo
};

enum EntityType : char { CHARACTER, ENEMY, OBSTACLE, TILE, BULLET, ITEM };

#endif  // ENTITYSTATE_H
