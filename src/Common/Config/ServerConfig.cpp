#include "ServerConfig.h"

const static std::string YAML_FILE_PATH = "config/server.yaml";

ServerConfig* ServerConfig::instance = nullptr;

ServerConfig::ServerConfig() { this->root = YAML::LoadFile(YAML_FILE_PATH); }

ServerConfig* ServerConfig::getInstance() {
    if (instance == nullptr) {
        instance = new ServerConfig();
    }
    return instance;
}

std::string ServerConfig::getLogFile() { return getInstance()->root["LOG_FILE"].as<std::string>(); }

float ServerConfig::getGameGravity() { return getInstance()->root["GAME"]["GRAVITY"].as<float>(); }

float ServerConfig::getGameFrameRate(){
    return getInstance()->root["GAME"]["FRAME_RATE"].as<float>();
}

uint32_t ServerConfig::getGameCommandsToProcess(){
    return static_cast<uint32_t>(getInstance()->root["GAME"]["COMMANDS_TO_PROCESS"].as<int>());
}

uint8_t ServerConfig::getGameMaxMoves() {
    int maxMoves = getInstance()->root["GAME"]["MAX_MOVES"].as<int>();
    return static_cast<uint8_t>(maxMoves);
}

uint8_t ServerConfig::getGameMaxRevived() {
    int maxRevived = getInstance()->root["GAME"]["MAX_REVIVED"].as<int>();
    return static_cast<uint8_t>(maxRevived);
}

uint32_t ServerConfig::getCharacterInitialX() {
    int initialX = getInstance()->root["CHARACTER"]["INITIAL_X"].as<int>();
    return static_cast<uint32_t>(initialX);
}

uint32_t ServerConfig::getCharacterInitialY() {
    int initialY = getInstance()->root["CHARACTER"]["INITIAL_Y"].as<int>();
    return static_cast<uint32_t>(initialY);
}

uint8_t ServerConfig::getCharacterInitialHealth() {
    int initialHealth = getInstance()->root["CHARACTER"]["INITIAL_HEALTH"].as<int>();
    return static_cast<uint8_t>(initialHealth);
}

uint8_t ServerConfig::getCharacterMaxRevived() {
    int maxRevived = getInstance()->root["CHARACTER"]["MAX_REVIVED"].as<int>();
    return static_cast<uint8_t>(maxRevived);
}

uint8_t ServerConfig::getCharacterDamageTime() {
    int damageTime = getInstance()->root["CHARACTER"]["DAMAGE_TIME"].as<int>();
    return static_cast<uint8_t>(damageTime);
}

uint8_t ServerConfig::getCharacterReviveTime() {
    int reviveTime = getInstance()->root["CHARACTER"]["REVIVE_TIME"].as<int>();
    return static_cast<uint8_t>(reviveTime);
}

uint8_t ServerConfig::getCharacterRespawnTime() {
    int respawnTime = getInstance()->root["CHARACTER"]["RESPAWN_TIME"].as<int>();
    return static_cast<uint8_t>(respawnTime);
}

uint8_t ServerConfig::getCharacterIntoxicatedTime() {
    int intoxicatedTime = getInstance()->root["CHARACTER"]["INTOXICATED_TIME"].as<int>();
    return static_cast<uint8_t>(intoxicatedTime);
}

uint8_t ServerConfig::getCharacterMaxMovesPerCell() {
    int maxMovesPerCell = getInstance()->root["CHARACTER"]["MAX_MOVES_PER_CELL"].as<int>();
    return static_cast<uint8_t>(maxMovesPerCell);
}

uint32_t ServerConfig::getCharacterQuadMovesPerCell() {
    int quadMovesPerCell = getInstance()->root["CHARACTER"]["QUAD_MOVES_PER_CELL"].as<int>();
    return static_cast<uint32_t>(quadMovesPerCell);
}

uint32_t ServerConfig::getCharacterTwoMovesPerCell() {
    int twoMovesPerCell = getInstance()->root["CHARACTER"]["TWO_MOVES_PER_CELL"].as<int>();
    return static_cast<uint32_t>(twoMovesPerCell);
}

uint32_t ServerConfig::getCharacterJumpHeight() {
    int jumpHeight = getInstance()->root["CHARACTER"]["JUMP_HEIGHT"].as<int>();
    return static_cast<uint32_t>(jumpHeight);
}


