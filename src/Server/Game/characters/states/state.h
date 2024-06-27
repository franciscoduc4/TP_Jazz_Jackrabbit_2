#ifndef STATE_H
#define STATE_H
#include <cstdint>
#include <memory>
#include <utility>

#include "../../../../Common/Types/entity.h"

class Weapon;
class Character;

class State {
protected:
    CharacterStateEntity characterState;

public:
    virtual ~State() = default;

    /** Ejecutar la acción correspondiente al estado actual */
    virtual std::unique_ptr<State> exec(float time) = 0;

    /** Disparar el arma del personaje */
    virtual std::unique_ptr<State> shoot(const std::shared_ptr<Weapon>& weapon, float time) = 0;

    /** Mover el personaje en la dirección especificada */
    virtual std::unique_ptr<State> move(Direction direction, float time) = 0;

    /** Correr en la dirección especificada */
    virtual std::unique_ptr<State> sprint(Direction direction, float time) = 0;

    /** Recibir daño y actualizar el estado */
    virtual std::unique_ptr<State> receiveDamage(uint8_t dmg, float time) = 0;

    /** Manejar la muerte del personaje y actualizar el estado */
    virtual std::unique_ptr<State> die(float time) = 0;

    /** Revivir al personaje y actualizar el estado */
    virtual std::unique_ptr<State> revive(float time) = 0;

    /** Saltar y actualizar el estado */
    virtual std::unique_ptr<State> jump(float time) = 0;

    /** Realizar un ataque especial y actualizar el estado */
    virtual std::unique_ptr<State> specialAttack(float time) = 0;

    /** Volverse intoxicado y actualizar el estado */
    virtual std::unique_ptr<State> becomeIntoxicated(float duration) = 0;

    /** Detener la acción actual y actualizar el estado */
    virtual std::unique_ptr<State> stopAction() = 0;

    /** Obtener el estado actual del personaje */
    virtual CharacterStateEntity getCharacterState() { return characterState; }
};

#endif  // STATE_H
