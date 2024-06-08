#include "ClientConfig.h"

#include <unistd.h>

const static std::string YAML_FILE_PATH = "config/client.yaml";

// Singleton Pattern so it can be accessed anywhere.
ClientConfig* ClientConfig::instance = nullptr;

ClientConfig::ClientConfig() { this->root = YAML::LoadFile(YAML_FILE_PATH); }

ClientConfig* ClientConfig::getInstance() {
    if (instance == nullptr) {
        instance = new ClientConfig();
    }
    return instance;
}

// Logger
std::string ClientConfig::getLogFile() {
    std::string logFile = getInstance()->root["LOG_FILE"].as<std::string>();
    std::size_t pos = logFile.find(".log");
    if (pos != std::string::npos) {
        std::ostringstream pidStream;
        pidStream << getpid();
        logFile.insert(pos, "_" + pidStream.str());
    }
    return logFile;
}

// Files
std::string ClientConfig::getEpisodeFile() {
    return getInstance()->root["EPISODES_FILE"].as<std::string>();
}

std::string ClientConfig::getCharacterSelectFile() {
    return getInstance()->root["CHARACTERS_SELECT_FILE"].as<std::string>();
}

std::string ClientConfig::getJazzFile() {
    return getInstance()->root["JAZZ_FILE"].as<std::string>();
}

std::string ClientConfig::getSpazFile() {
    return getInstance()->root["SPAZ_FILE"].as<std::string>();
}

std::string ClientConfig::getLoriFile() {
    return getInstance()->root["LORI_FILE"].as<std::string>();
}

std::string ClientConfig::getTurtleFile() {
    return getInstance()->root["TURTLE_FILE"].as<std::string>();
}

std::string ClientConfig::getSFXFile() { return getInstance()->root["SFX_FILE"].as<std::string>(); }

std::string ClientConfig::getItemsFile() {
    return getInstance()->root["ITEMS_FILE"].as<std::string>();
}

// Colour Keys
std::tuple<int, int, int> ClientConfig::getEpisodesColourKey() {
    YAML::Node episodesColourKeyNode = getInstance()->root["EPISODES_SELECT_CK"];
    return std::make_tuple(episodesColourKeyNode[0].as<int>(), episodesColourKeyNode[1].as<int>(),
                           episodesColourKeyNode[2].as<int>());
}

std::tuple<int, int, int> ClientConfig::getCharacterSelectColourKey() {
    YAML::Node characterSelectColourKeyNode = getInstance()->root["CHARACTER_SELECT_CK"];
    return std::make_tuple(characterSelectColourKeyNode[0].as<int>(),
                           characterSelectColourKeyNode[1].as<int>(),
                           characterSelectColourKeyNode[2].as<int>());
}

std::tuple<int, int, int> ClientConfig::getJazzColourKey() {
    YAML::Node jazzColourKeyNode = getInstance()->root["JAZZ_FILE_CK"];
    return std::make_tuple(jazzColourKeyNode[0].as<int>(), jazzColourKeyNode[1].as<int>(),
                           jazzColourKeyNode[2].as<int>());
}

std::tuple<int, int, int> ClientConfig::getSpazColourKey() {
    YAML::Node spazColourKeyNode = getInstance()->root["SPAZ_FILE_CK"];
    return std::make_tuple(spazColourKeyNode[0].as<int>(), spazColourKeyNode[1].as<int>(),
                           spazColourKeyNode[2].as<int>());
}

std::tuple<int, int, int> ClientConfig::getLoriColourKey() {
    YAML::Node loriColourKeyNode = getInstance()->root["LORI_FILE_CK"];
    return std::make_tuple(loriColourKeyNode[0].as<int>(), loriColourKeyNode[1].as<int>(),
                           loriColourKeyNode[2].as<int>());
}

std::tuple<int, int, int> ClientConfig::getTurtleColourKey() {
    YAML::Node turtleColourKeyNode = getInstance()->root["TURTLE_FILE_CK"];
    return std::make_tuple(turtleColourKeyNode[0].as<int>(), turtleColourKeyNode[1].as<int>(),
                           turtleColourKeyNode[2].as<int>());
}

std::tuple<int, int, int> ClientConfig::getSFXColourKey() {
    YAML::Node sfxColourKeyNode = getInstance()->root["SFX_FILE_CK"];
    return std::make_tuple(sfxColourKeyNode[0].as<int>(), sfxColourKeyNode[1].as<int>(),
                           sfxColourKeyNode[2].as<int>());
}

