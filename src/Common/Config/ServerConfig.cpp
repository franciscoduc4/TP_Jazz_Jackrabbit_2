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

uint8_t ServerConfig::getGameMaxMoves() {
    return getInstance()->root["GAME"]["MAX_MOVES"].as<uint8_t>();
}

uint8_t ServerConfig::getGameMaxRevived() {
    return getInstance()->root["GAME"]["MAX_REVIVED"].as<uint8_t>();
}

uint8_t ServerConfig::getCharacterInitialX() {
    return getInstance()->root["CHARACTER"]["INITIAL_X"].as<uint8_t>();
}

uint8_t ServerConfig::getCharacterInitialY() {
    return getInstance()->root["CHARACTER"]["INITIAL_Y"].as<uint8_t>();
}

uint8_t ServerConfig::getCharacterInitialHealth() {
    return getInstance()->root["CHARACTER"]["INITIAL_HEALTH"].as<uint8_t>();
}

uint8_t ServerConfig::getCharacterMaxRevived() {
    return getInstance()->root["CHARACTER"]["MAX_REVIVED"].as<uint8_t>();
}

uint8_t ServerConfig::getCharacterDamageTime() {
    return getInstance()->root["CHARACTER"]["DAMAGE_TIME"].as<uint8_t>();
}

uint8_t ServerConfig::getCharacterReviveTime() {
    return getInstance()->root["CHARACTER"]["REVIVE_TIME"].as<uint8_t>();
}

uint8_t ServerConfig::getCharacterRespawnTime() {
    return getInstance()->root["CHARACTER"]["RESPAWN_TIME"].as<uint8_t>();
}

uint8_t ServerConfig::getCharacterIntoxicatedTime() {
    return getInstance()->root["CHARACTER"]["INTOXICATED_TIME"].as<uint8_t>();
}

uint8_t ServerConfig::getCharacterMaxMovesPerCell() {
    return getInstance()->root["CHARACTER"]["MAX_MOVES_PER_CELL"].as<uint8_t>();
}

uint8_t ServerConfig::getJazzShootCooldownTime() {
    return getInstance()->root["CHARACTER"]["JAZZ"]["SHOOT_COOLDOWN_TIME"].as<uint8_t>();
}

float ServerConfig::getJazzHorizontalSpeed() {
    return getInstance()->root["CHARACTER"]["JAZZ"]["HORIZONTAL_SPEED"].as<uint8_t>();
}

float ServerConfig::getJazzVerticalSpeed() {
    return getInstance()->root["CHARACTER"]["JAZZ"]["VERTICAL_SPEED"].as<uint8_t>();
}

float ServerConfig::getJazzSprintSpeed() {
    return getInstance()->root["CHARACTER"]["JAZZ"]["SPRINT_SPEED"].as<uint8_t>();
}

uint8_t ServerConfig::getJazzJumpHeight() {
    return getInstance()->root["CHARACTER"]["JAZZ"]["JUMP_HEIGHT"].as<uint8_t>();
}

uint8_t ServerConfig::getLoriShootCooldownTime() {
    return getInstance()->root["CHARACTER"]["LORI"]["SHOOT_COOLDOWN_TIME"].as<uint8_t>();
}

float ServerConfig::getLoriHorizontalSpeed() {
    return getInstance()->root["CHARACTER"]["LORI"]["HORIZONTAL_SPEED"].as<uint8_t>();
}

float ServerConfig::getLoriVerticalSpeed() {
    return getInstance()->root["CHARACTER"]["LORI"]["VERTICAL_SPEED"].as<uint8_t>();
}

float ServerConfig::getLoriSprintSpeed() {
    return getInstance()->root["CHARACTER"]["LORI"]["SPRINT_SPEED"].as<uint8_t>();
}

uint8_t ServerConfig::getLoriJumpHeight() {
    return getInstance()->root["CHARACTER"]["LORI"]["JUMP_HEIGHT"].as<uint8_t>();
}

uint8_t ServerConfig::getSpazShootCooldownTime() {
    return getInstance()->root["CHARACTER"]["SPAZ"]["SHOOT_COOLDOWN_TIME"].as<uint8_t>();
}

float ServerConfig::getSpazHorizontalSpeed() {
    return getInstance()->root["CHARACTER"]["SPAZ"]["HORIZONTAL_SPEED"].as<uint8_t>();
}

