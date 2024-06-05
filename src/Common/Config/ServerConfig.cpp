#include "ServerConfig.h"

const static std::string YAML_FILE_PATH = "config/server.yaml";

ServerConfig* ServerConfig::instance = nullptr;

ServerConfig::ServerConfig() {
    this->root = YAML::LoadFile(YAML_FILE_PATH);
}

ServerConfig* ServerConfig::getInstance() {
    if (instance == nullptr) {
        instance = new ServerConfig();
    }
    return instance;
}

std::string ServerConfig::getLogFile() {
    return getInstance()->root["LOG_FILE"].as<std::string>();
}

int ServerConfig::getGameMaxMoves() {
    return getInstance()->root["GAME"]["MAX_MOVES"].as<int>();
}

int ServerConfig::getGameMaxRevived() {
    return getInstance()->root["GAME"]["MAX_REVIVED"].as<int>();
}

int ServerConfig::getCharacterInitialX() {
    return getInstance()->root["CHARACTER"]["INITIAL_X"].as<int>();
}

int ServerConfig::getCharacterInitialY() {
    return getInstance()->root["CHARACTER"]["INITIAL_Y"].as<int>();
}

int ServerConfig::getCharacterInitialHealth() {
    return getInstance()->root["CHARACTER"]["INITIAL_HEALTH"].as<int>();
}

int ServerConfig::getCharacterMaxMoves() {
    return getInstance()->root["CHARACTER"]["MAX_MOVES"].as<int>();
}

int ServerConfig::getCharacterMaxRevived() {
    return getInstance()->root["CHARACTER"]["MAX_REVIVED"].as<int>();
}

int ServerConfig::getWeaponBlasterBullets() {
    return getInstance()->root["WEAPON"]["BLASTER"]["BULLETS"].as<int>();
}

int ServerConfig::getWeaponBlasterDamage() {
    return getInstance()->root["WEAPON"]["BLASTER"]["DAMAGE"].as<int>();
}

float ServerConfig::getWeaponBlasterFireRate() {
    return getInstance()->root["WEAPON"]["BLASTER"]["FIRE_RATE"].as<float>();
}

int ServerConfig::getWeaponBouncerBullets() {
    return getInstance()->root["WEAPON"]["BOUNCER"]["BULLETS"].as<int>();
}

int ServerConfig::getWeaponBouncerDamage() {
    return getInstance()->root["WEAPON"]["BOUNCER"]["DAMAGE"].as<int>();
}

float ServerConfig::getWeaponBouncerFireRate() {
    return getInstance()->root["WEAPON"]["BOUNCER"]["FIRE_RATE"].as<float>();
}

int ServerConfig::getWeaponFreezerBullets() {
    return getInstance()->root["WEAPON"]["FREEZER"]["BULLETS"].as<int>();
}

int ServerConfig::getWeaponFreezerDamage() {
    return getInstance()->root["WEAPON"]["FREEZER"]["DAMAGE"].as<int>();
}

float ServerConfig::getWeaponFreezerFireRate() {
    return getInstance()->root["WEAPON"]["FREEZER"]["FIRE_RATE"].as<float>();
}

int ServerConfig::getWeaponRFMissileBullets() {
    return getInstance()->root["WEAPON"]["RFMISSILE"]["BULLETS"].as<int>();
}

int ServerConfig::getWeaponRFMissileDamage() {
    return getInstance()->root["WEAPON"]["RFMISSILE"]["DAMAGE"].as<int>();
}

float ServerConfig::getWeaponRFMissileFireRate() {
    return getInstance()->root["WEAPON"]["RFMISSILE"]["FIRE_RATE"].as<float>();
}

int ServerConfig::getObstacleMoves() {
    return getInstance()->root["OBSTACLE"]["MOVES"].as<int>();
}

int ServerConfig::getGameMapSizeX() {
    return getInstance()->root["GAME_MAP"]["SIZE_X"].as<int>();
}

