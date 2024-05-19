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

#include "Game/gameMonitor.h"
#include "Threads/acceptorThread.h"

class Server {
private:
    std::string& servname;
    GameMonitor gameMonitor;

public:
    explicit Server(std::string& servname);
    void run();
    void shutdown();

    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;
};

#endif  // SERVER_SERVER_H_