uint8_t ServerConfig::getJazzShootCooldownTime() {
    int jazzShootCooldownTime = getInstance()->root["CHARACTER"]["JAZZ"]["SHOOT_COOLDOWN_TIME"].as<int>();
    return static_cast<uint8_t>(jazzShootCooldownTime);
}

float ServerConfig::getJazzHorizontalSpeed() {
    return getInstance()->root["CHARACTER"]["JAZZ"]["HORIZONTAL_SPEED"].as<float>();
}

float ServerConfig::getJazzVerticalSpeed() {
    return getInstance()->root["CHARACTER"]["JAZZ"]["VERTICAL_SPEED"].as<float>();
}

float ServerConfig::getJazzSprintSpeed() {
    return getInstance()->root["CHARACTER"]["JAZZ"]["SPRINT_SPEED"].as<float>();
}

uint8_t ServerConfig::getJazzJumpHeight() {
    return getInstance()->root["CHARACTER"]["JAZZ"]["JUMP_HEIGHT"].as<int>();
}

uint8_t ServerConfig::getLoriShootCooldownTime() {
    int loriShootCooldownTime = getInstance()->root["CHARACTER"]["LORI"]["SHOOT_COOLDOWN_TIME"].as<int>();
    return static_cast<uint8_t>(loriShootCooldownTime);
}

float ServerConfig::getLoriHorizontalSpeed() {
    return getInstance()->root["CHARACTER"]["LORI"]["HORIZONTAL_SPEED"].as<float>();
}

float ServerConfig::getLoriVerticalSpeed() {
    return getInstance()->root["CHARACTER"]["LORI"]["VERTICAL_SPEED"].as<float>();
}

float ServerConfig::getLoriSprintSpeed() {
    return getInstance()->root["CHARACTER"]["LORI"]["SPRINT_SPEED"].as<float>();
}

uint8_t ServerConfig::getLoriJumpHeight() {
    int loriJumpHeight = getInstance()->root["CHARACTER"]["LORI"]["JUMP_HEIGHT"].as<int>();
    return static_cast<uint8_t>(loriJumpHeight);
}

uint8_t ServerConfig::getSpazShootCooldownTime() {
    int spazShootCooldownTime = getInstance()->root["CHARACTER"]["SPAZ"]["SHOOT_COOLDOWN_TIME"].as<int>();
    return static_cast<uint8_t>(spazShootCooldownTime);
}

float ServerConfig::getSpazHorizontalSpeed() {
    return getInstance()->root["CHARACTER"]["SPAZ"]["HORIZONTAL_SPEED"].as<float>();
}

float ServerConfig::getSpazVerticalSpeed() {
    return getInstance()->root["CHARACTER"]["SPAZ"]["VERTICAL_SPEED"].as<float>();
}

float ServerConfig::getSpazSprintSpeed() {
    return getInstance()->root["CHARACTER"]["SPAZ"]["SPRINT_SPEED"].as<float>();
}

uint8_t ServerConfig::getSpazJumpHeight() {
    int spazJumpHeight = getInstance()->root["CHARACTER"]["SPAZ"]["JUMP_HEIGHT"].as<int>();
    return static_cast<uint8_t>(spazJumpHeight);
}

uint8_t ServerConfig::getWeaponBlasterBullets() {
    int blasterBullets = getInstance()->root["WEAPON"]["BLASTER"]["BULLETS"].as<int>();
    return static_cast<uint8_t>(blasterBullets);
}

uint8_t ServerConfig::getWeaponBlasterDamage() {
    int blasterDamage = getInstance()->root["WEAPON"]["BLASTER"]["DAMAGE"].as<int>();
    return static_cast<uint8_t>(blasterDamage);
}

float ServerConfig::getWeaponBlasterFireRate() {
    return getInstance()->root["WEAPON"]["BLASTER"]["FIRE_RATE"].as<float>();
}

uint8_t ServerConfig::getWeaponBouncerBullets() {
    int bouncerBullets = getInstance()->root["WEAPON"]["BOUNCER"]["BULLETS"].as<int>();
    return static_cast<uint8_t>(bouncerBullets);
}