std::tuple<int, int, int> ClientConfig::getItemsColourKey() {
    YAML::Node itemsColourKeyNode = getInstance()->root["ITEMS_FILE_CK"];
    return std::make_tuple(itemsColourKeyNode[0].as<int>(), itemsColourKeyNode[1].as<int>(),
                           itemsColourKeyNode[2].as<int>());
}

// Rectangular Sprites
std::vector<std::vector<int>> ClientConfig::getEpisodesSprites() {
    YAML::Node episodesSpritesNode = getInstance()->root["EPISODES_SPRITES"];
    std::vector<std::vector<int>> episodesSprites;
    for (YAML::const_iterator it = episodesSpritesNode.begin(); it != episodesSpritesNode.end();
         ++it) {
        episodesSprites.push_back(it->as<std::vector<int>>());
    }
    return episodesSprites;
}

// Enemies
// Turtle
std::vector<std::vector<int>> ClientConfig::getTurtleWalkingSprites() {
    YAML::Node turtleWalkingSpritesNode = getInstance()->root["TURTLE_WALKING_SPRITES"];
    std::vector<std::vector<int>> turtleWalkingSprites;
    for (YAML::const_iterator it = turtleWalkingSpritesNode.begin();
         it != turtleWalkingSpritesNode.end(); ++it) {
        turtleWalkingSprites.push_back(it->as<std::vector<int>>());
    }
    return turtleWalkingSprites;
}

std::vector<std::vector<int>> ClientConfig::getTurtleAttackingSprites() {
    YAML::Node turtleAttackingSpritesNode = getInstance()->root["TURTLE_ATTACKING_SPRITES"];
    std::vector<std::vector<int>> turtleAttackingSprites;
    for (YAML::const_iterator it = turtleAttackingSpritesNode.begin();
         it != turtleAttackingSpritesNode.end(); ++it) {
        turtleAttackingSprites.push_back(it->as<std::vector<int>>());
    }
    return turtleAttackingSprites;
}

std::vector<std::vector<int>> ClientConfig::getTurtleDyingSprites() {
    YAML::Node turtleDyingSpritesNode = getInstance()->root["TURTLE_DYING_SPRITES"];
    std::vector<std::vector<int>> turtleDyingSprites;
    for (YAML::const_iterator it = turtleDyingSpritesNode.begin();
         it != turtleDyingSpritesNode.end(); ++it) {
        turtleDyingSprites.push_back(it->as<std::vector<int>>());
    }
    return turtleDyingSprites;
}

// Schwartzenguard
std::vector<std::vector<int>> ClientConfig::getSchwartzenguardWalkingSprites() {
    YAML::Node schwartzenguardWalkingSpritesNode =
            getInstance()->root["SCHWARTZENGUARD_WALKING_SPRITES"];
    std::vector<std::vector<int>> schwartzenguardWalkingSprites;
    for (YAML::const_iterator it = schwartzenguardWalkingSpritesNode.begin();
         it != schwartzenguardWalkingSpritesNode.end(); ++it) {
        schwartzenguardWalkingSprites.push_back(it->as<std::vector<int>>());
    }
    return schwartzenguardWalkingSprites;
}

std::vector<std::vector<int>> ClientConfig::getSchwartzenguardAttackingSprites() {
    YAML::Node schwartzenguardAttackingSpritesNode =
            getInstance()->root["SCHWARTZENGUARD_ATTACKING_SPRITES"];
    std::vector<std::vector<int>> schwartzenguardAttackingSprites;
    for (YAML::const_iterator it = schwartzenguardAttackingSpritesNode.begin();
         it != schwartzenguardAttackingSpritesNode.end(); ++it) {
        schwartzenguardAttackingSprites.push_back(it->as<std::vector<int>>());
    }
    return schwartzenguardAttackingSprites;
}

std::vector<std::vector<int>> ClientConfig::getSchwartzenguardDyingSprites() {
    YAML::Node schwartzenguardDyingSpritesNode =
            getInstance()->root["SCHWARTZENGUARD_DYING_SPRITES"];
    std::vector<std::vector<int>> schwartzenguardDyingSprites;
    for (YAML::const_iterator it = schwartzenguardDyingSpritesNode.begin();
         it != schwartzenguardDyingSpritesNode.end(); ++it) {
        schwartzenguardDyingSprites.push_back(it->as<std::vector<int>>());
    }
    return schwartzenguardDyingSprites;
}

