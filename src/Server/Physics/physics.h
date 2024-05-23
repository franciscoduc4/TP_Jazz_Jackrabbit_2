#ifndef PHYSICS_H_
#define PHYSICS_H_

#include <algorithm>
#include <memory>

#include "character.h"
#include "gameStatus.h"

class Physics {
public:
    void update(std::shared_ptr<GameStatus> gameStatus, float deltaTime);

private:
    void handleCollisions(std::shared_ptr<Character> character,
                          std::shared_ptr<GameStatus> gameStatus);
    void handleProjectiles(std::shared_ptr<GameStatus> gameStatus, float deltaTime);
};

#endif  // PHYSICS_H_