#include <cstring>

#include <arpa/inet.h>
#include <gtest/gtest.h>

#include "../../src/Server/Game/characters/character.h"
#include "../../src/Server/Game/entity.h"
#include "../../src/Server/Game/gameMap.h"
#include "../../src/Server/Game/enemies/enemy.h"
#include "../../src/Server/Game/obstacles/obstacle.h"
#include "../../src/Server/Game/items/item.h"

#define MOVEMENTS_PER_CELL 2

class CharacterTest: public ::testing::Test {
protected:
    void SetUp() override {
        // Configura el entorno de prueba
        gameMap = std::make_shared<GameMap>(Vector<uint32_t>{1000, 1000}, 0);
        character = std::make_shared<Character>(*gameMap, Vector<uint32_t>{100, 100}, 1,
                                                CharacterType::JAZZ, 1.0f, 2.0f, 1.0f, 10.0f, 0.5f,
                                                30, 50);
        enemy = std::make_shared<Enemy>(EnemyType::TURTLE, Vector<uint32_t>{100, 150}, 30, 10);
        obstacle = std::make_shared<Obstacle>(ObstacleType::FULL_FLOOR, Vector<uint32_t>{100, 150},
                                              30, 10);
        item = std::make_shared<Item>(ItemType::GEM, Vector<uint32_t>{100, 150}, 30, 10);
    }

    std::shared_ptr<GameMap> gameMap;
    std::shared_ptr<Character> character;
    std::shared_ptr<Enemy> enemy;
    std::shared_ptr<Obstacle> obstacle;
    std::shared_ptr<Item> item;

};


TEST(testCharacterMove, testCharacterSpawnsInCorrectPosition) {
    auto gameMap = std::make_shared<GameMap>(Vector<uint32_t>{1000, 1000}, 0);
    auto character =
            std::make_shared<Character>(*gameMap, Vector<uint32_t>{100, 100}, 1,
                                        CharacterType::JAZZ, 1.0f, 2.0f, 1.0f, 10.0f, 0.5f, 30, 50);
    EXPECT_EQ(character->getPosition().x, 100);
    EXPECT_EQ(character->getPosition().y, 100);
}

TEST(testCharacterMove, testCharacterMoveLeftOneCell) {
    auto gameMap = std::make_shared<GameMap>(Vector<uint32_t>{1000, 1000}, 0);
    auto character =
            std::make_shared<Character>(*gameMap, Vector<uint32_t>{100, 100}, 1,
                                        CharacterType::JAZZ, 1.0f, 2.0f, 1.0f, 10.0f, 0.5f, 30, 50);
    character->moveLeft(0.1);
    EXPECT_LT(character->getPosition().x, 100);
}

TEST(testCharacterMove, testCharacterMoveRightOneCell) {
    auto gameMap = std::make_shared<GameMap>(Vector<uint32_t>{1000, 1000}, 0);
    auto character =
            std::make_shared<Character>(*gameMap, Vector<uint32_t>{100, 100}, 1,
                                        CharacterType::JAZZ, 1.0f, 2.0f, 1.0f, 10.0f, 0.5f, 30, 50);
    character->moveRight(0.1);
    EXPECT_GT(character->getPosition().x, 100);
}

TEST(testCharacterMove, testCharacterAtTheEdgeDoesNotMove) {
    auto gameMap = std::make_shared<GameMap>(Vector<uint32_t>{1000, 1000}, 0);
    auto character =
            std::make_shared<Character>(*gameMap, Vector<uint32_t>{1000, 1000}, 1,
                                        CharacterType::JAZZ, 1.0f, 2.0f, 1.0f, 10.0f, 0.5f, 30, 50);
    character->moveRight(0.1);
    EXPECT_EQ(character->getPosition().x, 1000);
}