uint8_t ServerConfig::getWeaponBouncerDamage() {
    int bouncerDamage = getInstance()->root["WEAPON"]["BOUNCER"]["DAMAGE"].as<int>();
    return static_cast<uint8_t>(bouncerDamage);
}

float ServerConfig::getWeaponBouncerFireRate() {
    return getInstance()->root["WEAPON"]["BOUNCER"]["FIRE_RATE"].as<float>();
}

uint8_t ServerConfig::getWeaponFreezerBullets() {
    int freezerBullets = getInstance()->root["WEAPON"]["FREEZER"]["BULLETS"].as<int>();
    return static_cast<uint8_t>(freezerBullets);
}

uint8_t ServerConfig::getWeaponFreezerDamage() {
    int freezerDamage = getInstance()->root["WEAPON"]["FREEZER"]["DAMAGE"].as<int>();
    return static_cast<uint8_t>(freezerDamage);
}

float ServerConfig::getWeaponFreezerFireRate() {
    return getInstance()->root["WEAPON"]["FREEZER"]["FIRE_RATE"].as<float>();
}

uint8_t ServerConfig::getWeaponRFMissileBullets() {
    int rfMissileBullets = getInstance()->root["WEAPON"]["RFMISSILE"]["BULLETS"].as<int>();
    return static_cast<uint8_t>(rfMissileBullets);
}

uint8_t ServerConfig::getWeaponRFMissileDamage() {
    int rfMissileDamage = getInstance()->root["WEAPON"]["RFMISSILE"]["DAMAGE"].as<int>();
    return static_cast<uint8_t>(rfMissileDamage);
}

float ServerConfig::getWeaponRFMissileFireRate() {
    return getInstance()->root["WEAPON"]["RFMISSILE"]["FIRE_RATE"].as<float>();
}

uint8_t ServerConfig::getObstacleMoves() {
    int obstacleMoves = getInstance()->root["OBSTACLE"]["MOVES"].as<int>();
    return static_cast<uint8_t>(obstacleMoves);
}

void ServerConfig::deleteInstance() {
    if (instance != nullptr) {
        delete instance;
        instance = nullptr;
    }
}

uint32_t ServerConfig::getWalkingEnemyInitialX() {
    int walkingEnemyInitialX = getInstance()->root["ENEMY"]["WALKING"]["INITIAL_X"].as<int>();
    return static_cast<uint32_t>(walkingEnemyInitialX);
}

uint32_t ServerConfig::getWalkingEnemyInitialY() {
    int walkingEnemyInitialY = getInstance()->root["ENEMY"]["WALKING"]["INITIAL_Y"].as<int>();
    return static_cast<uint32_t>(walkingEnemyInitialY);
}

uint8_t ServerConfig::getWalkingEnemyMaxMovesPerCell() {
    int walkingEnemyMaxMovesPerCell = getInstance()->root["ENEMY"]["WALKING"]["MAX_MOVES_PER_CELL"].as<int>();
    return static_cast<uint8_t>(walkingEnemyMaxMovesPerCell);
}

uint8_t ServerConfig::getWalkingEnemyInitialHealth() {
    int walkingEnemyInitialHealth = getInstance()->root["ENEMY"]["WALKING"]["INITIAL_HEALTH"].as<int>();
    return static_cast<uint8_t>(walkingEnemyInitialHealth);
}

uint8_t ServerConfig::getWalkingEnemyDamage() {
    int walkingEnemyDamage = getInstance()->root["ENEMY"]["WALKING"]["DAMAGE"].as<int>();
    return static_cast<uint8_t>(walkingEnemyDamage);
}

uint8_t ServerConfig::getWalkingEnemyMaxRevived() {
    int walkingEnemyMaxRevived = getInstance()->root["ENEMY"]["WALKING"]["MAX_REVIVED"].as<int>();
    return static_cast<uint8_t>(walkingEnemyMaxRevived);
}

uint8_t ServerConfig::getWalkingEnemyDamageTime() {
    int walkingEnemyDamageTime = getInstance()->root["ENEMY"]["WALKING"]["DAMAGE_TIME"].as<int>();
    return static_cast<uint8_t>(walkingEnemyDamageTime);
}

uint8_t ServerConfig::getWalkingEnemyReviveTime() {
    int walkingEnemyReviveTime = getInstance()->root["ENEMY"]["WALKING"]["REVIVE_TIME"].as<int>();
    return static_cast<uint8_t>(walkingEnemyReviveTime);
}

