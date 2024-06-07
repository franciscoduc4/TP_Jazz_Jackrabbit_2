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

int ServerConfig::getGameMaxMoves() { return getInstance()->root["GAME"]["MAX_MOVES"].as<int>(); }

int ServerConfig::getGameMaxRevived() {
    return getInstance()->root["GAME"]["MAX_REVIVED"].as<int>();
}

int ServerConfig::getCharacterInitialHealth() {
    return getInstance()->root["CHARACTER"]["INITIAL_HEALTH"].as<int>();
}

int ServerConfig::getCharacterReviveTime() {
    return getInstance()->root["CHARACTER"]["REVIVE_TIME"].as<int>();
}

int ServerConfig::getCharacterDamage() {
    return getInstance()->root["CHARACTER"]["DAMAGE"].as<int>();
}

int ServerConfig::getCharacterMaxRevived() {
    return getInstance()->root["CHARACTER"]["MAX_REVIVED"].as<int>();
}

int ServerConfig::getCharacterMaxMovesPerCell() {
    return getInstance()->root["CHARACTER"]["MAX_MOVES_PER_CELL"].as<int>();
}

int ServerConfig::getCharacterRespawnTime() {
    return getInstance()->root["CHARACTER"]["RESPAWN_TIME"].as<int>();
}

int ServerConfig::getCharacterDamageTime() {
    return getInstance()->root["CHARACTER"]["DAMAGE_TIME"].as<int>();
}

int ServerConfig::getCharacterIntoxicatedTime() {
    return getInstance()->root["CHARACTER"]["INTOXICATED_TIME"].as<int>();
}

int ServerConfig::getJazzShootCooldownTime() {
    return getInstance()->root["CHARACTER"]["JAZZ"]["SHOOT_COOLDOWN_TIME"].as<int>();
}

int ServerConfig::getJazzSpeed() {
    return getInstance()->root["CHARACTER"]["JAZZ"]["SPEED"].as<int>();
}

int ServerConfig::getJazzSprintSpeed() {
    return getInstance()->root["CHARACTER"]["JAZZ"]["SPRINT_SPEED"].as<int>();
}

int ServerConfig::getJazzJumpHeight() {
    return getInstance()->root["CHARACTER"]["JAZZ"]["JUMP_HEIGHT"].as<int>();
}

int ServerConfig::getLoriShootCooldownTime() {
    return getInstance()->root["CHARACTER"]["LORI"]["SHOOT_COOLDOWN_TIME"].as<int>();
}

int ServerConfig::getLoriSpeed() {
    return getInstance()->root["CHARACTER"]["LORI"]["SPEED"].as<int>();
}

int ServerConfig::getLoriSprintSpeed() {
    return getInstance()->root["CHARACTER"]["LORI"]["SPRINT_SPEED"].as<int>();
}

int ServerConfig::getLoriJumpHeight() {
    return getInstance()->root["CHARACTER"]["LORI"]["JUMP_HEIGHT"].as<int>();
}

int ServerConfig::getSpazShootCooldownTime() {
    return getInstance()->root["CHARACTER"]["SPAZ"]["SHOOT_COOLDOWN_TIME"].as<int>();
}

int ServerConfig::getSpazSpeed() {
    return getInstance()->root["CHARACTER"]["SPAZ"]["SPEED"].as<int>();
}

int ServerConfig::getSpazSprintSpeed() {
    return getInstance()->root["CHARACTER"]["SPAZ"]["SPRINT_SPEED"].as<int>();
}

