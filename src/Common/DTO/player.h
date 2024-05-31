#ifndef PLAYER_DTO_H_
#define PLAYER_DTO_H_

#include "../sprite.h"

#include "gameElement.h"

class PlayerDTO: public GameElementDTO {
private:
    uint16_t x;
    uint16_t y;
    uint32_t player_id;
    int health;
    int damage;
    int speed;
    bool playerIsAlive;
    int respawnTime;
    Sprite currentSprite;

public:
    PlayerDTO(uint16_t x, uint16_t y, uint32_t player_id, int health, int damage, int speed,
              const Sprite& currentSprite);
    uint32_t getPlayerId() const;
    int getDamage() const;
    int getHealth() const;
    int getSpeed() const;
    bool isAlive() const;
    void setRespawnTime(int time);
    int getRespawnTime() const;
};

#endif  // PLAYER_DTO_H_
