#include <exception>
#include <iostream>
#include <sstream>

#include "Common/logger.h"
#include "Common/Config/ClientConfig.h"

#define SUCCESS 0
#define FAIL -1
#define CLIENT_ARGS 3

int main(int argc, char* argv) {
    Logger logger(ClientConfig::getLogFile());
    if (argc != CLIENT_ARGS) {
        logger.error(__func__, __LINE__, "Invalid number of arguments. Expected: %d, got: %d",
                     CLIENT_ARGS, argc);
        return FAIL;
    }
    try {
        // Init Client con Logger.
    } catch (const std::exception& e) {
        logger.error(__func__, __LINE__, "Exception caught: %s", e.what());
        return FAIL;
    }
    return SUCCESS;
}