// YellowMons
std::vector<std::vector<int>> ClientConfig::getYellowMonsWalkingSprites() {
    YAML::Node yellowMonsWalkingSpritesNode = getInstance()->root["YELLOWMONS_WALKING_SPRITES"];
    std::vector<std::vector<int>> yellowMonsWalkingSprites;
    for (YAML::const_iterator it = yellowMonsWalkingSpritesNode.begin();
         it != yellowMonsWalkingSpritesNode.end(); ++it) {
        yellowMonsWalkingSprites.push_back(it->as<std::vector<int>>());
    }
    return yellowMonsWalkingSprites;
}

std::vector<std::vector<int>> ClientConfig::getYellowMonsAttackingSprites() {
    YAML::Node yellowMonsAttackingSpritesNode = getInstance()->root["YELLOWMONS_ATTACKING_SPRITES"];
    std::vector<std::vector<int>> yellowMonsAttackingSprites;
    for (YAML::const_iterator it = yellowMonsAttackingSpritesNode.begin();
         it != yellowMonsAttackingSpritesNode.end(); ++it) {
        yellowMonsAttackingSprites.push_back(it->as<std::vector<int>>());
    }
    return yellowMonsAttackingSprites;
}

std::vector<std::vector<int>> ClientConfig::getYellowMonsDyingSprites() {
    YAML::Node yellowMonsDyingSpritesNode = getInstance()->root["YELLOWMONS_DYING_SPRITES"];
    std::vector<std::vector<int>> yellowMonsDyingSprites;
    for (YAML::const_iterator it = yellowMonsDyingSpritesNode.begin();
         it != yellowMonsDyingSpritesNode.end(); ++it) {
        yellowMonsDyingSprites.push_back(it->as<std::vector<int>>());
    }
    return yellowMonsDyingSprites;
}

// Players
// Jazz
std::vector<std::vector<int>> ClientConfig::getJazzWalkingSprites() {
    YAML::Node jazzWalkingSpritesNode = getInstance()->root["JAZZ_WALKING"];
    std::vector<std::vector<int>> jazzWalkingSprites;
    for (YAML::const_iterator it = jazzWalkingSpritesNode.begin();
         it != jazzWalkingSpritesNode.end(); ++it) {
        jazzWalkingSprites.push_back(it->as<std::vector<int>>());
    }
    return jazzWalkingSprites;
}

std::vector<std::vector<int>> ClientConfig::getJazzRunningSprites() {
    YAML::Node jazzRunningSpritesNode = getInstance()->root["JAZZ_RUNNING"];
    std::vector<std::vector<int>> jazzRunningSprites;
    for (YAML::const_iterator it = jazzRunningSpritesNode.begin();
         it != jazzRunningSpritesNode.end(); ++it) {
        jazzRunningSprites.push_back(it->as<std::vector<int>>());
    }
    return jazzRunningSprites;
}

std::vector<std::vector<int>> ClientConfig::getJazzShootingSprites() {
    YAML::Node jazzShootingSpritesNode = getInstance()->root["JAZZ_SHOOTING"];
    std::vector<std::vector<int>> jazzShootingSprites;
    for (YAML::const_iterator it = jazzShootingSpritesNode.begin();
         it != jazzShootingSpritesNode.end(); ++it) {
        jazzShootingSprites.push_back(it->as<std::vector<int>>());
    }
    return jazzShootingSprites;
}

std::vector<std::vector<int>> ClientConfig::getJazzJumpingSprites() {
    YAML::Node jazzJumpingSpritesNode = getInstance()->root["JAZZ_JUMPING"];
    std::vector<std::vector<int>> jazzJumpingSprites;
    for (YAML::const_iterator it = jazzJumpingSpritesNode.begin();
         it != jazzJumpingSpritesNode.end(); ++it) {
        jazzJumpingSprites.push_back(it->as<std::vector<int>>());
    }
    return jazzJumpingSprites;
}

std::vector<std::vector<int>> ClientConfig::getJazzDashingSprites() {
    YAML::Node jazzDashingSpritesNode = getInstance()->root["JAZZ_DASHING"];
    std::vector<std::vector<int>> jazzDashingSprites;
    for (YAML::const_iterator it = jazzDashingSpritesNode.begin();
         it != jazzDashingSpritesNode.end(); ++it) {
        jazzDashingSprites.push_back(it->as<std::vector<int>>());
    }
    return jazzDashingSprites;
}

