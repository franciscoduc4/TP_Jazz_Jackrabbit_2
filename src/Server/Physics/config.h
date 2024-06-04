#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <yaml-cpp/yaml.h>
#include <cstdint>
#include <vector>

class Configuration {
private:
    std::int16_t maxHealth;
    std::int16_t maxAmmo;

    float intoxicatedDuration;
    float respawnTime;

    float walkSpeed;
    float runSpeed;
    float sprintSpeed;
    float jumpHeight;

    std::int16_t initialWeaponAmmo;
    float weaponFireRate;
    float projectileSpeed;
    std::int16_t projectileDamage;

    std::int16_t carrotHealthBoost;

    std::int16_t enemyHealth;
    std::int16_t enemyDamage;
    std::int16_t enemyRespawnTime;
    std::vector<std::int16_t> enemyProbDropAmmo;
    std::vector<std::int16_t> enemyProbDropHealth;
    std::vector<std::int16_t> enemyProbDropPoints;
    std::int16_t maxMoves;
    
    //Constructor privado para el Singleton
    explicit Configuration(const YAML::Node& node);
    void parseConfigurations(const YAML::Node& configNode);

public:
    static Configuration& getInstance();

    Configuration(Configuration&) = delete;
    Configuration& operator=(Configuration&) = delete;

    std::int16_t getMaxHealth();
    std::int16_t getMaxAmmo();
    float getIntoxicatedDuration();
    float getRespawnTime();
    float getWalkSpeed();
    float getRunSpeed();
    float getSprintSpeed();
    float getJumpHeight();
    std::int16_t getInitialWeaponAmmo();
    float getWeaponFireRate();
    float getProjectileSpeed();
    std::int16_t getProjectileDamage();
    std::int16_t getCarrotHealthBoost();
    std::int16_t getEnemyHealth();
    std::int16_t getEnemyDamage();
    std::int16_t getEnemyRespawnTime();
    std::vector<std::int16_t> getEnemyProbDropAmmo();
    std::vector<std::int16_t> getEnemyProbDropHealth();
    std::vector<std::int16_t> getEnemyProbDropPoints();
    std::int16_t getMaxMoves();
};

#endif  // CONFIGURATION_H_
