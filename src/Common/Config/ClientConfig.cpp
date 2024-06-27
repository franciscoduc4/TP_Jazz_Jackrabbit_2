#include "ClientConfig.h"

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

// Characters from Font File
std::vector<int> ClientConfig::getGreaterThan() {
    return getInstance()->root["GREATER_THAN"].as<std::vector<int>>();
}

std::vector<int> ClientConfig::getLessThan() {
    return getInstance()->root["LESS_THAN"].as<std::vector<int>>();
}

// Intervals
int ClientConfig::getGamesListRefreshInterval() {
    return getInstance()->root["GAMES_LIST_REFRESH_INTERVAL"].as<int>();
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

std::string ClientConfig::getSchguardFile() {
    return getInstance()->root["SCH_GUARD_FILE"].as<std::string>();
}

std::string ClientConfig::getYellowmonsFile() {
    return getInstance()->root["YELLOWMONS_FILE"].as<std::string>();
}

std::string ClientConfig::getSFXFile() { return getInstance()->root["SFX_FILE"].as<std::string>(); }

std::string ClientConfig::getItemsFile() {
    return getInstance()->root["ITEMS_FILE"].as<std::string>();
}

std::string ClientConfig::getInterfaceFontFile() {
    return getInstance()->root["INTERFACE_FONT_FILE"].as<std::string>();
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

std::tuple<int, int, int> ClientConfig::getInterfaceFontColourKey() {
    YAML::Node interfaceFontColourKeyNode = getInstance()->root["INTERFACE_FONT_CK"];
    return std::make_tuple(interfaceFontColourKeyNode[0].as<int>(),
                           interfaceFontColourKeyNode[1].as<int>(),
                           interfaceFontColourKeyNode[2].as<int>());
}

std::tuple<int, int, int> ClientConfig::getScenesColourKey() {
    YAML::Node scenesColourKeyNode = getInstance()->root["SCENES_CK"];
    return std::make_tuple(scenesColourKeyNode[0].as<int>(),
                           scenesColourKeyNode[1].as<int>(),
                           scenesColourKeyNode[2].as<int>());
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

int ClientConfig::getGameTime() { return getInstance()->root["GAME_TIME"].as<int>(); }


//Sounds
std::vector<std::string> ClientConfig::getSoundsFiles() {
    YAML::Node soundsFilesNode = getInstance()->root["SOUNDS"];
    std::vector<std::string> soundsFiles;
    for (YAML::const_iterator it = soundsFilesNode.begin();
         it != soundsFilesNode.end(); ++it) {
        soundsFiles.push_back(it->as<std::string>());
    }
    return soundsFiles;
}


//Beach
std::vector<std::string> ClientConfig::getBeachFiles() {
    YAML::Node beachFilesNode = getInstance()->root["BEACH"];
    std::vector<std::string> beachFiles;
    for (YAML::const_iterator it = beachFilesNode.begin();
         it != beachFilesNode.end(); ++it) {
        beachFiles.push_back(it->as<std::string>());
    }
    return beachFiles;
}

std::string ClientConfig::getBeachBacksound() { 
    return getInstance()->root["BEACH_BACKSOUND"].as<std::string>();
}

std::vector<std::vector<int>> ClientConfig::getBeachSprites() {
    YAML::Node beachSpritesNode = getInstance()->root["BEACH_PIXELS"];
    std::vector<std::vector<int>> beachSprites;
    for (YAML::const_iterator it = beachSpritesNode.begin();
         it != beachSpritesNode.end(); ++it) {
        beachSprites.push_back(it->as<std::vector<int>>());
    }
    return beachSprites;
}

std::vector<std::vector<int>> ClientConfig::getBeachWidthHeightSprites() {
    YAML::Node beachWidthHeightSpritesNode = getInstance()->root["BEACH_WIDTHS_HEIGHTS"];
    std::vector<std::vector<int>> beachWidthsHeights;
    for (YAML::const_iterator it = beachWidthHeightSpritesNode.begin();
         it != beachWidthHeightSpritesNode.end(); ++it) {
        beachWidthsHeights.push_back(it->as<std::vector<int>>());
    }
    return beachWidthsHeights;
}


//Colonius
std::vector<std::string> ClientConfig::getColoniusFiles() {
    YAML::Node coloniusFilesNode = getInstance()->root["COLONIUS"];
    std::vector<std::string> coloniusFiles;
    for (YAML::const_iterator it = coloniusFilesNode.begin();
         it != coloniusFilesNode.end(); ++it) {
        coloniusFiles.push_back(it->as<std::string>());
    }
    return coloniusFiles;
}

std::string ClientConfig::getColoniusBacksound() {
    return getInstance()->root["COLONIUS_BACKSOUND"].as<std::string>();
}

std::vector<std::vector<int>> ClientConfig::getColoniusSprites() {
    YAML::Node coloniusSpritesNode = getInstance()->root["COLONIUS_PIXELS"];
    std::vector<std::vector<int>> coloniusSprites;
    for (YAML::const_iterator it = coloniusSpritesNode.begin();
         it != coloniusSpritesNode.end(); ++it) {
        coloniusSprites.push_back(it->as<std::vector<int>>());
    }
    return coloniusSprites;
}

std::vector<std::vector<int>> ClientConfig::getColoniusWidthHeightSprites() {
    YAML::Node coloniusWidthHeightSpritesNode = getInstance()->root["COLONIUS_WIDTHS_HEIGHTS"];
    std::vector<std::vector<int>> coloniusWidthsHeights;
    for (YAML::const_iterator it = coloniusWidthHeightSpritesNode.begin();
         it != coloniusWidthHeightSpritesNode.end(); ++it) {
        coloniusWidthsHeights.push_back(it->as<std::vector<int>>());
    }
    return coloniusWidthsHeights;
}


//Holidaius
std::vector<std::string> ClientConfig::getHolidaiusFiles() {
    YAML::Node holidaiusFilesNode = getInstance()->root["HOLIDAIUS"];
    std::vector<std::string> holidaiusFiles;
    for (YAML::const_iterator it = holidaiusFilesNode.begin();
         it != holidaiusFilesNode.end(); ++it) {
        holidaiusFiles.push_back(it->as<std::string>());
    }
    return holidaiusFiles;
}

std::string ClientConfig::getHolidaiusBacksound() {
    return getInstance()->root["HOLIDAIUS_BACKSOUND"].as<std::string>();
}

std::vector<std::vector<int>> ClientConfig::getHolidaiusSprites() {
    YAML::Node holidaiusSpritesNode = getInstance()->root["HOLIDAIUS_PIXELS"];
    std::vector<std::vector<int>> holidaiusSprites;
    for (YAML::const_iterator it = holidaiusSpritesNode.begin();
         it != holidaiusSpritesNode.end(); ++it) {
        holidaiusSprites.push_back(it->as<std::vector<int>>());
    }
    return holidaiusSprites;
}

std::vector<std::vector<int>> ClientConfig::getHolidaiusWidthHeightSprites() {
    YAML::Node holidaiusWidthHeightSpritesNode = getInstance()->root["HOLIDAIUS_WIDTHS_HEIGHTS"];
    std::vector<std::vector<int>> holidaiusWidthsHeights;
    for (YAML::const_iterator it = holidaiusWidthHeightSpritesNode.begin();
         it != holidaiusWidthHeightSpritesNode.end(); ++it) {
        holidaiusWidthsHeights.push_back(it->as<std::vector<int>>());
    }
    return holidaiusWidthsHeights;
}


// Enemies
// Turtle

int ClientConfig::getTurtleWidth() { return getInstance()->root["TURTLE_WIDTH"].as<int>(); }

int ClientConfig::getTurtleHeight() { return getInstance()->root["TURTLE_HEIGHT"].as<int>(); }

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

int ClientConfig::getSchWidth() { return getInstance()->root["SCH_WIDTH"].as<int>(); }

int ClientConfig::getSchHeight() { return getInstance()->root["SCH_HEIGHT"].as<int>(); }

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
int ClientConfig::getYellowMonsWidth() { return getInstance()->root["YELLOWMONS_WIDTH"].as<int>(); }

int ClientConfig::getYellowMonsHeight() { return getInstance()->root["YELLOWMONS_HEIGHT"].as<int>(); }

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
int ClientConfig::getPlayerWidth() { return getInstance()->root["PLAYER_WIDTH"].as<int>(); }

int ClientConfig::getPlayerHeight() { return getInstance()->root["PLAYER_HEIGHT"].as<int>(); }

std::vector<std::vector<int>> ClientConfig::getJazzIdleSprites() {
    YAML::Node jazzIdleSpritesNode = getInstance()->root["JAZZ_IDLE"];
    std::vector<std::vector<int>> jazzIdleSprites;
    for (YAML::const_iterator it = jazzIdleSpritesNode.begin();
         it != jazzIdleSpritesNode.end(); ++it) {
        jazzIdleSprites.push_back(it->as<std::vector<int>>());
    }
    return jazzIdleSprites;
}



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

std::vector<std::vector<int>> ClientConfig::getJazzSpecialAttackSprites() {
    YAML::Node jazzSpecialAttackSpritesNode = getInstance()->root["JAZZ_SPECIAL_ATTACK"];
    std::vector<std::vector<int>> jazzSpecialAttackSprites;
    for (YAML::const_iterator it = jazzSpecialAttackSpritesNode.begin();
         it != jazzSpecialAttackSpritesNode.end(); ++it) {
        jazzSpecialAttackSprites.push_back(it->as<std::vector<int>>());
    }
    return jazzSpecialAttackSprites;
}

std::vector<std::vector<int>> ClientConfig::getJazzIntoxicatedSprites() {
    YAML::Node jazzIntoxicatedSpritesNode = getInstance()->root["JAZZ_INTOXICATED"];
    std::vector<std::vector<int>> jazzIntoxicatedSprites;
    for (YAML::const_iterator it = jazzIntoxicatedSpritesNode.begin();
         it != jazzIntoxicatedSpritesNode.end(); ++it) {
        jazzIntoxicatedSprites.push_back(it->as<std::vector<int>>());
    }
    return jazzIntoxicatedSprites;
}

std::vector<std::vector<int>> ClientConfig::getJazzTakingDamageSprites() {
    YAML::Node jazzTakingDamageSpritesNode = getInstance()->root["JAZZ_TAKING_DAMAGE"];
    std::vector<std::vector<int>> jazzTakingDamageSprites;
    for (YAML::const_iterator it = jazzTakingDamageSpritesNode.begin();
         it != jazzTakingDamageSpritesNode.end(); ++it) {
        jazzTakingDamageSprites.push_back(it->as<std::vector<int>>());
    }
    return jazzTakingDamageSprites;
}

std::vector<std::vector<int>> ClientConfig::getJazzDeadSprites() {
    YAML::Node jazzDeadSpritesNode = getInstance()->root["JAZZ_DEAD"];
    std::vector<std::vector<int>> jazzDeadSprites;
    for (YAML::const_iterator it = jazzDeadSpritesNode.begin();
         it != jazzDeadSpritesNode.end(); ++it) {
        jazzDeadSprites.push_back(it->as<std::vector<int>>());
    }
    return jazzDeadSprites;
}

std::vector<std::vector<int>> ClientConfig::getJazzIconSprites() {
    YAML::Node jazzIconSpritesNode = getInstance()->root["JAZZ_ICON"];
    std::vector<std::vector<int>> jazzIconSprites;
    for (YAML::const_iterator it = jazzIconSpritesNode.begin();
         it != jazzIconSpritesNode.end(); ++it) {
        jazzIconSprites.push_back(it->as<std::vector<int>>());
    }
    return jazzIconSprites;
}


// Spaz
std::vector<std::vector<int>> ClientConfig::getSpazIdleSprites() {
    YAML::Node spazIdleSpritesNode = getInstance()->root["SPAZ_IDLE"];
    std::vector<std::vector<int>> spazIdleSprites;
    for (YAML::const_iterator it = spazIdleSpritesNode.begin();
         it != spazIdleSpritesNode.end(); ++it) {
        spazIdleSprites.push_back(it->as<std::vector<int>>());
    }
    return spazIdleSprites;
}


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

std::vector<std::vector<int>> ClientConfig::getSpazDashingSprites() {
    YAML::Node spazDashingSpritesNode = getInstance()->root["SPAZ_DASHING"];
    std::vector<std::vector<int>> spazDashingSprites;
    for (YAML::const_iterator it = spazDashingSpritesNode.begin();
         it != spazDashingSpritesNode.end(); ++it) {
        spazDashingSprites.push_back(it->as<std::vector<int>>());
    }
    return spazDashingSprites;
}

std::vector<std::vector<int>> ClientConfig::getSpazSpecialAttackSprites() {
    YAML::Node spazSpecialAttackSpritesNode = getInstance()->root["SPAZ_SPECIAL_ATTACK"];
    std::vector<std::vector<int>> spazSpecialAttackSprites;
    for (YAML::const_iterator it = spazSpecialAttackSpritesNode.begin();
         it != spazSpecialAttackSpritesNode.end(); ++it) {
        spazSpecialAttackSprites.push_back(it->as<std::vector<int>>());
    }
    return spazSpecialAttackSprites;
}

std::vector<std::vector<int>> ClientConfig::getSpazIntoxicatedSprites() {
    YAML::Node spazIntoxicatedSpritesNode = getInstance()->root["SPAZ_INTOXICATED"];
    std::vector<std::vector<int>> spazIntoxicatedSprites;
    for (YAML::const_iterator it = spazIntoxicatedSpritesNode.begin();
         it != spazIntoxicatedSpritesNode.end(); ++it) {
        spazIntoxicatedSprites.push_back(it->as<std::vector<int>>());
    }
    return spazIntoxicatedSprites;
}

std::vector<std::vector<int>> ClientConfig::getSpazTakingDamageSprites() {
    YAML::Node spazTakingDamageSpritesNode = getInstance()->root["SPAZ_TAKING_DAMAGE"];
    std::vector<std::vector<int>> spazTakingDamageSprites;
    for (YAML::const_iterator it = spazTakingDamageSpritesNode.begin();
         it != spazTakingDamageSpritesNode.end(); ++it) {
        spazTakingDamageSprites.push_back(it->as<std::vector<int>>());
    }
    return spazTakingDamageSprites;
}

std::vector<std::vector<int>> ClientConfig::getSpazDeadSprites() {
    YAML::Node spazDeadSpritesNode = getInstance()->root["SPAZ_DEAD"];
    std::vector<std::vector<int>> spazDeadSprites;
    for (YAML::const_iterator it = spazDeadSpritesNode.begin();
         it != spazDeadSpritesNode.end(); ++it) {
        spazDeadSprites.push_back(it->as<std::vector<int>>());
    }
    return spazDeadSprites;
}

std::vector<std::vector<int>> ClientConfig::getSpazIconSprites() {
    YAML::Node spazIconSpritesNode = getInstance()->root["SPAZ_ICON"];
    std::vector<std::vector<int>> spazIconSprites;
    for (YAML::const_iterator it = spazIconSpritesNode.begin();
         it != spazIconSpritesNode.end(); ++it) {
        spazIconSprites.push_back(it->as<std::vector<int>>());
    }
    return spazIconSprites;
}


// Lori
std::vector<std::vector<int>> ClientConfig::getLoriIdleSprites() {
    YAML::Node loriIdleSpritesNode = getInstance()->root["LORI_IDLE"];
    std::vector<std::vector<int>> loriIdleSprites;
    for (YAML::const_iterator it = loriIdleSpritesNode.begin();
         it != loriIdleSpritesNode.end(); ++it) {
        loriIdleSprites.push_back(it->as<std::vector<int>>());
    }
    return loriIdleSprites;
}


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

std::vector<std::vector<int>> ClientConfig::getLoriDashingSprites() {
    YAML::Node loriDashingSpritesNode = getInstance()->root["LORI_DASHING"];
    std::vector<std::vector<int>> loriDashingSprites;
    for (YAML::const_iterator it = loriDashingSpritesNode.begin();
         it != loriDashingSpritesNode.end(); ++it) {
        loriDashingSprites.push_back(it->as<std::vector<int>>());
    }
    return loriDashingSprites;
}

std::vector<std::vector<int>> ClientConfig::getLoriSpecialAttackSprites() {
    YAML::Node loriSpecialAttackSpritesNode = getInstance()->root["LORI_SPECIAL_ATTACK"];
    std::vector<std::vector<int>> loriSpecialAttackSprites;
    for (YAML::const_iterator it = loriSpecialAttackSpritesNode.begin();
         it != loriSpecialAttackSpritesNode.end(); ++it) {
        loriSpecialAttackSprites.push_back(it->as<std::vector<int>>());
    }
    return loriSpecialAttackSprites;
}

std::vector<std::vector<int>> ClientConfig::getLoriIntoxicatedSprites() {
    YAML::Node loriIntoxicatedSpritesNode = getInstance()->root["LORI_INTOXICATED"];
    std::vector<std::vector<int>> loriIntoxicatedSprites;
    for (YAML::const_iterator it = loriIntoxicatedSpritesNode.begin();
         it != loriIntoxicatedSpritesNode.end(); ++it) {
        loriIntoxicatedSprites.push_back(it->as<std::vector<int>>());
    }
    return loriIntoxicatedSprites;
}

std::vector<std::vector<int>> ClientConfig::getLoriTakingDamageSprites() {
    YAML::Node loriTakingDamageSpritesNode = getInstance()->root["LORI_TAKING_DAMAGE"];
    std::vector<std::vector<int>> loriTakingDamageSprites;
    for (YAML::const_iterator it = loriTakingDamageSpritesNode.begin();
         it != loriTakingDamageSpritesNode.end(); ++it) {
        loriTakingDamageSprites.push_back(it->as<std::vector<int>>());
    }
    return loriTakingDamageSprites;
}

std::vector<std::vector<int>> ClientConfig::getLoriDeadSprites() {
    YAML::Node loriDeadSpritesNode = getInstance()->root["LORI_DEAD"];
    std::vector<std::vector<int>> loriDeadSprites;
    for (YAML::const_iterator it = loriDeadSpritesNode.begin();
         it != loriDeadSpritesNode.end(); ++it) {
        loriDeadSprites.push_back(it->as<std::vector<int>>());
    }
    return loriDeadSprites;
}

std::vector<std::vector<int>> ClientConfig::getLoriIconSprites() {
    YAML::Node loriIconSpritesNode = getInstance()->root["LORI_ICON"];
    std::vector<std::vector<int>> loriIconSprites;
    for (YAML::const_iterator it = loriIconSpritesNode.begin();
         it != loriIconSpritesNode.end(); ++it) {
        loriIconSprites.push_back(it->as<std::vector<int>>());
    }
    return loriIconSprites;
}


// Items
int ClientConfig::getItemsWidth() { return getInstance()->root["ITEMS_WIDTH"].as<int>(); }

int ClientConfig::getItemsHeight() { return getInstance()->root["ITEMS_HEIGHT"].as<int>(); }

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

std::vector<std::vector<int>> ClientConfig::getCarrotSprites() {
    YAML::Node carrotSpritesNode = getInstance()->root["CARROT_SPRITES"];
    std::vector<std::vector<int>> carrotSprites;
    for (YAML::const_iterator it = carrotSpritesNode.begin(); it != carrotSpritesNode.end();
         ++it) {
        carrotSprites.push_back(it->as<std::vector<int>>());
    }
    return carrotSprites;
}

std::vector<int> ClientConfig::getPoisonedFoodSprites() {
    return getInstance()->root["POISONED_FOOD"].as<std::vector<int>>();
}


// Projectiles
int ClientConfig::getProjWidth() { return getInstance()->root["PROJ_WIDTH"].as<int>(); }

int ClientConfig::getProjHeight() { return getInstance()->root["PROJ_HEIGHT"].as<int>(); }

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

// Weapons
int ClientConfig::getWeaponWidth() { return getInstance()->root["WEAPON_WIDTH"].as<int>(); }

int ClientConfig::getWeaponHeight() { return getInstance()->root["WEAPON_HEIGHT"].as<int>(); }


std::vector<std::vector<int>> ClientConfig::getBlasterSprites() {
    YAML::Node blasterSpritesNode = getInstance()->root["BLASTER"];
    std::vector<std::vector<int>> blasterSprites;
    for (YAML::const_iterator it = blasterSpritesNode.begin(); it != blasterSpritesNode.end();
         ++it) {
        blasterSprites.push_back(it->as<std::vector<int>>());
    }
    return blasterSprites;
}

std::vector<std::vector<int>> ClientConfig::getBouncerSprites() {
    YAML::Node bouncerSpritesNode = getInstance()->root["BOUNCER"];
    std::vector<std::vector<int>> bouncerSprites;
    for (YAML::const_iterator it = bouncerSpritesNode.begin(); it != bouncerSpritesNode.end();
         ++it) {
        bouncerSprites.push_back(it->as<std::vector<int>>());
    }
    return bouncerSprites;
}

std::vector<std::vector<int>> ClientConfig::getRfmissileSprites() {
    YAML::Node rfmissileSpritesNode = getInstance()->root["RFMISSILE"];
    std::vector<std::vector<int>> rfmissileSprites;
    for (YAML::const_iterator it = rfmissileSpritesNode.begin(); it != rfmissileSpritesNode.end();
         ++it) {
        rfmissileSprites.push_back(it->as<std::vector<int>>());
    }
    return rfmissileSprites;
}

std::vector<std::vector<int>> ClientConfig::getFrezzerSprites() {
    YAML::Node frezzerSpritesNode = getInstance()->root["FREZZER"];
    std::vector<std::vector<int>> frezzerSprites;
    for (YAML::const_iterator it = frezzerSpritesNode.begin(); it != frezzerSpritesNode.end();
         ++it) {
        frezzerSprites.push_back(it->as<std::vector<int>>());
    }
    return frezzerSprites;
}



//Interface font
std::vector<std::vector<int>> ClientConfig::getInterfaceFontSprites() {
    YAML::Node interfaceFontSpritesNode = getInstance()->root["INTERFACE_FONT"];
    std::vector<std::vector<int>> interfaceFontSprites;
    for (YAML::const_iterator it = interfaceFontSpritesNode.begin();
        it != interfaceFontSpritesNode.end();
        ++it) {
        interfaceFontSprites.push_back(it->as<std::vector<int>>());
    }
    return interfaceFontSprites;
}

int ClientConfig::getWidthFont() { return getInstance()->root["INTERFACE_WIDTH"].as<int>(); }

int ClientConfig::getHeightFont() { return getInstance()->root["INTERFACE_HEIGHT"].as<int>(); }

//Interface heart
std::vector<std::vector<int>> ClientConfig::getInterfaceHeartSprites() {
    YAML::Node interfaceHeartSpritesNode = getInstance()->root["INTERFACE_HEART"];
    std::vector<std::vector<int>> interfaceHeartSprites;
    for (YAML::const_iterator it = interfaceHeartSpritesNode.begin();
        it != interfaceHeartSpritesNode.end();
        ++it) {
        interfaceHeartSprites.push_back(it->as<std::vector<int>>());
    }
    return interfaceHeartSprites;
}
std::vector<std::vector<int>> ClientConfig::getInterfaceColors() {
    YAML::Node interfaceColorsNode = getInstance()->root["INTERFACE_COLORS"];
    std::vector<std::vector<int>> interfaceColors;
    for (YAML::const_iterator it = interfaceColorsNode.begin();
        it != interfaceColorsNode.end();
        ++it) {
        interfaceColors.push_back(it->as<std::vector<int>>());
    }
    return interfaceColors;
}



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
