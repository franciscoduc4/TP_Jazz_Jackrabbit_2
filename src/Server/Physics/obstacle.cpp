#include "obstacle.h"

Obstacle::Obstacle(int16_t x, int16_t y, int16_t id) :
    moves(2), //sale del CONFIG
    x(x * moves), 
    y(y * moves), 
    id(id) {} 

int16_t Obstacle::getX() {
    return x;
}

int16_t Obstacle::getY() {
    return y;
}

int16_t Obstacle::getMatrixX() {
    return x / moves;
}

int16_t Obstacle::getMatrixY() {
    return y / moves;
}

int16_t Obstacle::getId() {
    return id;
}

void Obstacle::recvDmg(uint16_t dmg, float time) {
    // No hace nada
}