uint8_t ServerConfig::getWalkingEnemyHitDistance() {
    int walkingEnemyHitDistance = getInstance()->root["ENEMY"]["WALKING"]["HIT_DISTANCE"].as<int>();
    return static_cast<uint8_t>(walkingEnemyHitDistance);
}

uint8_t ServerConfig::getWalkingEnemyHitDistanceY() {
    int walkingEnemyHitDistanceY = getInstance()->root["ENEMY"]["WALKING"]["HIT_DISTANCE_Y"].as<int>();
    return static_cast<uint8_t>(walkingEnemyHitDistanceY);
}

uint8_t ServerConfig::getWalkingEnemyViewDistance() {
    int walkingEnemyViewDistance = getInstance()->root["ENEMY"]["WALKING"]["VIEW_DISTANCE"].as<int>();
    return static_cast<uint8_t>(walkingEnemyViewDistance);
}

uint8_t ServerConfig::getWalkingEnemyViewDistanceHit() {
    int walkingEnemyViewDistanceHit = getInstance()->root["ENEMY"]["WALKING"]["VIEW_DISTANCE_HIT"].as<int>();
    return static_cast<uint8_t>(walkingEnemyViewDistanceHit);
}

std::vector<uint8_t> ServerConfig::getWalkingEnemyWalkProb() {
    std::vector<uint8_t> walkProb;
    for (const auto& prob: getInstance()->root["ENEMY"]["WALKING"]["WALK_PROB"]) {
        walkProb.push_back(static_cast<uint8_t>(prob.as<int>()));
    }
    return walkProb;
}

uint32_t ServerConfig::getWalkingEnemyWidth() {
    int walkingEnemyWidth = getInstance()->root["ENEMY"]["WALKING"]["WIDTH"].as<int>();
    return static_cast<uint32_t>(walkingEnemyWidth);
}

uint32_t ServerConfig::getWalkingEnemyHeight() {
    int walkingEnemyHeight = getInstance()->root["ENEMY"]["WALKING"]["HEIGHT"].as<int>();
    return static_cast<uint32_t>(walkingEnemyHeight);
}


uint32_t ServerConfig::getFlyingEnemyInitialX() {
    int flyingEnemyInitialX = getInstance()->root["ENEMY"]["FLYING"]["INITIAL_X"].as<int>();
    return static_cast<uint32_t>(flyingEnemyInitialX);
}

uint32_t ServerConfig::getFlyingEnemyInitialY() {
    int flyingEnemyInitialY = getInstance()->root["ENEMY"]["FLYING"]["INITIAL_Y"].as<int>();
    return static_cast<uint32_t>(flyingEnemyInitialY);
}

uint8_t ServerConfig::getFlyingEnemyMaxMovesPerCell() {
    int flyingEnemyMaxMovesPerCell = getInstance()->root["ENEMY"]["FLYING"]["MAX_MOVES_PER_CELL"].as<int>();
    return static_cast<uint8_t>(flyingEnemyMaxMovesPerCell);
}

uint8_t ServerConfig::getFlyingEnemyInitialHealth() {
    int flyingEnemyInitialHealth = getInstance()->root["ENEMY"]["FLYING"]["INITIAL_HEALTH"].as<int>();
    return static_cast<uint8_t>(flyingEnemyInitialHealth);
}

uint8_t ServerConfig::getFlyingEnemyDamage() {
    int flyingEnemyDamage = getInstance()->root["ENEMY"]["FLYING"]["DAMAGE"].as<int>();
    return static_cast<uint8_t>(flyingEnemyDamage);
}

uint8_t ServerConfig::getFlyingEnemyMaxMoves() {
    int flyingEnemyMaxMoves = getInstance()->root["ENEMY"]["FLYING"]["MAX_MOVES"].as<int>();
    return static_cast<uint8_t>(flyingEnemyMaxMoves);
}

uint8_t ServerConfig::getFlyingEnemyMaxRevived() {
    int flyingEnemyMaxRevived = getInstance()->root["ENEMY"]["FLYING"]["MAX_REVIVED"].as<int>();
    return static_cast<uint8_t>(flyingEnemyMaxRevived);
}

