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

void ServerConfig::deleteInstance() {
    if (instance != nullptr) {
        delete instance;
        instance = nullptr;
    }
}
