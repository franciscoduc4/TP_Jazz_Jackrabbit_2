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
    return getInstance()->root["EPISODE_FILE"].as<std::string>();
}

std::string ClientConfig::getCharacterSelectFile() {
    return getInstance()->root["CHARACTER_SELECT_FILE"].as<std::string>();
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

std::string ClientConfig::getSFXFile() {
    return getInstance()->root["SFX_FILE"].as<std::string>();
}

std::string ClientConfig::getItemsFile() {
    return getInstance()->root["ITEMS_FILE"].as<std::string>();
}

// Colour Keys
std::tuple<int, int, int> ClientConfig::getEpisodesColourKey() {
    YAML::Node episodesColourKeyNode = getInstance()->root["EPISODES_COLOUR_KEY"];
    return std::make_tuple(episodesColourKeyNode[0].as<int>(), episodesColourKeyNode[1].as<int>(), episodesColourKeyNode[2].as<int>());
}

std::tuple<int, int, int> ClientConfig::getCharacterSelectColourKey() {
    YAML::Node characterSelectColourKeyNode = getInstance()->root["CHARACTER_SELECT_COLOUR_KEY"];
    return std::make_tuple(characterSelectColourKeyNode[0].as<int>(), characterSelectColourKeyNode[1].as<int>(), characterSelectColourKeyNode[2].as<int>());
}

std::tuple<int, int, int> ClientConfig::getJazzColourKey() {
    YAML::Node jazzColourKeyNode = getInstance()->root["JAZZ_COLOUR_KEY"];
    return std::make_tuple(jazzColourKeyNode[0].as<int>(), jazzColourKeyNode[1].as<int>(), jazzColourKeyNode[2].as<int>());
}

std::tuple<int, int, int> ClientConfig::getSpazColourKey() {
    YAML::Node spazColourKeyNode = getInstance()->root["SPAZ_COLOUR_KEY"];
    return std::make_tuple(spazColourKeyNode[0].as<int>(), spazColourKeyNode[1].as<int>(), spazColourKeyNode[2].as<int>());
}

std::tuple<int, int, int> ClientConfig::getLoriColourKey() {
    YAML::Node loriColourKeyNode = getInstance()->root["LORI_COLOUR_KEY"];
    return std::make_tuple(loriColourKeyNode[0].as<int>(), loriColourKeyNode[1].as<int>(), loriColourKeyNode[2].as<int>());
}

std::tuple<int, int, int> ClientConfig::getTurtleColourKey() {
    YAML::Node turtleColourKeyNode = getInstance()->root["TURTLE_COLOUR_KEY"];
    return std::make_tuple(turtleColourKeyNode[0].as<int>(), turtleColourKeyNode[1].as<int>(), turtleColourKeyNode[2].as<int>());
}

std::tuple<int, int, int> ClientConfig::getSFXColourKey() {
    YAML::Node sfxColourKeyNode = getInstance()->root["SFX_COLOUR_KEY"];
    return std::make_tuple(sfxColourKeyNode[0].as<int>(), sfxColourKeyNode[1].as<int>(), sfxColourKeyNode[2].as<int>());
}

std::tuple<int, int, int> ClientConfig::getItemsColourKey() {
    YAML::Node itemsColourKeyNode = getInstance()->root["ITEMS_COLOUR_KEY"];
    return std::make_tuple(itemsColourKeyNode[0].as<int>(), itemsColourKeyNode[1].as<int>(), itemsColourKeyNode[2].as<int>());
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

// Sprites
std::vector<std::vector<std::pair<int, int>>> ClientConfig::getJazzSelectNameSprites() {
    YAML::Node jazzSelectNameSpritesNode = getInstance()->root["JAZZ_SELECT_NAME_SPRITES"];
    std::vector<std::vector<std::pair<int, int>>> jazzSelectNameSprites;
    for (YAML::const_iterator it = jazzSelectNameSpritesNode.begin(); it != jazzSelectNameSpritesNode.end(); ++it) {
        std::vector<std::pair<int, int>> jazzSelectNameSprite;
        for (YAML::const_iterator it2 = it->begin(); it2 != it->end(); ++it2) {
            jazzSelectNameSprite.push_back(it2->as<std::pair<int, int>>());
        }
        jazzSelectNameSprites.push_back(jazzSelectNameSprite);
    }
    return jazzSelectNameSprites;
}

std::vector<std::vector<std::pair<int, int>>> ClientConfig::getJazzSelectSprites() {
    YAML::Node jazzSelectSpritesNode = getInstance()->root["JAZZ_SELECT_SPRITES"];
    std::vector<std::vector<std::pair<int, int>>> jazzSelectSprites;
    for (YAML::const_iterator it = jazzSelectSpritesNode.begin(); it != jazzSelectSpritesNode.end(); ++it) {
        std::vector<std::pair<int, int>> jazzSelectSprite;
        for (YAML::const_iterator it2 = it->begin(); it2 != it->end(); ++it2) {
            jazzSelectSprite.push_back(it2->as<std::pair<int, int>>());
        }
        jazzSelectSprites.push_back(jazzSelectSprite);
    }
    return jazzSelectSprites;
}

std::vector<std::vector<std::pair<int, int>>> ClientConfig::getSpazSelectNameSprites() {
    YAML::Node spazSelectNameSpritesNode = getInstance()->root["SPAZ_SELECT_NAME_SPRITES"];
    std::vector<std::vector<std::pair<int, int>>> spazSelectNameSprites;
    for (YAML::const_iterator it = spazSelectNameSpritesNode.begin(); it != spazSelectNameSpritesNode.end(); ++it) {
        std::vector<std::pair<int, int>> spazSelectNameSprite;
        for (YAML::const_iterator it2 = it->begin(); it2 != it->end(); ++it2) {
            spazSelectNameSprite.push_back(it2->as<std::pair<int, int>>());
        }
        spazSelectNameSprites.push_back(spazSelectNameSprite);
    }
    return spazSelectNameSprites;
}

std::vector<std::vector<std::pair<int, int>>> ClientConfig::getSpazSelectSprites() {
    YAML::Node spazSelectSpritesNode = getInstance()->root["SPAZ_SELECT_SPRITES"];
    std::vector<std::vector<std::pair<int, int>>> spazSelectSprites;
    for (YAML::const_iterator it = spazSelectSpritesNode.begin(); it != spazSelectSpritesNode.end(); ++it) {
        std::vector<std::pair<int, int>> spazSelectSprite;
        for (YAML::const_iterator it2 = it->begin(); it2 != it->end(); ++it2) {
            spazSelectSprite.push_back(it2->as<std::pair<int, int>>());
        }
        spazSelectSprites.push_back(spazSelectSprite);
    }
    return spazSelectSprites;
}

std::vector<std::vector<std::pair<int, int>>> ClientConfig::getLoriSelectNameSprites() {
    YAML::Node loriSelectNameSpritesNode = getInstance()->root["LORI_SELECT_NAME_SPRITES"];
    std::vector<std::vector<std::pair<int, int>>> loriSelectNameSprites;
    for (YAML::const_iterator it = loriSelectNameSpritesNode.begin(); it != loriSelectNameSpritesNode.end(); ++it) {
        std::vector<std::pair<int, int>> loriSelectNameSprite;
        for (YAML::const_iterator it2 = it->begin(); it2 != it->end(); ++it2) {
            loriSelectNameSprite.push_back(it2->as<std::pair<int, int>>());
        }
        loriSelectNameSprites.push_back(loriSelectNameSprite);
    }
    return loriSelectNameSprites;
}

std::vector<std::vector<std::pair<int, int>>> ClientConfig::getLoriSelectSprites() {
    YAML::Node loriSelectSpritesNode = getInstance()->root["LORI_SELECT_SPRITES"];
    std::vector<std::vector<std::pair<int, int>>> loriSelectSprites;
    for (YAML::const_iterator it = loriSelectSpritesNode.begin(); it != loriSelectSpritesNode.end(); ++it) {
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
