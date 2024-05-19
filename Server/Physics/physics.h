#ifndef PHYSICS_H_
#define PHYSICS_H_

#include "../Game/character.h"
#include "../Game/enemy.h"
#include <vector>

class Physics {
    public: 
        Physics() = default;
        virtual ~Physics() = default;

    private:
        std::vector<Character> characters;
        std::vector<Enemy> enemies;
};


#endif // PHYSICS_H_
