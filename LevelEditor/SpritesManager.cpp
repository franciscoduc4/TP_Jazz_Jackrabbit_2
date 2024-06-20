#include "SpritesManager.h"

SpritesManager* SpritesManager::instance = nullptr;

SpritesManager::SpritesManager() {
    root = YAML::LoadFile("Sprites/sprites.yaml");
}

SpritesManager* SpritesManager::getInstance() {
    if (!instance) {
        instance = new SpritesManager();
    }
    return instance;
}

std::vector<int> SpritesManager::getFullFloor() {
    return getInstance()->root["FULL_FLOOR"].as<std::vector<int>>();
}

std::vector<int> SpritesManager::getLargeWoodFloor() {
    return getInstance()->root["LARGE_WOOD_FLOOR"].as<std::vector<int>>();
}

std::vector<std::vector<int>> SpritesManager::getLeftLadder() {
    return getInstance()->root["LEFT_LADDER"].as<std::vector<std::vector<int>>>();
}

std::vector<std::vector<int>> SpritesManager::getLongPlatform() {
    return getInstance()->root["LONG_PLATFORM"].as<std::vector<std::vector<int>>>();
}

std::vector<std::vector<int>> SpritesManager::getRightLadder() {
    return getInstance()->root["RIGHT_LADDER"].as<std::vector<std::vector<int>>>();
}

std::vector<std::vector<int>> SpritesManager::getSmallPlatform() {
    return getInstance()->root["SMALL_PLATFORM"].as<std::vector<std::vector<int>>>();
}

std::vector<std::vector<int>> SpritesManager::getWoodFloor() {
    return getInstance()->root["WOOD_FLOOR"].as<std::vector<std::vector<int>>>();
}

std::vector<std::vector<int>> SpritesManager::getWoodLargeColumn() {
    return getInstance()->root["WOOD_LARGE_COLUMN"].as<std::vector<std::vector<int>>>();
}

std::vector<std::vector<int>> SpritesManager::getTurtle() {
    return getInstance()->root["TURTLE"].as<std::vector<std::vector<int>>>();
}

std::vector<std::vector<int>> SpritesManager::getSchwarzenguard() {
    return getInstance()->root["SCHWARZENGUARD"].as<std::vector<std::vector<int>>>();
}

std::vector<std::vector<int>> SpritesManager::getYellowmon() {
    return getInstance()->root["YELLOWMON"].as<std::vector<std::vector<int>>>();
}

std::vector<std::vector<int>> SpritesManager::getGem() {
    return getInstance()->root["GEM"].as<std::vector<std::vector<int>>>();
}

std::vector<std::vector<int>> SpritesManager::getGoldCoin() {
    return getInstance()->root["GOLD_COIN"].as<std::vector<std::vector<int>>>();
}

std::vector<std::vector<int>> SpritesManager::getSilverCoin() {
    return getInstance()->root["SILVER_COIN"].as<std::vector<std::vector<int>>>();
}

std::vector<std::vector<int>> SpritesManager::getFood() {
    return getInstance()->root["FOOD"].as<std::vector<std::vector<int>>>();
}

std::vector<std::vector<int>> SpritesManager::getJazz() {
    return getInstance()->root["JAZZ"].as<std::vector<std::vector<int>>>();
}

std::vector<std::vector<int>> SpritesManager::getLori() {
    return getInstance()->root["LORI"].as<std::vector<std::vector<int>>>();
}

std::vector<std::vector<int>> SpritesManager::getSpaz() {
    return getInstance()->root["SPAZ"].as<std::vector<std::vector<int>>>();
}

void SpritesManager::deleteInstance() {
    if (instance) {
        delete instance;
        instance = nullptr;
    }
}