// Spaz
std::vector<std::vector<int>> ClientConfig::getSpazWalkingSprites() {
    YAML::Node spazWalkingSpritesNode = getInstance()->root["SPAZ_WALKING"];
    std::vector<std::vector<int>> spazWalkingSprites;
    for (YAML::const_iterator it = spazWalkingSpritesNode.begin();
         it != spazWalkingSpritesNode.end(); ++it) {
        spazWalkingSprites.push_back(it->as<std::vector<int>>());
    }
    return spazWalkingSprites;
}

std::vector<std::vector<int>> ClientConfig::getSpazRunningSprites() {
    YAML::Node spazRunningSpritesNode = getInstance()->root["SPAZ_RUNNING"];
    std::vector<std::vector<int>> spazRunningSprites;
    for (YAML::const_iterator it = spazRunningSpritesNode.begin();
         it != spazRunningSpritesNode.end(); ++it) {
        spazRunningSprites.push_back(it->as<std::vector<int>>());
    }
    return spazRunningSprites;
}

std::vector<std::vector<int>> ClientConfig::getSpazShootingSprites() {
    YAML::Node spazShootingSpritesNode = getInstance()->root["SPAZ_SHOOTING"];
    std::vector<std::vector<int>> spazShootingSprites;
    for (YAML::const_iterator it = spazShootingSpritesNode.begin();
         it != spazShootingSpritesNode.end(); ++it) {
        spazShootingSprites.push_back(it->as<std::vector<int>>());
    }
    return spazShootingSprites;
}

std::vector<std::vector<int>> ClientConfig::getSpazJumpingSprites() {
    YAML::Node spazJumpingSpritesNode = getInstance()->root["SPAZ_JUMPING"];
    std::vector<std::vector<int>> spazJumpingSprites;
    for (YAML::const_iterator it = spazJumpingSpritesNode.begin();
         it != spazJumpingSpritesNode.end(); ++it) {
        spazJumpingSprites.push_back(it->as<std::vector<int>>());
    }
    return spazJumpingSprites;
}

// Lori
std::vector<std::vector<int>> ClientConfig::getLoriWalkingSprites() {
    YAML::Node loriWalkingSpritesNode = getInstance()->root["LORI_WALKING"];
    std::vector<std::vector<int>> loriWalkingSprites;
    for (YAML::const_iterator it = loriWalkingSpritesNode.begin();
         it != loriWalkingSpritesNode.end(); ++it) {
        loriWalkingSprites.push_back(it->as<std::vector<int>>());
    }
    return loriWalkingSprites;
}

std::vector<std::vector<int>> ClientConfig::getLoriRunningSprites() {
    YAML::Node loriRunningSpritesNode = getInstance()->root["LORI_RUNNING"];
    std::vector<std::vector<int>> loriRunningSprites;
    for (YAML::const_iterator it = loriRunningSpritesNode.begin();
         it != loriRunningSpritesNode.end(); ++it) {
        loriRunningSprites.push_back(it->as<std::vector<int>>());
    }
    return loriRunningSprites;
}

std::vector<std::vector<int>> ClientConfig::getLoriShootingSprites() {
    YAML::Node loriShootingSpritesNode = getInstance()->root["LORI_SHOOTING"];
    std::vector<std::vector<int>> loriShootingSprites;
    for (YAML::const_iterator it = loriShootingSpritesNode.begin();
         it != loriShootingSpritesNode.end(); ++it) {
        loriShootingSprites.push_back(it->as<std::vector<int>>());
    }
    return loriShootingSprites;
}

std::vector<std::vector<int>> ClientConfig::getLoriJumpingSprites() {
    YAML::Node loriJumpingSpritesNode = getInstance()->root["LORI_JUMPING"];
    std::vector<std::vector<int>> loriJumpingSprites;
    for (YAML::const_iterator it = loriJumpingSpritesNode.begin();
         it != loriJumpingSpritesNode.end(); ++it) {
        loriJumpingSprites.push_back(it->as<std::vector<int>>());
    }
    return loriJumpingSprites;
}

// Items
std::vector<std::vector<int>> ClientConfig::getRedGemSprites() {
    YAML::Node redGemSpritesNode = getInstance()->root["RED_GEM_SPRITES"];
    std::vector<std::vector<int>> redGemSprites;
    for (YAML::const_iterator it = redGemSpritesNode.begin(); it != redGemSpritesNode.end(); ++it) {
        redGemSprites.push_back(it->as<std::vector<int>>());
    }
    return redGemSprites;
}

