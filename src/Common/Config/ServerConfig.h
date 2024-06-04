#ifndef __SERVER_CONFIG_H__
#define __SERVER_CONFIG_H__

#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>

class ServerConfig {
private:
    static ServerConfig* instance;
    YAML::Node root;
    ServerConfig();

public:
    static ServerConfig* getInstance();
    static std::string getLogFile();
    static int getGameMaxMoves();
    static int getGameMaxRevived();
    static int getCharacterInitialX();
    static int getCharacterInitialY();
    static int getCharacterInitialHealth();
    static int getCharacterMaxMoves();
    static int getCharacterMaxRevived();
    static int getWeaponBlasterBullets();
    static int getWeaponBlasterDamage();
    static float getWeaponBlasterFireRate();
    static int getWeaponBouncerBullets();
    static int getWeaponBouncerDamage();
    static float getWeaponBouncerFireRate();
    static int getWeaponFreezerBullets();
    static int getWeaponFreezerDamage();
    static float getWeaponFreezerFireRate();
    static int getWeaponRFMissileBullets();
    static int getWeaponRFMissileDamage();
    static float getWeaponRFMissileFireRate();
    static int getObstacleMoves();
    static int getGameMapSizeX();
    static int getGameMapSizeY();
    static void deleteInstance();
    static int getDamageTime();
    static int getCharacterReviveTime();
    static int getEnemyMaxMoves();

    static int getWalkingEnemyInitialX();
    static int getWalkingEnemyInitialY();
    static int getWalkingEnemyInitialHealth();
    static int getWalkingEnemyDamage();
    static int getWalkingEnemyMaxMoves();
    static int getWalkingEnemyMaxRevived();
    static int getWalkingEnemyDamageTime();
    static int getWalkingEnemyReviveTime();
    static int getWalkingEnemyMaxMovesPerCell();
    static int getWalkingEnemyHitDistance();
    static int getWalkingEnemyHitDistanceY();
    static int getWalkingEnemyViewDistance();
    static int getWalkingEnemyViewDistanceHit();
    static std::vector<int16_t> getWalkingEnemyWalkProb();
    static std::vector<int16_t> getWalkingEnemyFlyProb();
    static std::vector<int16_t> getWalkingEnemyJumpProb();
};

#endif  // __SERVER_CONFIG_H__
