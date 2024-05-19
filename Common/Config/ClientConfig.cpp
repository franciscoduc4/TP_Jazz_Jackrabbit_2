#include "ClientConfig.h"

const static std::string YAML_FILE_PATH = "config/client.yaml";

ClientConfig* ClientConfig::instance = nullptr;

ClientConfig::ClientConfig() {
    this->root = YAML::LoadFile(YAML_FILE_PATH);
}

ClientConfig* ClientConfig::getInstance() {
    if (instance == nullptr) {
        instance = new ClientConfig();
    }
    return instance;
}

std::string ClientConfig::getLogFile() {
    return getInstance()->root["LOG_FILE"].as<std::string>();
}

void ClientConfig::deleteInstance() {
    if (instance != nullptr) {
        delete instance;
        instance = nullptr;
    }
}
