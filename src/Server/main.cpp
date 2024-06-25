#include <exception>
#include <iostream>
#include <sstream>

#include "../Common/Config/ServerConfig.h"
#include "../Common/logger.h"

#include "server.h"

#define SUCCESS 0
#define FAIL -1
#define SERVER_ARGS 2

int main(int argc, char** argv) {
    if (argc != SERVER_ARGS) {
        std::cerr << "Invalid number of arguments. Expected: " << SERVER_ARGS << ", got: " << argc
                  << std::endl;
        return FAIL;
    }

    try {
        // Load the server configuration

        // Initialize Logger
        // Logger logger(config->getLogFile());

        // Create and run the server
        Server server(argv[1]);
        std::cout << "Server created" << std::endl;
        server.run();
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        ServerConfig::deleteInstance();
        return FAIL;
    }
    ServerConfig::deleteInstance();
    return SUCCESS;
}