int ServerConfig::getGameMapSizeY() {
    return getInstance()->root["GAME_MAP"]["SIZE_Y"].as<int>();
}

void ServerConfig::deleteInstance() {
    if (instance != nullptr) {
        delete instance;
        instance = nullptr;
    }
}

int ServerConfig::getDamageTime() {
    return getInstance()->root["CHARACTER"]["DAMAGE_TIME"].as<int>();
}

int ServerConfig::getCharacterReviveTime() {
    return getInstance()->root["CHARACTER"]["REVIVE_TIME"].as<int>();
}

int ServerConfig::getEnemyMaxMoves() {
    return getInstance()->root["ENEMY"]["MAX_MOVES"].as<int>();
}

int ServerConfig::getWalkingEnemyInitialX() {
    return getInstance()->root["ENEMY"]["WALKING"]["INITIAL_X"].as<int>();
}

int ServerConfig::getWalkingEnemyInitialY() {
    return getInstance()->root["ENEMY"]["WALKING"]["INITIAL_Y"].as<int>();
}

int ServerConfig::getWalkingEnemyMaxMovesPerCell() {
    return getInstance()->root["ENEMY"]["WALKING"]["MAX_MOVES_PER_CELL"].as<int>();
}

int ServerConfig::getWalkingEnemyInitialHealth() {
    return getInstance()->root["ENEMY"]["WALKING"]["INITIAL_HEALTH"].as<int>();
}

int ServerConfig::getWalkingEnemyDamage() {
    return getInstance()->root["ENEMY"]["WALKING"]["DAMAGE"].as<int>();
}

int ServerConfig::getWalkingEnemyMaxMoves() {
    return getInstance()->root["ENEMY"]["WALKING"]["MAX_MOVES"].as<int>();
}

int ServerConfig::getWalkingEnemyMaxRevived() {
    return getInstance()->root["ENEMY"]["WALKING"]["MAX_REVIVED"].as<int>();
}

int ServerConfig::getWalkingEnemyDamageTime() {
    return getInstance()->root["ENEMY"]["WALKING"]["DAMAGE_TIME"].as<int>();
}

int ServerConfig::getWalkingEnemyReviveTime() {
    return getInstance()->root["ENEMY"]["WALKING"]["REVIVE_TIME"].as<int>();
}

int ServerConfig::getWalkingEnemyHitDistance() {
    return getInstance()->root["ENEMY"]["WALKING"]["HIT_DISTANCE"].as<int>();
}

int ServerConfig::getWalkingEnemyHitDistanceY() {
    return getInstance()->root["ENEMY"]["WALKING"]["HIT_DISTANCE_Y"].as<int>();
}

int ServerConfig::getWalkingEnemyViewDistance() {
    return getInstance()->root["ENEMY"]["WALKING"]["VIEW_DISTANCE"].as<int>();
}

int ServerConfig::getWalkingEnemyViewDistanceHit() {
    return getInstance()->root["ENEMY"]["WALKING"]["VIEW_DISTANCE_HIT"].as<int>();
}

std::vector<int16_t> ServerConfig::getWalkingEnemyWalkProb() {
    std::vector<int16_t> walkProb;
    for (const auto& prob: getInstance()->root["ENEMY"]["WALKING"]["WALK_PROB"]) {
        walkProb.push_back(prob.as<int16_t>());
    }
    return walkProb;
}

std::vector<int16_t> ServerConfig::getWalkingEnemyFlyProb() {
    std::vector<int16_t> flyProb;
    for (const auto& prob: getInstance()->root["ENEMY"]["WALKING"]["FLY_PROB"]) {
        flyProb.push_back(prob.as<int16_t>());
    }
    return flyProb;
}

std::vector<int16_t> ServerConfig::getWalkingEnemyJumpProb() {
    std::vector<int16_t> jumpProb;
    for (const auto& prob: getInstance()->root["ENEMY"]["WALKING"]["JUMP_PROB"]) {
        jumpProb.push_back(prob.as<int16_t>());
    }
    return jumpProb;
}


