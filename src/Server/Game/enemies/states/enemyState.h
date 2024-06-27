#ifndef ENEMY_STATE_H
#define ENEMY_STATE_H

#include <iostream>
#include <memory>

#include "../../../../Common/Types/entity.h"
#include "../../characters/character.h"

class Character;

/*
 * Clase abstracta EnemyState que define la interfaz para los estados de un enemigo.
 */
class EnemyState {
public:
    EnemyStateEntity enemyState = ENEMY_IDLE;

    /*
     * Actualiza el estado del enemigo.
     * @param time Tiempo transcurrido.
     * @return Nuevo estado del enemigo.
     */
    virtual std::unique_ptr<EnemyState> update(float time) = 0;

    /*
     * Maneja el ataque a un personaje.
     * @param character Personaje a atacar.
     * @param dmg Daño infligido.
     * @param time Tiempo transcurrido.
     * @return Nuevo estado del enemigo.
     */
    virtual std::unique_ptr<EnemyState> attackCharacter(std::shared_ptr<Character> character,
                                                        int16_t dmg, float time) = 0;

    /*
     * Maneja el daño recibido por el enemigo.
     * @param time Tiempo transcurrido.
     * @return Nuevo estado del enemigo.
     */
    virtual std::unique_ptr<EnemyState> receivingDmg(float time) = 0;

    /*
     * Maneja la muerte del enemigo.
     * @param time Tiempo transcurrido.
     * @return Nuevo estado del enemigo.
     */
    virtual std::unique_ptr<EnemyState> die(float time) = 0;

    /*
     * Establece la velocidad del enemigo.
     * @param vel Velocidad del enemigo.
     */
    virtual void setVelocity(float vel) = 0;

    /*
     * Devuelve el estado actual del enemigo.
     * @return Estado actual del enemigo.
     */
    EnemyStateEntity getState(){ return enemyState; }

    virtual ~EnemyState() = default;
};

#endif  // ENEMY_STATE_H
