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

    static int getCharacterInitialHealth();
    static int getCharacterReviveTime();
    static int getCharacterDamage();
    static int getCharacterMaxRevived();
    static int getCharacterMaxMovesPerCell();
    static int getCharacterRespawnTime();
    static int getCharacterDamageTime();
    static int getCharacterIntoxicatedTime();

    static int getJazzShootCooldownTime();
    static int getJazzSpeed();
    static int getJazzSprintSpeed();
    static int getJazzJumpHeight();

    static int getLoriShootCooldownTime();
    static int getLoriSpeed();
    static int getLoriSprintSpeed();
    static int getLoriJumpHeight();

    static int getSpazShootCooldownTime();
    static int getSpazSpeed();
    static int getSpazSprintSpeed();
    static int getSpazJumpHeight();

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

    static int getFlyingEnemyInitialX();
    static int getFlyingEnemyInitialY();
    static int getFlyingEnemyInitialHealth();
    static int getFlyingEnemyDamage();
    static int getFlyingEnemyMaxMoves();
    static int getFlyingEnemyMaxRevived();
    static int getFlyingEnemyDamageTime();
    static int getFlyingEnemyReviveTime();
    static int getFlyingEnemyMaxMovesPerCell();
    static int getFlyingEnemyHitDistance();
    static int getFlyingEnemyHitDistanceY();
    static int getFlyingEnemyViewDistance();
    static int getFlyingEnemyViewDistanceHit();
    static std::vector<int16_t> getFlyingEnemyFlyProb();

    static int getJumpingEnemyInitialX();
    static int getJumpingEnemyInitialY();
    static int getJumpingEnemyInitialHealth();
    static int getJumpingEnemyDamage();
    static int getJumpingEnemyMaxMoves();
    static int getJumpingEnemyMaxRevived();
    static int getJumpingEnemyDamageTime();
    static int getJumpingEnemyReviveTime();
    static int getJumpingEnemyMaxMovesPerCell();
    static int getJumpingEnemyHitDistance();
    static int getJumpingEnemyHitDistanceY();
    static int getJumpingEnemyViewDistance();
    static int getJumpingEnemyViewDistanceHit();
    static std::vector<int16_t> getJumpingEnemyJumpProb();
};

#endif  // __SERVER_CONFIG_H__