uint8_t ServerConfig::getFlyingEnemyDamageTime() {
    int flyingEnemyDamageTime = getInstance()->root["ENEMY"]["FLYING"]["DAMAGE_TIME"].as<int>();
    return static_cast<uint8_t>(flyingEnemyDamageTime);
}

uint8_t ServerConfig::getFlyingEnemyReviveTime() {
    int flyingEnemyReviveTime = getInstance()->root["ENEMY"]["FLYING"]["REVIVE_TIME"].as<int>();
    return static_cast<uint8_t>(flyingEnemyReviveTime);
}

uint8_t ServerConfig::getFlyingEnemyHitDistance() {
    int flyingEnemyHitDistance = getInstance()->root["ENEMY"]["FLYING"]["HIT_DISTANCE"].as<int>();
    return static_cast<uint8_t>(flyingEnemyHitDistance);
}

uint8_t ServerConfig::getFlyingEnemyHitDistanceY() {
    int flyingEnemyHitDistanceY = getInstance()->root["ENEMY"]["FLYING"]["HIT_DISTANCE_Y"].as<int>();
    return static_cast<uint8_t>(flyingEnemyHitDistanceY);
}

uint8_t ServerConfig::getFlyingEnemyViewDistance() {
    int flyingEnemyViewDistance = getInstance()->root["ENEMY"]["FLYING"]["VIEW_DISTANCE"].as<int>();
    return static_cast<uint8_t>(flyingEnemyViewDistance);
}

uint8_t ServerConfig::getFlyingEnemyViewDistanceHit() {
    int flyingEnemyViewDistanceHit = getInstance()->root["ENEMY"]["FLYING"]["VIEW_DISTANCE_HIT"].as<int>();
    return static_cast<uint8_t>(flyingEnemyViewDistanceHit);
}

std::vector<uint8_t> ServerConfig::getFlyingEnemyFlyProb() {
    std::vector<uint8_t> flyProb;
    for (const auto& prob: getInstance()->root["ENEMY"]["FLYING"]["FLY_PROB"]) {
        flyProb.push_back(static_cast<uint8_t>(prob.as<int>()));
    }
    return flyProb;
}

uint32_t ServerConfig::getFlyingEnemyWidth() {
    int flyingEnemyWidth = getInstance()->root["ENEMY"]["FLYING"]["WIDTH"].as<int>();
    return static_cast<uint32_t>(flyingEnemyWidth);
}

uint32_t ServerConfig::getFlyingEnemyHeight() {
    int flyingEnemyHeight = getInstance()->root["ENEMY"]["FLYING"]["HEIGHT"].as<int>();
    return static_cast<uint32_t>(flyingEnemyHeight);
}


uint32_t ServerConfig::getJumpingEnemyInitialX() {
    int jumpingEnemyInitialX = getInstance()->root["ENEMY"]["JUMPING"]["INITIAL_X"].as<int>();
    return static_cast<uint32_t>(jumpingEnemyInitialX);
}

uint32_t ServerConfig::getJumpingEnemyInitialY() {
    int jumpingEnemyInitialY = getInstance()->root["ENEMY"]["JUMPING"]["INITIAL_Y"].as<int>();
    return static_cast<uint32_t>(jumpingEnemyInitialY);
}

uint8_t ServerConfig::getJumpingEnemyMaxMovesPerCell() {
    int jumpingEnemyMaxMovesPerCell = getInstance()->root["ENEMY"]["JUMPING"]["MAX_MOVES_PER_CELL"].as<int>();
    return static_cast<uint8_t>(jumpingEnemyMaxMovesPerCell);
}

uint8_t ServerConfig::getJumpingEnemyInitialHealth() {
    int jumpingEnemyInitialHealth = getInstance()->root["ENEMY"]["JUMPING"]["INITIAL_HEALTH"].as<int>();
    return static_cast<uint8_t>(jumpingEnemyInitialHealth);
}

uint8_t ServerConfig::getJumpingEnemyDamage() {
    int jumpingEnemyDamage = getInstance()->root["ENEMY"]["JUMPING"]["DAMAGE"].as<int>();
    return static_cast<uint8_t>(jumpingEnemyDamage);
}

uint8_t ServerConfig::getJumpingEnemyMaxMoves() {
    int jumpingEnemyMaxMoves = getInstance()->root["ENEMY"]["JUMPING"]["MAX_MOVES"].as<int>();
    return static_cast<uint8_t>(jumpingEnemyMaxMoves);
}

