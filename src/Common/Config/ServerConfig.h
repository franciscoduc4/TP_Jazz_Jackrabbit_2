#ifndef __SERVER_CONFIG_H__
#define __SERVER_CONFIG_H__

#include <map>
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
    static float getGameGravity();
    static uint8_t getGameMaxMoves();
    static uint8_t getGameMaxRevived();
    
    static float getGameFrameRate();
    static uint32_t getGameCommandsToProcess();



    static uint32_t getCharacterInitialX();
    static uint32_t getCharacterInitialY();
    static uint8_t getCharacterInitialHealth();
    static uint8_t getCharacterReviveTime();
    static uint8_t getCharacterMaxRevived();
    static uint8_t getCharacterMaxMovesPerCell();
    static uint8_t getCharacterRespawnTime();
    static uint8_t getCharacterDamageTime();
    static uint8_t getCharacterIntoxicatedTime();
    static uint32_t getCharacterQuadMovesPerCell();
    static uint32_t getCharacterTwoMovesPerCell();
    static float getCharacterJumpHeight();


    static uint8_t getJazzShootCooldownTime();
    static float getJazzHorizontalSpeed();
    static float getJazzVerticalSpeed();
    static float getJazzSprintSpeed();
    static float getJazzJumpHeight();

    static uint8_t getLoriShootCooldownTime();
    static float getLoriHorizontalSpeed();
    static float getLoriVerticalSpeed();
    static float getLoriSprintSpeed();
    static float getLoriJumpHeight();

    static uint8_t getSpazShootCooldownTime();
    static float getSpazHorizontalSpeed();
    static float getSpazVerticalSpeed();
    static float getSpazSprintSpeed();
    static float getSpazJumpHeight();

    static uint8_t getWeaponBlasterBullets();
    static uint8_t getWeaponBlasterDamage();
    static float getWeaponBlasterFireRate();
    static uint8_t getWeaponBouncerBullets();
    static uint8_t getWeaponBouncerDamage();
    static float getWeaponBouncerFireRate();
    static uint8_t getWeaponFreezerBullets();
    static uint8_t getWeaponFreezerDamage();
    static float getWeaponFreezerFireRate();
    static uint8_t getWeaponRFMissileBullets();
    static uint8_t getWeaponRFMissileDamage();
    static float getWeaponRFMissileFireRate();

    static uint8_t getObstacleMoves();
    static uint32_t getColumnWidth();
    static uint32_t getColumnHeight();
    static uint32_t getFullFloorWidth();
    static uint32_t getFullFloorHeight();
    static uint32_t getLeftLadderWidth();
    static uint32_t getLeftLadderHeight();
    static uint32_t getLongPlatformWidth();
    static uint32_t getLongPlatformHeight();
    static uint32_t getRightLadderWidth();
    static uint32_t getRightLadderHeight();
    static uint32_t getSmallPlatformWidth();
    static uint32_t getSmallPlatformHeight();

    static void deleteInstance();

    static uint32_t getWalkingEnemyInitialX();
    static uint32_t getWalkingEnemyInitialY();
    static uint8_t getWalkingEnemyInitialHealth();
    static uint8_t getWalkingEnemyDamage();
    static uint8_t getWalkingEnemyMaxMoves();
    static uint8_t getWalkingEnemyMaxRevived();
    static uint8_t getWalkingEnemyDamageTime();
    static uint8_t getWalkingEnemyReviveTime();
    static uint8_t getWalkingEnemyMaxMovesPerCell();
    static uint8_t getWalkingEnemyHitDistance();
    static uint8_t getWalkingEnemyHitDistanceY();
    static uint8_t getWalkingEnemyViewDistance();
    static uint8_t getWalkingEnemyViewDistanceHit();
    static std::vector<uint8_t> getWalkingEnemyWalkProb();
    static uint32_t getWalkingEnemyWidth();
    static uint32_t getWalkingEnemyHeight();
    static uint32_t getWalkingEnemyValue();
    static uint32_t getWalkingEnemyRespawnTime();


    static uint32_t getFlyingEnemyInitialX();
    static uint32_t getFlyingEnemyInitialY();
    static uint8_t getFlyingEnemyInitialHealth();
    static uint8_t getFlyingEnemyDamage();
    static uint8_t getFlyingEnemyMaxMoves();
    static uint8_t getFlyingEnemyMaxRevived();
    static uint8_t getFlyingEnemyDamageTime();
    static uint8_t getFlyingEnemyReviveTime();
    static uint8_t getFlyingEnemyMaxMovesPerCell();
    static uint8_t getFlyingEnemyHitDistance();
    static uint8_t getFlyingEnemyHitDistanceY();
    static uint8_t getFlyingEnemyViewDistance();
    static uint8_t getFlyingEnemyViewDistanceHit();
    static std::vector<uint8_t> getFlyingEnemyFlyProb();
    static uint32_t getFlyingEnemyWidth();
    static uint32_t getFlyingEnemyHeight();
    static uint32_t getFlyingEnemyValue();\
    static uint32_t getFlyingEnemyRespawnTime();


    static uint32_t getJumpingEnemyInitialX();
    static uint32_t getJumpingEnemyInitialY();
    static uint8_t getJumpingEnemyInitialHealth();
    static uint8_t getJumpingEnemyDamage();
    static uint8_t getJumpingEnemyMaxMoves();
    static uint8_t getJumpingEnemyMaxRevived();
    static uint8_t getJumpingEnemyDamageTime();
    static uint8_t getJumpingEnemyReviveTime();
    static uint8_t getJumpingEnemyMaxMovesPerCell();
    static uint8_t getJumpingEnemyHitDistance();
    static uint8_t getJumpingEnemyHitDistanceY();
    static uint8_t getJumpingEnemyViewDistance();
    static uint8_t getJumpingEnemyViewDistanceHit();
    static std::vector<uint8_t> getJumpingEnemyJumpProb();
    static uint32_t getJumpingEnemyWidth();
    static uint32_t getJumpingEnemyHeight();
    static uint32_t getJumpingEnemyValue();
    static uint32_t getJumpingEnemyRespawnTime();

    static uint32_t getItemFoodValue();
    static uint32_t getItemFoodWidth();
    static uint32_t getItemFoodHeight();
    static uint32_t getItemGoldCoinValue();
    static uint32_t getItemGoldCoinWidth();
    static uint32_t getItemGoldCoinHeight();
    static uint32_t getItemSilverCoinValue();
    static uint32_t getItemSilverCoinWidth();
    static uint32_t getItemSilverCoinHeight();
    static uint32_t getItemGemValue();
    static uint32_t getItemGemWidth();
    static uint32_t getItemGemHeight();
    static uint32_t getItemPoisonedFoodValue();
    static uint32_t getItemPoisonedFoodWidth();
    static uint32_t getItemPoisonedFoodHeight();


    static uint32_t getGameMapSizeX(const std::string& mapName);
    static uint32_t getGameMapSizeY(const std::string& mapName);
    static uint8_t getGameMapObstacles(const std::string& mapName);
    static uint8_t getGameMapEnemies(const std::string& mapName);
    static uint8_t getGameMapGems(const std::string& mapName);
    static uint8_t getGameMapSilverCoins(const std::string& mapName);
    static uint8_t getGameMapGoldCoins(const std::string& mapName);
    static uint32_t getGameMapSizeX();
    static uint32_t getGameMapSizeY();
    static uint8_t getGameMapObstacles();
    static uint8_t getGameMapEnemies();
    static uint8_t getGameMapGems();
    static uint8_t getGameMapSilverCoins();
    static uint8_t getGameMapGoldCoins();
    static uint32_t getGameMapShootRange();
    static uint32_t getGameMapHeightRange();
};

#endif  // __SERVER_CONFIG_H__
