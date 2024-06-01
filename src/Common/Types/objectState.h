#ifndef OBJECTSTATE_H
#define OBJECTSTATE_H

enum CharacterState : char {
    IDLE,            // El personaje está quieto
    MOVING,          // El personaje se está moviendo
    SPRINTING,       // El personaje se está moviendo rápidamente
    JUMPING,         // El personaje está saltando
    SHOOTING,        // El personaje está disparando
    SPECIAL_ATTACK,  // El personaje está realizando un ataque especial
    INTOXICATED,     // El personaje está intoxicado
    TAKING_DAMAGE,   // El personaje está recibiendo daño
    DEAD,            // El personaje está muerto
    REVIVING         // El personaje se está reanimando
};

enum EnemyState : char {
    ENEMY_IDLE,           // El enemigo está quieto
    ENEMY_MOVING,         // El enemigo se está moviendo
    ENEMY_ATTACKING,      // El enemigo está atacando
    ENEMY_TAKING_DAMAGE,  // El enemigo está recibiendo daño
    ENEMY_DEAD,           // El enemigo está muerto
    ENEMY_RESPAWNING      // El enemigo está reapareciendo
};

#endif  // OBJECTSTATE_H
