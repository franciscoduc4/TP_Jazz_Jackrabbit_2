#ifndef SPRITESMANAGER_H
#define SPRITESMANAGER_H

#include <yaml-cpp/yaml.h>
#include <string>
#include <utility>
#include <vector>

class SpritesManager {
private:
    static SpritesManager* instance;
    YAML::Node root;
    SpritesManager();
public:
    static SpritesManager* getInstance();

    // OBSTACLES
    static std::vector<int> getFullFloor();
    static std::vector<int> getLargeWoodFloor();
    static std::vector<std::vector<int>> getLeftLadder();
    static std::vector<std::vector<int>> getLongPlatform();
    static std::vector<std::vector<int>> getRightLadder();
    static std::vector<std::vector<int>> getSmallPlatform();
    static std::vector<std::vector<int>> getWoodFloor();
    static std::vector<std::vector<int>> getWoodLargeColumn();

    // ENEMIES
    static std::vector<std::vector<int>> getTurtle();
    static std::vector<std::vector<int>> getSchwarzenguard();
    static std::vector<std::vector<int>> getYellowmon();

    // ITEMS
    static std::vector<std::vector<int>> getGem();
    static std::vector<std::vector<int>> getGoldCoin();
    static std::vector<std::vector<int>> getSilverCoin();
    static std::vector<std::vector<int>> getFood();

    // PLAYERS
    static std::vector<std::vector<int>> getJazz();
    static std::vector<std::vector<int>> getLori();
    static std::vector<std::vector<int>> getSpaz();

    // Delete Instance
    static void deleteInstance();
};


#endif  // SPRITESMANAGER_H