uint8_t ServerConfig::getJumpingEnemyMaxRevived() {
    int jumpingEnemyMaxRevived = getInstance()->root["ENEMY"]["JUMPING"]["MAX_REVIVED"].as<int>();
    return static_cast<uint8_t>(jumpingEnemyMaxRevived);
}

uint8_t ServerConfig::getJumpingEnemyDamageTime() {
    int jumpingEnemyDamageTime = getInstance()->root["ENEMY"]["JUMPING"]["DAMAGE_TIME"].as<int>();
    return static_cast<uint8_t>(jumpingEnemyDamageTime);
}

uint8_t ServerConfig::getJumpingEnemyReviveTime() {
    int jumpingEnemyReviveTime = getInstance()->root["ENEMY"]["JUMPING"]["REVIVE_TIME"].as<int>();
    return static_cast<uint8_t>(jumpingEnemyReviveTime);
}

uint8_t ServerConfig::getJumpingEnemyHitDistance() {
    int jumpingEnemyHitDistance = getInstance()->root["ENEMY"]["JUMPING"]["HIT_DISTANCE"].as<int>();
    return static_cast<uint8_t>(jumpingEnemyHitDistance);
}

uint8_t ServerConfig::getJumpingEnemyHitDistanceY() {
    int jumpingEnemyHitDistanceY = getInstance()->root["ENEMY"]["JUMPING"]["HIT_DISTANCE_Y"].as<int>();
    return static_cast<uint8_t>(jumpingEnemyHitDistanceY);
}

uint8_t ServerConfig::getJumpingEnemyViewDistance() {
    int jumpingEnemyViewDistance = getInstance()->root["ENEMY"]["JUMPING"]["VIEW_DISTANCE"].as<int>();
    return static_cast<uint8_t>(jumpingEnemyViewDistance);
}

uint8_t ServerConfig::getJumpingEnemyViewDistanceHit() {
    int jumpingEnemyViewDistanceHit = getInstance()->root["ENEMY"]["JUMPING"]["VIEW_DISTANCE_HIT"].as<int>();
    return static_cast<uint8_t>(jumpingEnemyViewDistanceHit);
}

uint32_t ServerConfig::getJumpingEnemyWidth() {
    int jumpingEnemyWidth = getInstance()->root["ENEMY"]["JUMPING"]["WIDTH"].as<int>();
    return static_cast<uint32_t>(jumpingEnemyWidth);
}

uint32_t ServerConfig::getJumpingEnemyHeight() {
    int jumpingEnemyHeight = getInstance()->root["ENEMY"]["JUMPING"]["HEIGHT"].as<int>();
    return static_cast<uint32_t>(jumpingEnemyHeight);
}


std::vector<uint8_t> ServerConfig::getJumpingEnemyJumpProb() {
    std::vector<uint8_t> jumpProb;
    for (const auto& prob: getInstance()->root["ENEMY"]["JUMPING"]["JUMP_PROB"]) {
        jumpProb.push_back(static_cast<uint8_t>(prob.as<int>()));
    }
    return jumpProb;
}

uint32_t ServerConfig::getGameMapSizeX(const std::string& mapName) {
    int gameMapSizeX = getInstance()->root["GAMEMAP"][mapName]["SIZE_X"].as<int>();
    return static_cast<uint32_t>(gameMapSizeX);
}

uint32_t ServerConfig::getGameMapSizeY(const std::string& mapName) {
    int gameMapSizeY = getInstance()->root["GAMEMAP"][mapName]["SIZE_Y"].as<int>();
    return static_cast<uint32_t>(gameMapSizeY);
}

uint8_t ServerConfig::getGameMapObstacles(const std::string& mapName) {
    int gameMapObstacles = getInstance()->root["GAMEMAP"][mapName]["OBSTACLES"].as<int>();
    return static_cast<uint8_t>(gameMapObstacles);
}

uint8_t ServerConfig::getGameMapEnemies(const std::string& mapName) {
    int gameMapEnemies = getInstance()->root["GAMEMAP"][mapName]["ENEMIES"].as<int>();
    return static_cast<uint8_t>(gameMapEnemies);
}