TEST(testCharacterMove, testCharacterSpawnsOutOfBounds) {
    auto gameMap = std::make_shared<GameMap>(Vector<uint32_t>{1000, 1000}, 0);
    auto character =
            std::make_shared<Character>(*gameMap, Vector<uint32_t>{2000, 2000}, 1,
                                        CharacterType::JAZZ, 1.0f, 2.0f, 1.0f, 10.0f, 0.5f, 30, 50);
    EXPECT_FALSE(gameMap->isValidPosition(character->getPosition()));
}


TEST(testCharacterMove, testCharacterMovesOutOfBounds) {
    auto gameMap = std::make_shared<GameMap>(Vector<uint32_t>{1000, 1000}, 0);
    auto character =
            std::make_shared<Character>(*gameMap, Vector<uint32_t>{995, 100}, 1,
                                        CharacterType::JAZZ, 1.0f, 2.0f, 1.0f, 10.0f, 0.5f, 30, 50);
    character->moveRight(0.1);
    EXPECT_EQ(character->getPosition().x, 1000);
}


TEST(testCharacterMove, testCharacterReceivesDamage) {
    auto gameMap = std::make_shared<GameMap>(Vector<uint32_t>{1000, 1000}, 0);
    auto character =
            std::make_shared<Character>(*gameMap, Vector<uint32_t>{100, 100}, 1,
                                        CharacterType::JAZZ, 1.0f, 2.0f, 1.0f, 10.0f, 0.5f, 30, 50);
    uint8_t initialHealth = character->getHealth();
    character->recvDamage(10);
    EXPECT_LT(character->getHealth(), initialHealth);
}


TEST(testCharacterMove, testCharacterHeals) {
    auto gameMap = std::make_shared<GameMap>(Vector<uint32_t>{1000, 1000}, 0);
    auto character =
            std::make_shared<Character>(*gameMap, Vector<uint32_t>{100, 100}, 1,
                                        CharacterType::JAZZ, 1.0f, 2.0f, 1.0f, 10.0f, 0.5f, 30, 50);
    character->recvDamage(10);
    uint8_t healthAfterDamage = character->getHealth();
    character->heal(5);
    EXPECT_GT(character->getHealth(), healthAfterDamage);
}


TEST(testCharacterMove, testCharacterIntoxicated) {
    auto gameMap = std::make_shared<GameMap>(Vector<uint32_t>{1000, 1000}, 0);
    auto character =
            std::make_shared<Character>(*gameMap, Vector<uint32_t>{100, 100}, 1,
                                        CharacterType::JAZZ, 1.0f, 2.0f, 1.0f, 10.0f, 0.5f, 30, 50);
    character->becomeIntoxicated(5.0f);
    EXPECT_TRUE(character->characIsIntoxicated());
    EXPECT_FLOAT_EQ(character->getIntoxicatedTime(), 5.0f);
}


TEST(testCharacterMove, testCharacterDiesAndRevives) {
    auto gameMap = std::make_shared<GameMap>(Vector<uint32_t>{1000, 1000}, 0);
    auto character =
            std::make_shared<Character>(*gameMap, Vector<uint32_t>{100, 100}, 1,
                                        CharacterType::JAZZ, 1.0f, 2.0f, 1.0f, 10.0f, 0.5f, 30, 50);
    character->die(5.0f);
    character->revive(0.1f);
    EXPECT_FALSE(character->getIsDead());
    EXPECT_EQ(character->getHealth(), ServerConfig::getCharacterInitialHealth());
}

TEST(testCharacterMove, testCharacterSwitchWeapon) {
    auto gameMap = std::make_shared<GameMap>(Vector<uint32_t>{1000, 1000}, 0);
    auto character =
            std::make_shared<Character>(*gameMap, Vector<uint32_t>{100, 100}, 1,
                                        CharacterType::JAZZ, 1.0f, 2.0f, 1.0f, 10.0f, 0.5f, 30, 50);
    character->switchWeapon(WeaponType::BOUNCER);
    EXPECT_EQ(character->getCurrentWeaponType(), WeaponType::BOUNCER);
}


