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

// GAME
float ServerConfig::getGameGravity() { return getInstance()->root["GAME"]["GRAVITY"].as<float>(); }

float ServerConfig::getGameFrameRate() {
    return getInstance()->root["GAME"]["FRAME_RATE"].as<float>();
}

uint32_t ServerConfig::getGameCommandsToProcess() {
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

int ServerConfig::getItemsCollected() {
    return getInstance()->root["GAME"]["CANT_ITEMS_COLLECTED"].as<int>();
}


// Character
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

float ServerConfig::getCharacterJumpHeight() {
    return getInstance()->root["CHARACTER"]["JUMP_HEIGHT"].as<float>();
}

uint8_t ServerConfig::getJazzShootCooldownTime() {
    int jazzShootCooldownTime =
            getInstance()->root["CHARACTER"]["JAZZ"]["SHOOT_COOLDOWN_TIME"].as<int>();
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

float ServerConfig::getJazzJumpHeight() {
    return getInstance()->root["CHARACTER"]["JAZZ"]["JUMP_HEIGHT"].as<float>();
}

uint32_t ServerConfig::getJazzSpecialAttackRangeX() {
    int jazzSpecialAttackRangeX = getInstance()->root["CHARACTER"]["JAZZ"]["SPECIAL_ATTACK_RANGE_X"].as<int>();
    return static_cast<uint32_t>(jazzSpecialAttackRangeX);
}

uint32_t ServerConfig::getJazzSpecialAttackRangeY() {
    int jazzSpecialAttackRangeY = getInstance()->root["CHARACTER"]["JAZZ"]["SPECIAL_ATTACK_RANGE_Y"].as<int>();
    return static_cast<uint32_t>(jazzSpecialAttackRangeY);
}


uint32_t ServerConfig::getJazzSpecialAttackDamage() {
    int jazzSpecialAttackDamage = getInstance()->root["CHARACTER"]["JAZZ"]["SPECIAL_ATTACK_DAMAGE"].as<int>();
    return static_cast<uint32_t>(jazzSpecialAttackDamage);
}

uint8_t ServerConfig::getLoriShootCooldownTime() {
    int loriShootCooldownTime =
            getInstance()->root["CHARACTER"]["LORI"]["SHOOT_COOLDOWN_TIME"].as<int>();
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

float ServerConfig::getLoriJumpHeight() {
    return getInstance()->root["CHARACTER"]["LORI"]["JUMP_HEIGHT"].as<float>();
}

uint32_t ServerConfig::getLoriSpecialAttackRangeX() {
    int loriSpecialAttackRangeX = getInstance()->root["CHARACTER"]["LORI"]["SPECIAL_ATTACK_RANGE_X"].as<int>();
    return static_cast<uint32_t>(loriSpecialAttackRangeX);
}

uint32_t ServerConfig::getLoriSpecialAttackRangeY() {
    int loriSpecialAttackRangeY = getInstance()->root["CHARACTER"]["LORI"]["SPECIAL_ATTACK_RANGE_Y"].as<int>();
    return static_cast<uint32_t>(loriSpecialAttackRangeY);
}

uint32_t ServerConfig::getLoriSpecialAttackDamage() {
    int loriSpecialAttackDamage = getInstance()->root["CHARACTER"]["LORI"]["SPECIAL_ATTACK_DAMAGE"].as<int>();
    return static_cast<uint32_t>(loriSpecialAttackDamage);
}

uint8_t ServerConfig::getSpazShootCooldownTime() {
    int spazShootCooldownTime =
            getInstance()->root["CHARACTER"]["SPAZ"]["SHOOT_COOLDOWN_TIME"].as<int>();
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

float ServerConfig::getSpazJumpHeight() {
    return getInstance()->root["CHARACTER"]["SPAZ"]["JUMP_HEIGHT"].as<float>();
}

uint32_t ServerConfig::getSpazSpecialAttackRangeX() {
    int spazSpecialAttackRangeX = getInstance()->root["CHARACTER"]["SPAZ"]["SPECIAL_ATTACK_RANGE_X"].as<int>();
    return static_cast<uint32_t>(spazSpecialAttackRangeX);
}

uint32_t ServerConfig::getSpazSpecialAttackRangeY() {
    int spazSpecialAttackRangeY = getInstance()->root["CHARACTER"]["SPAZ"]["SPECIAL_ATTACK_RANGE_Y"].as<int>();
    return static_cast<uint32_t>(spazSpecialAttackRangeY);
}

uint32_t ServerConfig::getSpazSpecialAttackDamage() {
    int spazSpecialAttackDamage = getInstance()->root["CHARACTER"]["SPAZ"]["SPECIAL_ATTACK_DAMAGE"].as<int>();
    return static_cast<uint32_t>(spazSpecialAttackDamage);
}

float ServerConfig::getSpazSpecialAttackSpeed() {
    return getInstance()->root["CHARACTER"]["SPAZ"]["SPECIAL_ATTACK_SPEED"].as<float>();
}


// Weapons
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

// Obstacle
uint8_t ServerConfig::getObstacleMoves() {
    int obstacleMoves = getInstance()->root["OBSTACLE"]["MOVES"].as<int>();
    return static_cast<uint8_t>(obstacleMoves);
}

float ServerConfig::getObstacleLadderWidth() {
    return getInstance()->root["OBSTACLE"]["LADDER_WIDTH"].as<float>(); 
}

uint32_t ServerConfig::getColumnWidth() {
    int columnWidth = getInstance()->root["OBSTACLE"]["COLUMN"]["WIDTH"].as<int>();
    return static_cast<uint32_t>(columnWidth);
}

uint32_t ServerConfig::getColumnHeight() {
    int columnHeight = getInstance()->root["OBSTACLE"]["COLUMN"]["HEIGHT"].as<int>();
    return static_cast<uint32_t>(columnHeight);
}

uint32_t ServerConfig::getFullFloorWidth() {
    int fullFloorWidth = getInstance()->root["OBSTACLE"]["FULL_FLOOR"]["WIDTH"].as<int>();
    return static_cast<uint32_t>(fullFloorWidth);
}

uint32_t ServerConfig::getFullFloorHeight() {
    int fullFloorHeight = getInstance()->root["OBSTACLE"]["FULL_FLOOR"]["HEIGHT"].as<int>();
    return static_cast<uint32_t>(fullFloorHeight);
}

uint32_t ServerConfig::getLeftLadderWidth() {
    int leftLadderWidth = getInstance()->root["OBSTACLE"]["LEFT_LADDER"]["WIDTH"].as<int>();
    return static_cast<uint32_t>(leftLadderWidth);
}

uint32_t ServerConfig::getLeftLadderHeight() {
    int leftLadderHeight = getInstance()->root["OBSTACLE"]["LEFT_LADDER"]["HEIGHT"].as<int>();
    return static_cast<uint32_t>(leftLadderHeight);
}

uint32_t ServerConfig::getLongPlatformWidth() {
    int longPlatformWidth = getInstance()->root["OBSTACLE"]["LONG_PLATFORM"]["WIDTH"].as<int>();
    return static_cast<uint32_t>(longPlatformWidth);
}

uint32_t ServerConfig::getLongPlatformHeight() {
    int longPlatformHeight = getInstance()->root["OBSTACLE"]["LONG_PLATFORM"]["HEIGHT"].as<int>();
    return static_cast<uint32_t>(longPlatformHeight);
}

uint32_t ServerConfig::getRightLadderWidth() {
    int rightLadderWidth = getInstance()->root["OBSTACLE"]["RIGHT_LADDER"]["WIDTH"].as<int>();
    return static_cast<uint32_t>(rightLadderWidth);
}

uint32_t ServerConfig::getRightLadderHeight() {
    int rightLadderHeight = getInstance()->root["OBSTACLE"]["RIGHT_LADDER"]["HEIGHT"].as<int>();
    return static_cast<uint32_t>(rightLadderHeight);
}

uint32_t ServerConfig::getSmallPlatformWidth() {
    int smallPlatformWidth = getInstance()->root["OBSTACLE"]["SMALL_PLATFORM"]["WIDTH"].as<int>();
    return static_cast<uint32_t>(smallPlatformWidth);
}

uint32_t ServerConfig::getSmallPlatformHeight() {
    int smallPlatformHeight = getInstance()->root["OBSTACLE"]["SMALL_PLATFORM"]["HEIGHT"].as<int>();
    return static_cast<uint32_t>(smallPlatformHeight);
}

void ServerConfig::deleteInstance() {
    if (instance != nullptr) {
        delete instance;
        instance = nullptr;
    }
}

uint32_t ServerConfig::getTurtleEnemyInitialX() {
    int turtleEnemyInitialX = getInstance()->root["ENEMY"]["TURTLE"]["INITIAL_X"].as<int>();
    return static_cast<uint32_t>(turtleEnemyInitialX);
}

uint32_t ServerConfig::getTurtleEnemyInitialY() {
    int turtleEnemyInitialY = getInstance()->root["ENEMY"]["TURTLE"]["INITIAL_Y"].as<int>();
    return static_cast<uint32_t>(turtleEnemyInitialY);
}

uint8_t ServerConfig::getTurtleEnemyMaxMovesPerCell() {
    int turtleEnemyMaxMovesPerCell =
            getInstance()->root["ENEMY"]["TURTLE"]["MAX_MOVES_PER_CELL"].as<int>();
    return static_cast<uint8_t>(turtleEnemyMaxMovesPerCell);
}

uint8_t ServerConfig::getTurtleEnemyInitialHealth() {
    int turtleEnemyInitialHealth =
            getInstance()->root["ENEMY"]["TURTLE"]["INITIAL_HEALTH"].as<int>();
    return static_cast<uint8_t>(turtleEnemyInitialHealth);
}

uint8_t ServerConfig::getTurtleEnemyDamage() {
    int turtleEnemyDamage = getInstance()->root["ENEMY"]["TURTLE"]["DAMAGE"].as<int>();
    return static_cast<uint8_t>(turtleEnemyDamage);
}

uint8_t ServerConfig::getTurtleEnemyMaxRevived() {
    int turtleEnemyMaxRevived = getInstance()->root["ENEMY"]["TURTLE"]["MAX_REVIVED"].as<int>();
    return static_cast<uint8_t>(turtleEnemyMaxRevived);
}

uint8_t ServerConfig::getTurtleEnemyDamageTime() {
    int turtleEnemyDamageTime = getInstance()->root["ENEMY"]["TURTLE"]["DAMAGE_TIME"].as<int>();
    return static_cast<uint8_t>(turtleEnemyDamageTime);
}

uint8_t ServerConfig::getTurtleEnemyReviveTime() {
    int turtleEnemyReviveTime = getInstance()->root["ENEMY"]["TURTLE"]["REVIVE_TIME"].as<int>();
    return static_cast<uint8_t>(turtleEnemyReviveTime);
}

uint8_t ServerConfig::getTurtleEnemyHitDistance() {
    int turtleEnemyHitDistance = getInstance()->root["ENEMY"]["TURTLE"]["HIT_DISTANCE"].as<int>();
    return static_cast<uint8_t>(turtleEnemyHitDistance);
}

uint8_t ServerConfig::getTurtleEnemyHitDistanceY() {
    int turtleEnemyHitDistanceY =
            getInstance()->root["ENEMY"]["TURTLE"]["HIT_DISTANCE_Y"].as<int>();
    return static_cast<uint8_t>(turtleEnemyHitDistanceY);
}

uint8_t ServerConfig::getTurtleEnemyViewDistance() {
    int turtleEnemyViewDistance = getInstance()->root["ENEMY"]["TURTLE"]["VIEW_DISTANCE"].as<int>();
    return static_cast<uint8_t>(turtleEnemyViewDistance);
}

uint8_t ServerConfig::getTurtleEnemyViewDistanceHit() {
    int turtleEnemyViewDistanceHit =
            getInstance()->root["ENEMY"]["TURTLE"]["VIEW_DISTANCE_HIT"].as<int>();
    return static_cast<uint8_t>(turtleEnemyViewDistanceHit);
}

std::vector<uint8_t> ServerConfig::getTurtleEnemyWalkProb() {
    std::vector<uint8_t> walkProb;
    for (const auto& prob: getInstance()->root["ENEMY"]["TURTLE"]["WALK_PROB"]) {
        walkProb.push_back(static_cast<uint8_t>(prob.as<int>()));
    }
    return walkProb;
}

uint32_t ServerConfig::getTurtleEnemyWidth() {
    int turtleEnemyWidth = getInstance()->root["ENEMY"]["TURTLE"]["WIDTH"].as<int>();
    return static_cast<uint32_t>(turtleEnemyWidth);
}

uint32_t ServerConfig::getTurtleEnemyHeight() {
    int turtleEnemyHeight = getInstance()->root["ENEMY"]["TURTLE"]["HEIGHT"].as<int>();
    return static_cast<uint32_t>(turtleEnemyHeight);
}

uint32_t ServerConfig::getTurtleEnemyValue() {
    int turtleEnemyValue = getInstance()->root["ENEMY"]["TURTLE"]["VALUE"].as<int>();
    return static_cast<uint32_t>(turtleEnemyValue);
}

float ServerConfig::getTurtleEnemyRespawnTime() {
    return getInstance()->root["ENEMY"]["TURTLE"]["RESPAWN_TIME"].as<float>();
}


uint32_t ServerConfig::getYellowmonsEnemyInitialX() {
    int yellowmonsEnemyInitialX = getInstance()->root["ENEMY"]["YELLOWMONS"]["INITIAL_X"].as<int>();
    return static_cast<uint32_t>(yellowmonsEnemyInitialX);
}

uint32_t ServerConfig::getYellowmonsEnemyInitialY() {
    int yellowmonsEnemyInitialY = getInstance()->root["ENEMY"]["YELLOWMONS"]["INITIAL_Y"].as<int>();
    return static_cast<uint32_t>(yellowmonsEnemyInitialY);
}

uint8_t ServerConfig::getYellowmonsEnemyMaxMovesPerCell() {
    int yellowmonsEnemyMaxMovesPerCell =
            getInstance()->root["ENEMY"]["YELLOWMONS"]["MAX_MOVES_PER_CELL"].as<int>();
    return static_cast<uint8_t>(yellowmonsEnemyMaxMovesPerCell);
}

uint8_t ServerConfig::getYellowmonsEnemyInitialHealth() {
    int yellowmonsEnemyInitialHealth =
            getInstance()->root["ENEMY"]["YELLOWMONS"]["INITIAL_HEALTH"].as<int>();
    return static_cast<uint8_t>(yellowmonsEnemyInitialHealth);
}

uint8_t ServerConfig::getYellowmonsEnemyDamage() {
    int yellowmonsEnemyDamage = getInstance()->root["ENEMY"]["YELLOWMONS"]["DAMAGE"].as<int>();
    return static_cast<uint8_t>(yellowmonsEnemyDamage);
}

uint8_t ServerConfig::getYellowmonsEnemyMaxMoves() {
    int yellowmonsEnemyMaxMoves = getInstance()->root["ENEMY"]["YELLOWMONS"]["MAX_MOVES"].as<int>();
    return static_cast<uint8_t>(yellowmonsEnemyMaxMoves);
}

uint8_t ServerConfig::getYellowmonsEnemyMaxRevived() {
    int yellowmonsEnemyMaxRevived =
            getInstance()->root["ENEMY"]["YELLOWMONS"]["MAX_REVIVED"].as<int>();
    return static_cast<uint8_t>(yellowmonsEnemyMaxRevived);
}

uint8_t ServerConfig::getYellowmonsEnemyDamageTime() {
    int yellowmonsEnemyDamageTime =
            getInstance()->root["ENEMY"]["YELLOWMONS"]["DAMAGE_TIME"].as<int>();
    return static_cast<uint8_t>(yellowmonsEnemyDamageTime);
}

uint8_t ServerConfig::getYellowmonsEnemyReviveTime() {
    int yellowmonsEnemyReviveTime =
            getInstance()->root["ENEMY"]["YELLOWMONS"]["REVIVE_TIME"].as<int>();
    return static_cast<uint8_t>(yellowmonsEnemyReviveTime);
}

uint8_t ServerConfig::getYellowmonsEnemyHitDistance() {
    int yellowmonsEnemyHitDistance =
            getInstance()->root["ENEMY"]["YELLOWMONS"]["HIT_DISTANCE"].as<int>();
    return static_cast<uint8_t>(yellowmonsEnemyHitDistance);
}

uint8_t ServerConfig::getYellowmonsEnemyHitDistanceY() {
    int yellowmonsEnemyHitDistanceY =
            getInstance()->root["ENEMY"]["YELLOWMONS"]["HIT_DISTANCE_Y"].as<int>();
    return static_cast<uint8_t>(yellowmonsEnemyHitDistanceY);
}

uint8_t ServerConfig::getYellowmonsEnemyViewDistance() {
    int yellowmonsEnemyViewDistance =
            getInstance()->root["ENEMY"]["YELLOWMONS"]["VIEW_DISTANCE"].as<int>();
    return static_cast<uint8_t>(yellowmonsEnemyViewDistance);
}

uint8_t ServerConfig::getYellowmonsEnemyViewDistanceHit() {
    int yellowmonsEnemyViewDistanceHit =
            getInstance()->root["ENEMY"]["YELLOWMONS"]["VIEW_DISTANCE_HIT"].as<int>();
    return static_cast<uint8_t>(yellowmonsEnemyViewDistanceHit);
}

std::vector<uint8_t> ServerConfig::getYellowmonsEnemyFlyProb() {
    std::vector<uint8_t> flyProb;
    for (const auto& prob: getInstance()->root["ENEMY"]["YELLOWMONS"]["FLY_PROB"]) {
        flyProb.push_back(static_cast<uint8_t>(prob.as<int>()));
    }
    return flyProb;
}

uint32_t ServerConfig::getYellowmonsEnemyWidth() {
    int yellowmonsEnemyWidth = getInstance()->root["ENEMY"]["YELLOWMONS"]["WIDTH"].as<int>();
    return static_cast<uint32_t>(yellowmonsEnemyWidth);
}

uint32_t ServerConfig::getYellowmonsEnemyHeight() {
    int yellowmonsEnemyHeight = getInstance()->root["ENEMY"]["YELLOWMONS"]["HEIGHT"].as<int>();
    return static_cast<uint32_t>(yellowmonsEnemyHeight);
}

uint32_t ServerConfig::getYellowmonsEnemyValue() {
    int yellowmonsEnemyValue = getInstance()->root["ENEMY"]["YELLOWMONS"]["VALUE"].as<int>();
    return static_cast<uint32_t>(yellowmonsEnemyValue);
}

float ServerConfig::getYellowmonsEnemyRespawnTime() {
    return getInstance()->root["ENEMY"]["YELLOWMONS"]["RESPAWN_TIME"].as<float>();
    
}


uint32_t ServerConfig::getSchwarzenguardEnemyInitialX() {
    int schwarzenguardEnemyInitialX =
            getInstance()->root["ENEMY"]["SCHWARZENGUARD"]["INITIAL_X"].as<int>();
    return static_cast<uint32_t>(schwarzenguardEnemyInitialX);
}

uint32_t ServerConfig::getSchwarzenguardEnemyInitialY() {
    int schwarzenguardEnemyInitialY = getInstance()->root["ENEMY"]["SCHWARZENGUARD"]["INITIAL_Y"].as<int>();
    return static_cast<uint32_t>(schwarzenguardEnemyInitialY);
}

uint8_t ServerConfig::getSchwarzenguardEnemyMaxMovesPerCell() {
    int schwarzenguardEnemyMaxMovesPerCell = getInstance()->root["ENEMY"]["SCHWARZENGUARD"]["MAX_MOVES_PER_CELL"].as<int>();
    return static_cast<uint8_t>(schwarzenguardEnemyMaxMovesPerCell);
}

uint8_t ServerConfig::getSchwarzenguardEnemyInitialHealth() {
    int schwarzenguardEnemyInitialHealth = getInstance()->root["ENEMY"]["SCHWARZENGUARD"]["INITIAL_HEALTH"].as<int>();
    return static_cast<uint8_t>(schwarzenguardEnemyInitialHealth);
}

uint8_t ServerConfig::getSchwarzenguardEnemyDamage() {
    int schwarzenguardEnemyDamage = getInstance()->root["ENEMY"]["SCHWARZENGUARD"]["DAMAGE"].as<int>();
    return static_cast<uint8_t>(schwarzenguardEnemyDamage);
}

uint8_t ServerConfig::getSchwarzenguardEnemyMaxMoves() {
    int schwarzenguardEnemyMaxMoves = getInstance()->root["ENEMY"]["SCHWARZENGUARD"]["MAX_MOVES"].as<int>();
    return static_cast<uint8_t>(schwarzenguardEnemyMaxMoves);
}

uint8_t ServerConfig::getSchwarzenguardEnemyMaxRevived() {
    int schwarzenguardEnemyMaxRevived = getInstance()->root["ENEMY"]["SCHWARZENGUARD"]["MAX_REVIVED"].as<int>();
    return static_cast<uint8_t>(schwarzenguardEnemyMaxRevived);
}

uint8_t ServerConfig::getSchwarzenguardEnemyDamageTime() {
    int schwarzenguardEnemyDamageTime = getInstance()->root["ENEMY"]["SCHWARZENGUARD"]["DAMAGE_TIME"].as<int>();
    return static_cast<uint8_t>(schwarzenguardEnemyDamageTime);
}

uint8_t ServerConfig::getSchwarzenguardEnemyReviveTime() {
    int schwarzenguardEnemyReviveTime = getInstance()->root["ENEMY"]["SCHWARZENGUARD"]["REVIVE_TIME"].as<int>();
    return static_cast<uint8_t>(schwarzenguardEnemyReviveTime);
}

uint8_t ServerConfig::getSchwarzenguardEnemyHitDistance() {
    int schwarzenguardEnemyHitDistance = getInstance()->root["ENEMY"]["SCHWARZENGUARD"]["HIT_DISTANCE"].as<int>();
    return static_cast<uint8_t>(schwarzenguardEnemyHitDistance);
}

uint8_t ServerConfig::getSchwarzenguardEnemyHitDistanceY() {
    int schwarzenguardEnemyHitDistanceY = getInstance()->root["ENEMY"]["SCHWARZENGUARD"]["HIT_DISTANCE_Y"].as<int>();
    return static_cast<uint8_t>(schwarzenguardEnemyHitDistanceY);
}

uint8_t ServerConfig::getSchwarzenguardEnemyViewDistance() {
    int schwarzenguardEnemyViewDistance = getInstance()->root["ENEMY"]["SCHWARZENGUARD"]["VIEW_DISTANCE"].as<int>();
    return static_cast<uint8_t>(schwarzenguardEnemyViewDistance);
}

uint8_t ServerConfig::getSchwarzenguardEnemyViewDistanceHit() {
    int schwarzenguardEnemyViewDistanceHit = getInstance()->root["ENEMY"]["SCHWARZENGUARD"]["VIEW_DISTANCE_HIT"].as<int>();
    return static_cast<uint8_t>(schwarzenguardEnemyViewDistanceHit);
}

uint32_t ServerConfig::getSchwarzenguardEnemyWidth() {
    int schwarzenguardEnemyWidth = getInstance()->root["ENEMY"]["SCHWARZENGUARD"]["WIDTH"].as<int>();
    return static_cast<uint32_t>(schwarzenguardEnemyWidth);
}

uint32_t ServerConfig::getSchwarzenguardEnemyHeight() {
    int schwarzenguardEnemyHeight = getInstance()->root["ENEMY"]["SCHWARZENGUARD"]["HEIGHT"].as<int>();
    return static_cast<uint32_t>(schwarzenguardEnemyHeight);
}

uint32_t ServerConfig::getSchwarzenguardEnemyValue() {
    int schwarzenguardEnemyValue = getInstance()->root["ENEMY"]["SCHWARZENGUARD"]["VALUE"].as<int>();
    return static_cast<uint32_t>(schwarzenguardEnemyValue);
}

float ServerConfig::getSchwarzenguardEnemyRespawnTime() {
    return getInstance()->root["ENEMY"]["SCHWARZENGUARD"]["RESPAWN_TIME"].as<float>();
}

std::vector<uint8_t> ServerConfig::getSchwarzenguardEnemyJumpProb() {
    std::vector<uint8_t> jumpProb;
    for (const auto& prob: getInstance()->root["ENEMY"]["SCHWARZENGUARD"]["JUMP_PROB"]) {
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

uint32_t ServerConfig::getGameMapSizeX() { return getGameMapSizeX("DEFAULT"); }

uint32_t ServerConfig::getGameMapSizeY() { return getGameMapSizeY("DEFAULT"); }

uint8_t ServerConfig::getGameMapObstacles() { return getGameMapObstacles("DEFAULT"); }

uint8_t ServerConfig::getGameMapEnemies() { return getGameMapEnemies("DEFAULT"); }

uint8_t ServerConfig::getGameMapGems() { return getGameMapGems("DEFAULT"); }

uint8_t ServerConfig::getGameMapSilverCoins() { return getGameMapSilverCoins("DEFAULT"); }

uint8_t ServerConfig::getGameMapGoldCoins() { return getGameMapGoldCoins("DEFAULT"); }

uint32_t ServerConfig::getGameMapShootRange() {
    int gameMapShootRange = getInstance()->root["GAMEMAP"]["SHOOT_RANGE"].as<int>();
    return static_cast<uint32_t>(gameMapShootRange);
}

uint32_t ServerConfig::getGameMapHeightRange() {
    int gameMapHeightRange = getInstance()->root["GAMEMAP"]["HEIGHT_RANGE"].as<int>();
    return static_cast<uint32_t>(gameMapHeightRange);
}


uint32_t ServerConfig::getItemFoodValue() {
    int itemFoodValue = getInstance()->root["ITEM"]["FOOD"]["VALUE"].as<int>();
    return static_cast<uint32_t>(itemFoodValue);
}

uint32_t ServerConfig::getItemFoodWidth() {
    int itemFoodWidth = getInstance()->root["ITEM"]["FOOD"]["WIDTH"].as<int>();
    return static_cast<uint32_t>(itemFoodWidth);
}

uint32_t ServerConfig::getItemFoodHeight() {
    int itemFoodHeight = getInstance()->root["ITEM"]["FOOD"]["HEIGHT"].as<int>();
    return static_cast<uint32_t>(itemFoodHeight);
}

uint32_t ServerConfig::getItemGoldCoinValue() {
    int itemGoldCoinValue = getInstance()->root["ITEM"]["GOLD_COIN"]["VALUE"].as<int>();
    return static_cast<uint32_t>(itemGoldCoinValue);
}

uint32_t ServerConfig::getItemGoldCoinWidth() {
    int itemGoldCoinWidth = getInstance()->root["ITEM"]["GOLD_COIN"]["WIDTH"].as<int>();
    return static_cast<uint32_t>(itemGoldCoinWidth);
}

uint32_t ServerConfig::getItemGoldCoinHeight() {
    int itemGoldCoinHeight = getInstance()->root["ITEM"]["GOLD_COIN"]["HEIGHT"].as<int>();
    return static_cast<uint32_t>(itemGoldCoinHeight);
}

uint32_t ServerConfig::getItemSilverCoinValue() {
    int itemSilverCoinValue = getInstance()->root["ITEM"]["SILVER_COIN"]["VALUE"].as<int>();
    return static_cast<uint32_t>(itemSilverCoinValue);
}

uint32_t ServerConfig::getItemSilverCoinWidth() {
    int itemSilverCoinWidth = getInstance()->root["ITEM"]["SILVER_COIN"]["WIDTH"].as<int>();
    return static_cast<uint32_t>(itemSilverCoinWidth);
}

uint32_t ServerConfig::getItemSilverCoinHeight() {
    int itemSilverCoinHeight = getInstance()->root["ITEM"]["SILVER_COIN"]["HEIGHT"].as<int>();
    return static_cast<uint32_t>(itemSilverCoinHeight);
}

uint32_t ServerConfig::getItemGemValue() {
    int itemGemValue = getInstance()->root["ITEM"]["GEM"]["VALUE"].as<int>();
    return static_cast<uint32_t>(itemGemValue);
}

uint32_t ServerConfig::getItemGemWidth() {
    int itemGemWidth = getInstance()->root["ITEM"]["GEM"]["WIDTH"].as<int>();
    return static_cast<uint32_t>(itemGemWidth);
}

uint32_t ServerConfig::getItemGemHeight() {
    int itemGemHeight = getInstance()->root["ITEM"]["GEM"]["HEIGHT"].as<int>();
    return static_cast<uint32_t>(itemGemHeight);
}

uint32_t ServerConfig::getItemPoisonedFoodValue() {
    int itemPoisonedFoodValue = getInstance()->root["ITEM"]["POISONED_FOOD"]["VALUE"].as<int>();
    return static_cast<uint32_t>(itemPoisonedFoodValue);
}

uint32_t ServerConfig::getItemPoisonedFoodWidth() {
    int itemPoisonedFoodWidth = getInstance()->root["ITEM"]["POISONED_FOOD"]["WIDTH"].as<int>();
    return static_cast<uint32_t>(itemPoisonedFoodWidth);
}

uint32_t ServerConfig::getItemPoisonedFoodHeight() {
    int itemPoisonedFoodHeight = getInstance()->root["ITEM"]["POISONED_FOOD"]["HEIGHT"].as<int>();
    return static_cast<uint32_t>(itemPoisonedFoodHeight);
}

uint32_t ServerConfig::getItemBulletValue() {
    int itemBulletValue = getInstance()->root["ITEM"]["BULLET"]["VALUE"].as<int>();
    return static_cast<uint32_t>(itemBulletValue);
}

uint32_t ServerConfig::getItemBulletWidth() {
    int itemBulletWidth = getInstance()->root["ITEM"]["BULLET"]["WIDTH"].as<int>();
    return static_cast<uint32_t>(itemBulletWidth);
}

uint32_t ServerConfig::getItemBulletHeight() {
    int itemBulletHeight = getInstance()->root["ITEM"]["BULLET"]["HEIGHT"].as<int>();
    return static_cast<uint32_t>(itemBulletHeight);
}