uint8_t ServerConfig::getGameMapGems(const std::string& mapName) {
    int gameMapGems = getInstance()->root["GAMEMAP"][mapName]["GEMS"].as<int>();
    return static_cast<uint8_t>(gameMapGems);
}

uint8_t ServerConfig::getGameMapSilverCoins(const std::string& mapName) {
    int gameMapSilverCoins = getInstance()->root["GAMEMAP"][mapName]["SILVER_COINS"].as<int>();
    return static_cast<uint8_t>(gameMapSilverCoins);
}

uint8_t ServerConfig::getGameMapGoldCoins(const std::string& mapName) {
    int gameMapGoldCoins = getInstance()->root["GAMEMAP"][mapName]["GOLD_COINS"].as<int>();
    return static_cast<uint8_t>(gameMapGoldCoins);
}

uint32_t ServerConfig::getGameMapShootRange() {
    int gameMapShootRange = getInstance()->root["GAMEMAP"]["SHOOT_RANGE"].as<int>();
    return static_cast<uint32_t>(gameMapShootRange);
}

uint32_t ServerConfig::getGameMapHeightRange() {
    int gameMapHeightRange = getInstance()->root["GAMEMAP"]["HEIGHT_RANGE"].as<int>();
    return static_cast<uint32_t>(gameMapHeightRange);
}


uint32_t ServerConfig::getItemFoodValue(){
    int itemFoodValue = getInstance()->root["ITEM"]["FOOD"]["VALUE"].as<int>();
    return static_cast<uint32_t>(itemFoodValue);
}

uint32_t ServerConfig::getItemFoodWidth(){
    int itemFoodWidth = getInstance()->root["ITEM"]["FOOD"]["WIDTH"].as<int>();
    return static_cast<uint32_t>(itemFoodWidth);
}

uint32_t ServerConfig::getItemFoodHeight(){
    int itemFoodHeight = getInstance()->root["ITEM"]["FOOD"]["HEIGHT"].as<int>();
    return static_cast<uint32_t>(itemFoodHeight);
}

uint32_t ServerConfig::getItemGoldCoinValue(){
    int itemGoldCoinValue = getInstance()->root["ITEM"]["GOLD_COIN"]["VALUE"].as<int>();
    return static_cast<uint32_t>(itemGoldCoinValue);
}

uint32_t ServerConfig::getItemGoldCoinWidth(){
    int itemGoldCoinWidth = getInstance()->root["ITEM"]["GOLD_COIN"]["WIDTH"].as<int>();
    return static_cast<uint32_t>(itemGoldCoinWidth);
}

uint32_t ServerConfig::getItemGoldCoinHeight(){
    int itemGoldCoinHeight = getInstance()->root["ITEM"]["GOLD_COIN"]["HEIGHT"].as<int>();
    return static_cast<uint32_t>(itemGoldCoinHeight);
}

uint32_t ServerConfig::getItemSilverCoinValue(){
    int itemSilverCoinValue = getInstance()->root["ITEM"]["SILVER_COIN"]["VALUE"].as<int>();
    return static_cast<uint32_t>(itemSilverCoinValue);
}

uint32_t ServerConfig::getItemSilverCoinWidth(){
    int itemSilverCoinWidth = getInstance()->root["ITEM"]["SILVER_COIN"]["WIDTH"].as<int>();
    return static_cast<uint32_t>(itemSilverCoinWidth);
}

uint32_t ServerConfig::getItemSilverCoinHeight(){
    int itemSilverCoinHeight = getInstance()->root["ITEM"]["SILVER_COIN"]["HEIGHT"].as<int>();
    return static_cast<uint32_t>(itemSilverCoinHeight);
}

uint32_t ServerConfig::getItemGemValue(){
    int itemGemValue = getInstance()->root["ITEM"]["GEM"]["VALUE"].as<int>();
    return static_cast<uint32_t>(itemGemValue);
}

uint32_t ServerConfig::getItemGemWidth(){
    int itemGemWidth = getInstance()->root["ITEM"]["GEM"]["WIDTH"].as<int>();
    return static_cast<uint32_t>(itemGemWidth);
}

uint32_t ServerConfig::getItemGemHeight(){
    int itemGemHeight = getInstance()->root["ITEM"]["GEM"]["HEIGHT"].as<int>();
    return static_cast<uint32_t>(itemGemHeight);
}