float ServerConfig::getSpazVerticalSpeed() {
    return getInstance()->root["CHARACTER"]["SPAZ"]["VERTICAL_SPEED"].as<uint8_t>();
}

float ServerConfig::getSpazSprintSpeed() {
    return getInstance()->root["CHARACTER"]["SPAZ"]["SPRINT_SPEED"].as<uint8_t>();
}

uint8_t ServerConfig::getSpazJumpHeight() {
    return getInstance()->root["CHARACTER"]["SPAZ"]["JUMP_HEIGHT"].as<uint8_t>();
}

uint8_t ServerConfig::getWeaponBlasterBullets() {
    return getInstance()->root["WEAPON"]["BLASTER"]["BULLETS"].as<uint8_t>();
}

uint8_t ServerConfig::getWeaponBlasterDamage() {
    return getInstance()->root["WEAPON"]["BLASTER"]["DAMAGE"].as<uint8_t>();
}

float ServerConfig::getWeaponBlasterFireRate() {
    return getInstance()->root["WEAPON"]["BLASTER"]["FIRE_RATE"].as<float>();
}

uint8_t ServerConfig::getWeaponBouncerBullets() {
    return getInstance()->root["WEAPON"]["BOUNCER"]["BULLETS"].as<uint8_t>();
}

uint8_t ServerConfig::getWeaponBouncerDamage() {
    return getInstance()->root["WEAPON"]["BOUNCER"]["DAMAGE"].as<uint8_t>();
}

float ServerConfig::getWeaponBouncerFireRate() {
    return getInstance()->root["WEAPON"]["BOUNCER"]["FIRE_RATE"].as<float>();
}

uint8_t ServerConfig::getWeaponFreezerBullets() {
    return getInstance()->root["WEAPON"]["FREEZER"]["BULLETS"].as<uint8_t>();
}

uint8_t ServerConfig::getWeaponFreezerDamage() {
    return getInstance()->root["WEAPON"]["FREEZER"]["DAMAGE"].as<uint8_t>();
}

float ServerConfig::getWeaponFreezerFireRate() {
    return getInstance()->root["WEAPON"]["FREEZER"]["FIRE_RATE"].as<float>();
}

uint8_t ServerConfig::getWeaponRFMissileBullets() {
    return getInstance()->root["WEAPON"]["RFMISSILE"]["BULLETS"].as<uint8_t>();
}

uint8_t ServerConfig::getWeaponRFMissileDamage() {
    return getInstance()->root["WEAPON"]["RFMISSILE"]["DAMAGE"].as<uint8_t>();
}

float ServerConfig::getWeaponRFMissileFireRate() {
    return getInstance()->root["WEAPON"]["RFMISSILE"]["FIRE_RATE"].as<float>();
}

uint8_t ServerConfig::getObstacleMoves() {
    return getInstance()->root["OBSTACLE"]["MOVES"].as<uint8_t>();
}


void ServerConfig::deleteInstance() {
    if (instance != nullptr) {
        delete instance;
        instance = nullptr;
    }
}

uint8_t ServerConfig::getWalkingEnemyInitialX() {
    return getInstance()->root["ENEMY"]["WALKING"]["INITIAL_X"].as<uint8_t>();
}

uint8_t ServerConfig::getWalkingEnemyInitialY() {
    return getInstance()->root["ENEMY"]["WALKING"]["INITIAL_Y"].as<uint8_t>();
}

uint8_t ServerConfig::getWalkingEnemyMaxMovesPerCell() {
    return getInstance()->root["ENEMY"]["WALKING"]["MAX_MOVES_PER_CELL"].as<uint8_t>();
}

uint8_t ServerConfig::getWalkingEnemyInitialHealth() {
    return getInstance()->root["ENEMY"]["WALKING"]["INITIAL_HEALTH"].as<uint8_t>();
}

uint8_t ServerConfig::getWalkingEnemyDamage() {
    return getInstance()->root["ENEMY"]["WALKING"]["DAMAGE"].as<uint8_t>();
}

uint8_t ServerConfig::getWalkingEnemyMaxRevived() {
    return getInstance()->root["ENEMY"]["WALKING"]["MAX_REVIVED"].as<uint8_t>();
}

uint8_t ServerConfig::getWalkingEnemyDamageTime() {
    return getInstance()->root["ENEMY"]["WALKING"]["DAMAGE_TIME"].as<uint8_t>();
}

