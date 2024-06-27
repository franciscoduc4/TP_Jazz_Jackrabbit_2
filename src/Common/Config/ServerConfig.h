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
    static int getItemsCollected();

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

    static uint32_t getTurtleEnemyInitialX();
    static uint32_t getTurtleEnemyInitialY();
    static uint8_t getTurtleEnemyInitialHealth();
    static uint8_t getTurtleEnemyDamage();
    static uint8_t getTurtleEnemyMaxMoves();
    static uint8_t getTurtleEnemyMaxRevived();
    static uint8_t getTurtleEnemyDamageTime();
    static uint8_t getTurtleEnemyReviveTime();
    static uint8_t getTurtleEnemyMaxMovesPerCell();
    static uint8_t getTurtleEnemyHitDistance();
    static uint8_t getTurtleEnemyHitDistanceY();
    static uint8_t getTurtleEnemyViewDistance();
    static uint8_t getTurtleEnemyViewDistanceHit();
    static std::vector<uint8_t> getTurtleEnemyWalkProb();
    static uint32_t getTurtleEnemyWidth();
    static uint32_t getTurtleEnemyHeight();
    static uint32_t getTurtleEnemyValue();
    static uint32_t getTurtleEnemyRespawnTime();


    static uint32_t getYellowmonsEnemyInitialX();
    static uint32_t getYellowmonsEnemyInitialY();
    static uint8_t getYellowmonsEnemyInitialHealth();
    static uint8_t getYellowmonsEnemyDamage();
    static uint8_t getYellowmonsEnemyMaxMoves();
    static uint8_t getYellowmonsEnemyMaxRevived();
    static uint8_t getYellowmonsEnemyDamageTime();
    static uint8_t getYellowmonsEnemyReviveTime();
    static uint8_t getYellowmonsEnemyMaxMovesPerCell();
    static uint8_t getYellowmonsEnemyHitDistance();
    static uint8_t getYellowmonsEnemyHitDistanceY();
    static uint8_t getYellowmonsEnemyViewDistance();
    static uint8_t getYellowmonsEnemyViewDistanceHit();
    static std::vector<uint8_t> getYellowmonsEnemyFlyProb();
    static uint32_t getYellowmonsEnemyWidth();
    static uint32_t getYellowmonsEnemyHeight();
    static uint32_t getYellowmonsEnemyValue();
    static uint32_t getYellowmonsEnemyRespawnTime();


    static uint32_t getSchwarzenguardEnemyInitialX();
    static uint32_t getSchwarzenguardEnemyInitialY();
    static uint8_t getSchwarzenguardEnemyInitialHealth();
    static uint8_t getSchwarzenguardEnemyDamage();
    static uint8_t getSchwarzenguardEnemyMaxMoves();
    static uint8_t getSchwarzenguardEnemyMaxRevived();
    static uint8_t getSchwarzenguardEnemyDamageTime();
    static uint8_t getSchwarzenguardEnemyReviveTime();
    static uint8_t getSchwarzenguardEnemyMaxMovesPerCell();
    static uint8_t getSchwarzenguardEnemyHitDistance();
    static uint8_t getSchwarzenguardEnemyHitDistanceY();
    static uint8_t getSchwarzenguardEnemyViewDistance();
    static uint8_t getSchwarzenguardEnemyViewDistanceHit();
    static std::vector<uint8_t> getSchwarzenguardEnemyJumpProb();
    static uint32_t getSchwarzenguardEnemyWidth();
    static uint32_t getSchwarzenguardEnemyHeight();
    static uint32_t getSchwarzenguardEnemyValue();
    static uint32_t getSchwarzenguardEnemyRespawnTime();

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
    static uint32_t getItemBulletValue();
    static uint32_t getItemBulletWidth();
    static uint32_t getItemBulletHeight();

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
