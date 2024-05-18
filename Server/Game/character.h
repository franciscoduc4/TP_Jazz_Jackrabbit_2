#ifndef CHARACTER_H_H
#define CHARACTER_H_H

#include <string> 

class Character {
    protected:
        int x;
        int y;
        int health;
        std::string name;
        std::string state;

    public:
        Character(int x, int y, int health, const std::string& name, const std::string& state)
        : x(x), y(y), health(health), name(name), state(state) {}

        virtual ~Character() = default;

        virtual void shoot() = 0;
        virtual void run() = 0;
        virtual void sprint() = 0;
        virtual void jump() = 0;
        virtual void specialAttack() = 0;

        int getX() const { return x; }
        int getY() const { return y; }
        int getHealth() const { return health; }
        std::string getName() const { return name; }
        std::string getState() const { return state; }
};

class Jazz : public Character {
    public:
        Jazz(int x, int y, int health, const std::string& name, const std::string& state)
        : Character(x, y, health, name, state) {}

        void shoot() {}
        void run()  {}
        void sprint()  {}
        void jump()  {}
        void specialAttack() {}
};

class Spaz : public Character {
    public:
        Spaz(int x, int y, int health, const std::string& name, const std::string& state)
        : Character(x, y, health, name, state) {}

        void shoot()  {}
        void run()  {}
        void sprint()  {}
        void jump()  {}
        void specialAttack()  {}
};

class Lori : public Character {
    public:
        Lori(int x, int y, int health, const std::string& name, const std::string& state)
        : Character(x, y, health, name, state) {}

        void shoot()  {}
        void run()  {}
        void sprint()  {}
        void jump()  {}
        void specialAttack()  {}
};

#endif // CHARACTER_H_H

