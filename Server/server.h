// server_server.h
#ifndef SERVER_SERVER_H_
#define SERVER_SERVER_H_

#include <chrono>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

class Server {
private:
    std::string& servname;
    GamesMonitor gamesMonitor;

public:
    explicit Server(std::string& servname);
    void run();
    void shutdown();

    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;
};

#endif  // SERVER_SERVER_H_
