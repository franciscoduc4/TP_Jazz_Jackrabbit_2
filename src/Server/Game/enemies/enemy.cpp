#include "enemy.h"

#include <utility>
#include "../gameMap.h"

/*
 * Constructor de Enemy que inicializa sus atributos.
 */
Enemy::Enemy(GameMap& gameMap, const Vector<uint32_t>& pos, uint8_t id, uint8_t health,
             Direction dir, uint8_t dmg, std::unique_ptr<EnemyState> initialState,
             uint8_t viewDistance, uint8_t viewDistanceHit, uint8_t movesPerCell,
             uint8_t hitDistance, std::vector<uint8_t> walkProb, std::vector<uint8_t> jumpProb,
             std::vector<uint8_t> flyProb, uint32_t width, uint32_t height):
        Entity(pos, id, health, dir, EntityType::ENEMY),
        gameMap(gameMap),
        dmg(dmg),
        state(std::move(initialState)),
        viewDistance(viewDistance),
        viewDistanceHit(viewDistanceHit),
        movesPerCell(movesPerCell),
        hitDistance(hitDistance),
        walkProb(std::move(walkProb)),
        jumpProb(std::move(jumpProb)),
        flyProb(std::move(flyProb)),
        width(width),
        height(height),
        initialPosition(pos),
        movingRight(true) {}

/*
 * Actualiza el estado del enemigo en función del tiempo y los personajes en el juego.
 */
void Enemy::update(const std::map<uint8_t, std::shared_ptr<Character>>& characters, float time) {
    std::vector<std::shared_ptr<Character>> characterList;
    characterList.reserve(characters.size());
    for (const auto& pair: characters) {
        characterList.push_back(pair.second);
    }

    std::unique_ptr<EnemyState> newState = state->update(time);
    if (newState != nullptr) {
        state = std::move(newState);
    }
}

/*
 * Recibe daño y actualiza el estado del enemigo en consecuencia.
 */
void Enemy::recvDamage(uint8_t dmg, float time) {
    std::cout << "[ENEMY] recvDamage" << std::endl;
    Entity::recvDamage(dmg);
    if (isDead()) {
        die(time);
        return;
    } else {
        std::unique_ptr<EnemyState> newState = state->receivingDmg(time);
        if (newState != nullptr) {
            state = std::move(newState);
        }
    }
}

/*
 * Ataca al personaje más cercano si está dentro del rango de ataque.
 */
void Enemy::attack(const std::vector<std::shared_ptr<Character>>& characters, float time) {
    std::shared_ptr<Character> closeCharacter = getClosestCharacter(characters);
    if (!closeCharacter) {
        return;
    }
    if (getDistanceTo(closeCharacter) <= hitDistance) {
        std::unique_ptr<EnemyState> newState = state->attackCharacter(closeCharacter, dmg, time);
        if (newState != nullptr) {
            state = std::move(newState);
        }
    } else {
        return;
    }
}

/*
 * Maneja la muerte del enemigo y cambia su estado.
 */
void Enemy::die(float time) {
    Entity::die(time);
    std::unique_ptr<EnemyState> newState = state->die(time);
    if (newState != nullptr) {
        state = std::move(newState);
    }
}

/*
 * Devuelve el personaje más cercano dentro del rango de visión del enemigo.
 */
std::shared_ptr<Character> Enemy::getClosestCharacter(
        const std::vector<std::shared_ptr<Character>>& characters) {
    std::shared_ptr<Character> closestCharacter = nullptr;
    uint8_t minDistance = viewDistance;
    for (auto& character: characters) {
        uint8_t distance = getDistanceTo(character);
        if (distance < minDistance) {
            minDistance = distance;
            closestCharacter = character;
        }
    }
    return closestCharacter;
}

/*
 * Devuelve el estado actual del enemigo.
 */
std::unique_ptr<EnemyState>& Enemy::getState() { return state; }

/*
 * Devuelve el DTO del enemigo para la transmisión de datos.
 */
EnemyDTO Enemy::getDTO() const {
    return EnemyDTO{pos.x,
                    pos.y,
                    id,
                    health,
                    dmg,
                    static_cast<uint32_t>(0),
                    getEnemyType(),
                    EnemyStateEntity::ENEMY_WALKING};
}

/*
 * Actualiza el estado del enemigo.
 */
void Enemy::update(double deltaTime) {}

/*
 * Deja caer un ítem aleatorio cuando el enemigo muere.
 */
ItemType Enemy::dropRandomItem() const {
    std::array<ItemType, 6> possibleItems = {ItemType::GEM,           ItemType::GOLD_COIN,
                                             ItemType::SILVER_COIN,   ItemType::FOOD,
                                             ItemType::POISONED_FOOD, ItemType::BULLET};
    int randomIndex = std::rand() % possibleItems.size();
    return possibleItems[randomIndex];
}
