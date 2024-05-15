// server_server.h
#ifndef SERVER_SERVER_H_
#define SERVER_SERVER_H_

#include <vector>
#include <mutex>
#include <chrono>
#include <memory>
#include <string>

class Server {
    private:
        std::string& servname;

    public:
        explicit Server(std::string& servname);
        void run();
        void shutdown();

        Server(const Server&) = delete;
        Server& operator=(const Server&) = delete;
};

#endif // SERVER_SERVER_H_
