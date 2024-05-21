#ifndef CHARACTER_H_H
#define CHARACTER_H_H

#include <memory>
#include <string>

// Declaración adelantada de las clases específicas
class Jazz;
class Spaz;
class Lori;

class Character {
protected:
    int x;
    int y;
    int health;
    std::string name;
    std::string state;
    int id;

public:
    Character(int x, int y, int health, const std::string& name, const std::string& state, int id):
            x(x), y(y), health(health), name(name), state(state), id(id) {}

    virtual ~Character() = default;

    virtual void shoot() = 0;
    virtual void run() = 0;
    virtual void sprint() = 0;
    virtual void jump() = 0;
    virtual void specialAttack() = 0;
    void handleAction(const std::string& action) {}

    static std::unique_ptr<Character> createCharacter(const std::string& name);

    int getX() const { return x; }
    int getY() const { return y; }
    int getHealth() const { return health; }
    int getId() const { return id; }
    std::string getName() const { return name; }
    std::string getState() const { return state; }
};

class Jazz: public Character {
public:
    Jazz(int x, int y, int health, const std::string& name, const std::string& state, int id):
            Character(x, y, health, name, state, id) {}

    void shoot() override {}
    void run() override {}
    void sprint() override {}
    void jump() override {}
    void specialAttack() override {}
};

class Spaz: public Character {
public:
    Spaz(int x, int y, int health, const std::string& name, const std::string& state, int id):
            Character(x, y, health, name, state, id) {}

    void shoot() override {}
    void run() override {}
    void sprint() override {}
    void jump() override {}
    void specialAttack() override {}
};

class Lori: public Character {
public:
    Lori(int x, int y, int health, const std::string& name, const std::string& state, int id):
            Character(x, y, health, name, state, id) {}

    void shoot() override {}
    void run() override {}
    void sprint() override {}
    void jump() override {}
    void specialAttack() override {}
};

#endif  // CHARACTER_H_H