TEST(testCharacterMove, testCharacterReceivesContinuousDamage) {
    auto gameMap = std::make_shared<GameMap>(Vector<uint32_t>{1000, 1000}, 0);
    auto character =
            std::make_shared<Character>(*gameMap, Vector<uint32_t>{100, 100}, 1,
                                        CharacterType::JAZZ, 1.0f, 2.0f, 1.0f, 10.0f, 0.5f, 30, 50);
    uint8_t initialHealth = character->getHealth();
    character->recvDamage(10);
    character->recvDamage(10);
    EXPECT_LT(character->getHealth(), initialHealth);
}


// Test para verificar que el personaje se mueve correctamente hacia la derecha
TEST_F(CharacterTest, MoveRight) {
    Vector<uint32_t> initialPos = character->getPosition();
    character->moveRight(0.1);
    Vector<uint32_t> newPos = character->getPosition();
    EXPECT_GT(newPos.x, initialPos.x);
}

// Test para verificar que el personaje recibe daño correctamente
TEST_F(CharacterTest, RecvDamage) {
    uint8_t initialHealth = character->getHealth();
    character->recvDamage(10);
    EXPECT_LT(character->getHealth(), initialHealth);
}

// Test para verificar que el personaje se cura correctamente
TEST_F(CharacterTest, Heal) {
    character->recvDamage(10);
    uint8_t healthAfterDamage = character->getHealth();
    character->heal(5);
    EXPECT_GT(character->getHealth(), healthAfterDamage);
}

// Test para verificar que el personaje se intoxica correctamente
TEST_F(CharacterTest, BecomeIntoxicated) {
    character->becomeIntoxicated(5.0f);
    EXPECT_TRUE(character->characIsIntoxicated());
    EXPECT_FLOAT_EQ(character->getIntoxicatedTime(), 5.0f);
}

// Test para verificar que el personaje dispara correctamente
TEST_F(CharacterTest, Shoot) {
    character->shoot(0.1f);
    // Aquí puedes agregar verificaciones específicas si hay algún cambio en el estado del personaje
    // o del mapa de juego Por ejemplo, verificar si se ha registrado un disparo en gameMap
}

// Test para verificar que el personaje revive correctamente
TEST_F(CharacterTest, Revive) {
    character->die(5.0f);
    character->revive(0.1f);
    EXPECT_FALSE(character->getIsDead());
    EXPECT_EQ(character->getHealth(), ServerConfig::getCharacterInitialHealth());
}

// Test para verificar que el personaje maneja colisiones con obstáculos correctamente
TEST_F(CharacterTest, HandleObstacleCollision) {
    auto obstacle = std::make_shared<Obstacle>(ObstacleType::FULL_FLOOR, Vector<uint32_t>{100, 150},
                                               30, 10);
    character->handleObstacleCollision(obstacle);
    EXPECT_TRUE(character->isOnGround());
}

// Test para verificar que el personaje maneja colisiones con enemigos correctamente
TEST_F(CharacterTest, HandleEnemyCollision) {
    auto enemy = std::make_shared<Enemy>(EnemyType::TURTLE, Vector<uint32_t>{100, 150}, 30, 10);
    character->handleCollision(enemy);
    // Aquí puedes agregar verificaciones específicas si hay algún cambio en el estado del personaje
}

// Test para verificar que el personaje maneja colisiones con otros personajes correctamente
TEST_F(CharacterTest, HandleCharacterCollision) {
    auto otherCharacter =
            std::make_shared<Character>(*gameMap, Vector<uint32_t>{120, 100}, 2,
                                        CharacterType::SPAZ, 1.0f, 2.0f, 1.0f, 10.0f, 0.5f, 30, 50);
    character->handleCharacterCollision(otherCharacter);
    // Aquí puedes agregar verificaciones específicas si hay algún cambio en el estado del personaje
}

// Test para verificar que el personaje cambia de arma correctamente
TEST_F(CharacterTest, SwitchWeapon) {
    character->switchWeapon(WeaponType::BOUNCER);
    EXPECT_EQ(character->getCurrentWeaponType(), WeaponType::BOUNCER);
}