int ServerConfig::getSpazJumpHeight() {
    return getInstance()->root["CHARACTER"]["SPAZ"]["JUMP_HEIGHT"].as<int>();
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

int ServerConfig::getObstacleMoves() { return getInstance()->root["OBSTACLE"]["MOVES"].as<int>(); }

int ServerConfig::getGameMapSizeX() { return getInstance()->root["GAME_MAP"]["SIZE_X"].as<int>(); }

int ServerConfig::getGameMapSizeY() { return getInstance()->root["GAME_MAP"]["SIZE_Y"].as<int>(); }

void ServerConfig::deleteInstance() {
    if (instance != nullptr) {
        delete instance;
        instance = nullptr;
    }
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


int ServerConfig::getFlyingEnemyInitialX() {
    return getInstance()->root["ENEMY"]["FLYING"]["INITIAL_X"].as<int>();
}

int ServerConfig::getFlyingEnemyInitialY() {
    return getInstance()->root["ENEMY"]["FLYING"]["INITIAL_Y"].as<int>();
}

int ServerConfig::getFlyingEnemyMaxMovesPerCell() {
    return getInstance()->root["ENEMY"]["FLYING"]["MAX_MOVES_PER_CELL"].as<int>();
}

int ServerConfig::getFlyingEnemyInitialHealth() {
    return getInstance()->root["ENEMY"]["FLYING"]["INITIAL_HEALTH"].as<int>();
}

int ServerConfig::getFlyingEnemyDamage() {
    return getInstance()->root["ENEMY"]["FLYING"]["DAMAGE"].as<int>();
}

int ServerConfig::getFlyingEnemyMaxMoves() {
    return getInstance()->root["ENEMY"]["FLYING"]["MAX_MOVES"].as<int>();
}

int ServerConfig::getFlyingEnemyMaxRevived() {
    return getInstance()->root["ENEMY"]["FLYING"]["MAX_REVIVED"].as<int>();
}

int ServerConfig::getFlyingEnemyDamageTime() {
    return getInstance()->root["ENEMY"]["FLYING"]["DAMAGE_TIME"].as<int>();
}

int ServerConfig::getFlyingEnemyReviveTime() {
    return getInstance()->root["ENEMY"]["FLYING"]["REVIVE_TIME"].as<int>();
}

int ServerConfig::getFlyingEnemyHitDistance() {
    return getInstance()->root["ENEMY"]["FLYING"]["HIT_DISTANCE"].as<int>();
}

int ServerConfig::getFlyingEnemyHitDistanceY() {
    return getInstance()->root["ENEMY"]["FLYING"]["HIT_DISTANCE_Y"].as<int>();
}

int ServerConfig::getFlyingEnemyViewDistance() {
    return getInstance()->root["ENEMY"]["FLYING"]["VIEW_DISTANCE"].as<int>();
}

int ServerConfig::getFlyingEnemyViewDistanceHit() {
    return getInstance()->root["ENEMY"]["FLYING"]["VIEW_DISTANCE_HIT"].as<int>();
}

std::vector<int16_t> ServerConfig::getFlyingEnemyFlyProb() {
    std::vector<int16_t> flyProb;
    for (const auto& prob: getInstance()->root["ENEMY"]["FLYING"]["FLY_PROB"]) {
        flyProb.push_back(prob.as<int16_t>());
    }
    return flyProb;
}


int ServerConfig::getJumpingEnemyInitialX() {
    return getInstance()->root["ENEMY"]["JUMPING"]["INITIAL_X"].as<int>();
}

int ServerConfig::getJumpingEnemyInitialY() {
    return getInstance()->root["ENEMY"]["JUMPING"]["INITIAL_Y"].as<int>();
}

int ServerConfig::getJumpingEnemyMaxMovesPerCell() {
    return getInstance()->root["ENEMY"]["JUMPING"]["MAX_MOVES_PER_CELL"].as<int>();
}

int ServerConfig::getJumpingEnemyInitialHealth() {
    return getInstance()->root["ENEMY"]["JUMPING"]["INITIAL_HEALTH"].as<int>();
}

int ServerConfig::getJumpingEnemyDamage() {
    return getInstance()->root["ENEMY"]["JUMPING"]["DAMAGE"].as<int>();
}

int ServerConfig::getJumpingEnemyMaxMoves() {
    return getInstance()->root["ENEMY"]["JUMPING"]["MAX_MOVES"].as<int>();
}

int ServerConfig::getJumpingEnemyMaxRevived() {
    return getInstance()->root["ENEMY"]["JUMPING"]["MAX_REVIVED"].as<int>();
}

int ServerConfig::getJumpingEnemyDamageTime() {
    return getInstance()->root["ENEMY"]["JUMPING"]["DAMAGE_TIME"].as<int>();
}

int ServerConfig::getJumpingEnemyReviveTime() {
    return getInstance()->root["ENEMY"]["JUMPING"]["REVIVE_TIME"].as<int>();
}

int ServerConfig::getJumpingEnemyHitDistance() {
    return getInstance()->root["ENEMY"]["JUMPING"]["HIT_DISTANCE"].as<int>();
}

int ServerConfig::getJumpingEnemyHitDistanceY() {
    return getInstance()->root["ENEMY"]["JUMPING"]["HIT_DISTANCE_Y"].as<int>();
}

int ServerConfig::getJumpingEnemyViewDistance() {
    return getInstance()->root["ENEMY"]["JUMPING"]["VIEW_DISTANCE"].as<int>();
}

int ServerConfig::getJumpingEnemyViewDistanceHit() {
    return getInstance()->root["ENEMY"]["JUMPING"]["VIEW_DISTANCE_HIT"].as<int>();
}

std::vector<int16_t> ServerConfig::getJumpingEnemyJumpProb() {
    std::vector<int16_t> jumpProb;
    for (const auto& prob: getInstance()->root["ENEMY"]["JUMPING"]["JUMP_PROB"]) {
        jumpProb.push_back(prob.as<int16_t>());
    }
    return jumpProb;
}