uint8_t ServerConfig::getWalkingEnemyReviveTime() {
    return getInstance()->root["ENEMY"]["WALKING"]["REVIVE_TIME"].as<uint8_t>();
}

uint8_t ServerConfig::getWalkingEnemyHitDistance() {
    return getInstance()->root["ENEMY"]["WALKING"]["HIT_DISTANCE"].as<uint8_t>();
}

uint8_t ServerConfig::getWalkingEnemyHitDistanceY() {
    return getInstance()->root["ENEMY"]["WALKING"]["HIT_DISTANCE_Y"].as<uint8_t>();
}

uint8_t ServerConfig::getWalkingEnemyViewDistance() {
    return getInstance()->root["ENEMY"]["WALKING"]["VIEW_DISTANCE"].as<uint8_t>();
}

uint8_t ServerConfig::getWalkingEnemyViewDistanceHit() {
    return getInstance()->root["ENEMY"]["WALKING"]["VIEW_DISTANCE_HIT"].as<uint8_t>();
}

std::vector<uint8_t> ServerConfig::getWalkingEnemyWalkProb() {
    std::vector<uint8_t> walkProb;
    for (const auto& prob: getInstance()->root["ENEMY"]["WALKING"]["WALK_PROB"]) {
        walkProb.push_back(prob.as<uint8_t>());
    }
    return walkProb;
}


uint8_t ServerConfig::getFlyingEnemyInitialX() {
    return getInstance()->root["ENEMY"]["FLYING"]["INITIAL_X"].as<uint8_t>();
}

uint8_t ServerConfig::getFlyingEnemyInitialY() {
    return getInstance()->root["ENEMY"]["FLYING"]["INITIAL_Y"].as<uint8_t>();
}

uint8_t ServerConfig::getFlyingEnemyMaxMovesPerCell() {
    return getInstance()->root["ENEMY"]["FLYING"]["MAX_MOVES_PER_CELL"].as<uint8_t>();
}

uint8_t ServerConfig::getFlyingEnemyInitialHealth() {
    return getInstance()->root["ENEMY"]["FLYING"]["INITIAL_HEALTH"].as<uint8_t>();
}

uint8_t ServerConfig::getFlyingEnemyDamage() {
    return getInstance()->root["ENEMY"]["FLYING"]["DAMAGE"].as<uint8_t>();
}

uint8_t ServerConfig::getFlyingEnemyMaxMoves() {
    return getInstance()->root["ENEMY"]["FLYING"]["MAX_MOVES"].as<uint8_t>();
}

uint8_t ServerConfig::getFlyingEnemyMaxRevived() {
    return getInstance()->root["ENEMY"]["FLYING"]["MAX_REVIVED"].as<uint8_t>();
}

uint8_t ServerConfig::getFlyingEnemyDamageTime() {
    return getInstance()->root["ENEMY"]["FLYING"]["DAMAGE_TIME"].as<uint8_t>();
}

uint8_t ServerConfig::getFlyingEnemyReviveTime() {
    return getInstance()->root["ENEMY"]["FLYING"]["REVIVE_TIME"].as<uint8_t>();
}

uint8_t ServerConfig::getFlyingEnemyHitDistance() {
    return getInstance()->root["ENEMY"]["FLYING"]["HIT_DISTANCE"].as<uint8_t>();
}

uint8_t ServerConfig::getFlyingEnemyHitDistanceY() {
    return getInstance()->root["ENEMY"]["FLYING"]["HIT_DISTANCE_Y"].as<uint8_t>();
}

uint8_t ServerConfig::getFlyingEnemyViewDistance() {
    return getInstance()->root["ENEMY"]["FLYING"]["VIEW_DISTANCE"].as<uint8_t>();
}

uint8_t ServerConfig::getFlyingEnemyViewDistanceHit() {
    return getInstance()->root["ENEMY"]["FLYING"]["VIEW_DISTANCE_HIT"].as<uint8_t>();
}

std::vector<uint8_t> ServerConfig::getFlyingEnemyFlyProb() {
    std::vector<uint8_t> flyProb;
    for (const auto& prob: getInstance()->root["ENEMY"]["FLYING"]["FLY_PROB"]) {
        flyProb.push_back(prob.as<uint8_t>());
    }
    return flyProb;
}