std::vector<std::vector<int>> ClientConfig::getGoldCoinSprites() {
    YAML::Node goldCoinSpritesNode = getInstance()->root["GOLD_COIN_SPRITES"];
    std::vector<std::vector<int>> goldCoinSprites;
    for (YAML::const_iterator it = goldCoinSpritesNode.begin(); it != goldCoinSpritesNode.end();
         ++it) {
        goldCoinSprites.push_back(it->as<std::vector<int>>());
    }
    return goldCoinSprites;
}

std::vector<std::vector<int>> ClientConfig::getSilverCoinSprites() {
    YAML::Node silverCoinSpritesNode = getInstance()->root["SILVER_COIN_SPRITES"];
    std::vector<std::vector<int>> silverCoinSprites;
    for (YAML::const_iterator it = silverCoinSpritesNode.begin(); it != silverCoinSpritesNode.end();
         ++it) {
        silverCoinSprites.push_back(it->as<std::vector<int>>());
    }
    return silverCoinSprites;
}

// Projectiles
std::vector<std::vector<int>> ClientConfig::getNormalProjectileSprites() {
    YAML::Node normalProjectileSpritesNode = getInstance()->root["NORMAL_PROJECTILE_SPRITES"];
    std::vector<std::vector<int>> normalProjectileSprites;
    for (YAML::const_iterator it = normalProjectileSpritesNode.begin();
         it != normalProjectileSpritesNode.end(); ++it) {
        normalProjectileSprites.push_back(it->as<std::vector<int>>());
    }
    return normalProjectileSprites;
}

std::vector<std::vector<int>> ClientConfig::getBlueBulletSprites() {
    YAML::Node blueBulletSpritesNode = getInstance()->root["BLUE_BULLET_SPRITES"];
    std::vector<std::vector<int>> blueBulletSprites;
    for (YAML::const_iterator it = blueBulletSpritesNode.begin(); it != blueBulletSpritesNode.end();
         ++it) {
        blueBulletSprites.push_back(it->as<std::vector<int>>());
    }
    return blueBulletSprites;
}

std::vector<std::vector<int>> ClientConfig::getVioletBulletSprites() {
    YAML::Node violetBulletSpritesNode = getInstance()->root["VIOLET_BULLET_SPRITES"];
    std::vector<std::vector<int>> violetBulletSprites;
    for (YAML::const_iterator it = violetBulletSpritesNode.begin();
         it != violetBulletSpritesNode.end(); ++it) {
        violetBulletSprites.push_back(it->as<std::vector<int>>());
    }
    return violetBulletSprites;
}

std::vector<std::vector<int>> ClientConfig::getRedBombSprites() {
    YAML::Node redBombSpritesNode = getInstance()->root["RED_BOMB_SPRITES"];
    std::vector<std::vector<int>> redBombSprites;
    for (YAML::const_iterator it = redBombSpritesNode.begin(); it != redBombSpritesNode.end();
         ++it) {
        redBombSprites.push_back(it->as<std::vector<int>>());
    }
    return redBombSprites;
}

std::vector<std::vector<int>> ClientConfig::getVioletBombSprites() {
    YAML::Node violetBombSpritesNode = getInstance()->root["VIOLET_BOMB_SPRITES"];
    std::vector<std::vector<int>> violetBombSprites;
    for (YAML::const_iterator it = violetBombSpritesNode.begin(); it != violetBombSpritesNode.end();
         ++it) {
        violetBombSprites.push_back(it->as<std::vector<int>>());
    }
    return violetBombSprites;
}

// Projectile Fire
int ClientConfig::getFireX() { return getInstance()->root["PROJ_X_FIRE"].as<int>(); }

int ClientConfig::getFireY() { return getInstance()->root["PROJ_Y_FIRE"].as<int>(); }

int ClientConfig::getFireWidth() { return getInstance()->root["PROJ_WIDTH_FIRE"].as<int>(); }

int ClientConfig::getFireHeight() { return getInstance()->root["PROJ_HEIGHT_FIRE"].as<int>(); }

// Sprites
std::vector<std::vector<std::pair<int, int>>> ClientConfig::getJazzSelectNameSprites() {
    YAML::Node jazzSelectNameSpritesNode = getInstance()->root["JAZZ_SELECT_NAME"];
    std::vector<std::vector<std::pair<int, int>>> jazzSelectNameSprites;
    for (YAML::const_iterator it = jazzSelectNameSpritesNode.begin();
         it != jazzSelectNameSpritesNode.end(); ++it) {
        std::vector<std::pair<int, int>> jazzSelectNameSprite;
        for (YAML::const_iterator it2 = it->begin(); it2 != it->end(); ++it2) {
            jazzSelectNameSprite.push_back(it2->as<std::pair<int, int>>());
        }
        jazzSelectNameSprites.push_back(jazzSelectNameSprite);
    }
    return jazzSelectNameSprites;
}

