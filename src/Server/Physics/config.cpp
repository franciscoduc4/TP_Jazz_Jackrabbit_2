#include "config.h"
#include <fstream>
#include <iostream>
#include <string>

static std::string configPath = "src/config/server.yaml";

Configuration& Configuration::getInstance() {
    static Configuration instance(YAML::LoadFile(configPath));
    return instance;
}

Configuration::Configuration(const YAML::Node& node) :
    maxHealth(node["general"]["maxHealth"].as<std::int16_t>()),
    maxAmmo(node["general"]["maxAmmo"].as<std::int16_t>()),
    intoxicatedDuration(node["characterStates"]["intoxicatedDuration"].as<float>()),
    respawnTime(node["characterStates"]["respawnTime"].as<float>()),
    walkSpeed(node["characterSpeeds"]["walkSpeed"].as<float>()),
    runSpeed(node["characterSpeeds"]["runSpeed"].as<float>()),
    sprintSpeed(node["characterSpeeds"]["sprintSpeed"].as<float>()),
    jumpHeight(node["characterSpeeds"]["jumpHeight"].as<float>()),
    initialWeaponAmmo(node["weapons"]["initialWeaponAmmo"].as<std::int16_t>()),
    weaponFireRate(node["weapons"]["weaponFireRate"].as<float>()),
    projectileSpeed(node["weapons"]["projectileSpeed"].as<float>()),
    projectileDamage(node["weapons"]["projectileDamage"].as<std::int16_t>()),
    carrotHealthBoost(node["items"]["carrotHealthBoost"].as<std::int16_t>()),
    enemyHealth(node["enemies"]["enemyHealth"].as<std::int16_t>()),
    enemyDamage(node["enemies"]["enemyDamage"].as<std::int16_t>()),
    enemyRespawnTime(node["enemies"]["enemyRespawnTime"].as<std::int16_t>()),
    enemyProbDropAmmo(node["enemies"]["enemyProbDropAmmo"].as<std::vector<std::int16_t>>()),
    enemyProbDropHealth(node["enemies"]["enemyProbDropHealth"].as<std::vector<std::int16_t>>()),
    enemyProbDropPoints(node["enemies"]["enemyProbDropPoints"].as<std::vector<std::int16_t>>()),
    maxMoves(node["general"]["maxMoves"].as<std::int16_t>())
    {}

std::int16_t Configuration::getMaxHealth() {
    return maxHealth;
}

std::int16_t Configuration::getMaxAmmo() {
    return maxAmmo;
}

float Configuration::getIntoxicatedDuration() {
    return intoxicatedDuration;
}

float Configuration::getRespawnTime() {
    return respawnTime;
}

float Configuration::getWalkSpeed() {
    return walkSpeed;
}

float Configuration::getRunSpeed() {
    return runSpeed;
}

float Configuration::getSprintSpeed() {
    return sprintSpeed;
}

float Configuration::getJumpHeight() {
    return jumpHeight;
}

std::int16_t Configuration::getInitialWeaponAmmo() {
    return initialWeaponAmmo;
}

float Configuration::getWeaponFireRate() {
    return weaponFireRate;
}

float Configuration::getProjectileSpeed() {
    return projectileSpeed;
}

std::int16_t Configuration::getProjectileDamage() {
    return projectileDamage;
}

std::int16_t Configuration::getCarrotHealthBoost() {
    return carrotHealthBoost;
}

std::int16_t Configuration::getEnemyHealth() {
    return enemyHealth;
}

std::int16_t Configuration::getEnemyDamage() {
    return enemyDamage;
}

std::int16_t Configuration::getEnemyRespawnTime() {
    return enemyRespawnTime;
}

std::vector<std::int16_t> Configuration::getEnemyProbDropAmmo() {
    return enemyProbDropAmmo;
}

std::vector<std::int16_t> Configuration::getEnemyProbDropHealth() {
    return enemyProbDropHealth;
}

std::vector<std::int16_t> Configuration::getEnemyProbDropPoints() {
    return enemyProbDropPoints;
}

std::int16_t Configuration::getMaxMoves() {
    return maxMoves;
}

