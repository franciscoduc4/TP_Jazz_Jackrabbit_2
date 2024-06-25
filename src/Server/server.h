// server_server.h

#ifndef SERVER_SERVER_H_
#define SERVER_SERVER_H_

#include <chrono>
#include <iostream>
#include <memory>
#include <mutex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "Threads/acceptor.h"

class Server {
private:
    std::string servname;

public:
    explicit Server(const std::string& servname);
    void run();
    void shutdown();

    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;
};

#endif  // SERVER_SERVER_H_