std::vector<std::vector<std::pair<int, int>>> ClientConfig::getJazzSelectSprites() {
    YAML::Node jazzSelectSpritesNode = getInstance()->root["JAZZ_SELECT"];
    std::vector<std::vector<std::pair<int, int>>> jazzSelectSprites;
    for (YAML::const_iterator it = jazzSelectSpritesNode.begin(); it != jazzSelectSpritesNode.end();
         ++it) {
        std::vector<std::pair<int, int>> jazzSelectSprite;
        for (YAML::const_iterator it2 = it->begin(); it2 != it->end(); ++it2) {
            jazzSelectSprite.push_back(it2->as<std::pair<int, int>>());
        }
        jazzSelectSprites.push_back(jazzSelectSprite);
    }
    return jazzSelectSprites;
}

std::vector<std::vector<std::pair<int, int>>> ClientConfig::getSpazSelectNameSprites() {
    YAML::Node spazSelectNameSpritesNode = getInstance()->root["SPAZ_SELECT_NAME"];
    std::vector<std::vector<std::pair<int, int>>> spazSelectNameSprites;
    for (YAML::const_iterator it = spazSelectNameSpritesNode.begin();
         it != spazSelectNameSpritesNode.end(); ++it) {
        std::vector<std::pair<int, int>> spazSelectNameSprite;
        for (YAML::const_iterator it2 = it->begin(); it2 != it->end(); ++it2) {
            spazSelectNameSprite.push_back(it2->as<std::pair<int, int>>());
        }
        spazSelectNameSprites.push_back(spazSelectNameSprite);
    }
    return spazSelectNameSprites;
}

std::vector<std::vector<std::pair<int, int>>> ClientConfig::getSpazSelectSprites() {
    YAML::Node spazSelectSpritesNode = getInstance()->root["SPAZ_SELECT"];
    std::vector<std::vector<std::pair<int, int>>> spazSelectSprites;
    for (YAML::const_iterator it = spazSelectSpritesNode.begin(); it != spazSelectSpritesNode.end();
         ++it) {
        std::vector<std::pair<int, int>> spazSelectSprite;
        for (YAML::const_iterator it2 = it->begin(); it2 != it->end(); ++it2) {
            spazSelectSprite.push_back(it2->as<std::pair<int, int>>());
        }
        spazSelectSprites.push_back(spazSelectSprite);
    }
    return spazSelectSprites;
}

std::vector<std::vector<std::pair<int, int>>> ClientConfig::getLoriSelectNameSprites() {
    YAML::Node loriSelectNameSpritesNode = getInstance()->root["LORI_SELECT_NAME"];
    std::vector<std::vector<std::pair<int, int>>> loriSelectNameSprites;
    for (YAML::const_iterator it = loriSelectNameSpritesNode.begin();
         it != loriSelectNameSpritesNode.end(); ++it) {
        std::vector<std::pair<int, int>> loriSelectNameSprite;
        for (YAML::const_iterator it2 = it->begin(); it2 != it->end(); ++it2) {
            loriSelectNameSprite.push_back(it2->as<std::pair<int, int>>());
        }
        loriSelectNameSprites.push_back(loriSelectNameSprite);
    }
    return loriSelectNameSprites;
}

std::vector<std::vector<std::pair<int, int>>> ClientConfig::getLoriSelectSprites() {
    YAML::Node loriSelectSpritesNode = getInstance()->root["LORI_SELECT"];
    std::vector<std::vector<std::pair<int, int>>> loriSelectSprites;
    for (YAML::const_iterator it = loriSelectSpritesNode.begin(); it != loriSelectSpritesNode.end();
         ++it) {
        std::vector<std::pair<int, int>> loriSelectSprite;
        for (YAML::const_iterator it2 = it->begin(); it2 != it->end(); ++it2) {
            loriSelectSprite.push_back(it2->as<std::pair<int, int>>());
        }
        loriSelectSprites.push_back(loriSelectSprite);
    }
    return loriSelectSprites;
}

// Delete Instance
void ClientConfig::deleteInstance() {
    if (instance != nullptr) {
        delete instance;
        instance = nullptr;
    }
}