uint8_t ServerConfig::getJumpingEnemyInitialX() {
    return getInstance()->root["ENEMY"]["JUMPING"]["INITIAL_X"].as<uint8_t>();
}

uint8_t ServerConfig::getJumpingEnemyInitialY() {
    return getInstance()->root["ENEMY"]["JUMPING"]["INITIAL_Y"].as<uint8_t>();
}

uint8_t ServerConfig::getJumpingEnemyMaxMovesPerCell() {
    return getInstance()->root["ENEMY"]["JUMPING"]["MAX_MOVES_PER_CELL"].as<uint8_t>();
}

uint8_t ServerConfig::getJumpingEnemyInitialHealth() {
    return getInstance()->root["ENEMY"]["JUMPING"]["INITIAL_HEALTH"].as<uint8_t>();
}

uint8_t ServerConfig::getJumpingEnemyDamage() {
    return getInstance()->root["ENEMY"]["JUMPING"]["DAMAGE"].as<uint8_t>();
}

uint8_t ServerConfig::getJumpingEnemyMaxMoves() {
    return getInstance()->root["ENEMY"]["JUMPING"]["MAX_MOVES"].as<uint8_t>();
}

uint8_t ServerConfig::getJumpingEnemyMaxRevived() {
    return getInstance()->root["ENEMY"]["JUMPING"]["MAX_REVIVED"].as<uint8_t>();
}

uint8_t ServerConfig::getJumpingEnemyDamageTime() {
    return getInstance()->root["ENEMY"]["JUMPING"]["DAMAGE_TIME"].as<uint8_t>();
}

uint8_t ServerConfig::getJumpingEnemyReviveTime() {
    return getInstance()->root["ENEMY"]["JUMPING"]["REVIVE_TIME"].as<uint8_t>();
}

uint8_t ServerConfig::getJumpingEnemyHitDistance() {
    return getInstance()->root["ENEMY"]["JUMPING"]["HIT_DISTANCE"].as<uint8_t>();
}

uint8_t ServerConfig::getJumpingEnemyHitDistanceY() {
    return getInstance()->root["ENEMY"]["JUMPING"]["HIT_DISTANCE_Y"].as<uint8_t>();
}

uint8_t ServerConfig::getJumpingEnemyViewDistance() {
    return getInstance()->root["ENEMY"]["JUMPING"]["VIEW_DISTANCE"].as<uint8_t>();
}

uint8_t ServerConfig::getJumpingEnemyViewDistanceHit() {
    return getInstance()->root["ENEMY"]["JUMPING"]["VIEW_DISTANCE_HIT"].as<uint8_t>();
}

std::vector<uint8_t> ServerConfig::getJumpingEnemyJumpProb() {
    std::vector<uint8_t> jumpProb;
    for (const auto& prob: getInstance()->root["ENEMY"]["JUMPING"]["JUMP_PROB"]) {
        jumpProb.push_back(prob.as<uint8_t>());
    }
    return jumpProb;
}

uint8_t ServerConfig::getGameMapSizeX(const std::string& mapName) {
    return getInstance()->root["GAMEMAP"][mapName]["SIZE_X"].as<uint8_t>();
}

uint8_t ServerConfig::getGameMapSizeY(const std::string& mapName) {
    return getInstance()->root["GAMEMAP"][mapName]["SIZE_Y"].as<uint8_t>();
}

uint8_t ServerConfig::getGameMapObstacles(const std::string& mapName) {
    return getInstance()->root["GAMEMAP"][mapName]["OBSTACLES"].as<uint8_t>();
}

uint8_t ServerConfig::getGameMapEnemies(const std::string& mapName) {
    return getInstance()->root["GAMEMAP"][mapName]["ENEMIES"].as<uint8_t>();
}

uint8_t ServerConfig::getGameMapGems(const std::string& mapName) {
    return getInstance()->root["GAMEMAP"][mapName]["GEMS"].as<uint8_t>();
}

uint8_t ServerConfig::getGameMapSilverCoins(const std::string& mapName) {
    return getInstance()->root["GAMEMAP"][mapName]["SILVER_COINS"].as<uint8_t>();
}

uint8_t ServerConfig::getGameMapGoldCoins(const std::string& mapName) {
    return getInstance()->root["GAMEMAP"][mapName]["GOLD_COINS"].as<uint8_t>();
}
