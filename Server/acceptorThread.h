#ifndef SERVER_CLIENT_ACCEPTOR_H_
#define SERVER_CLIENT_ACCEPTOR_H_

#include <atomic>
#include <string>
#include <vector>

#include "../Common/queue.h"
#include "../Common/socket.h"
#include "../Common/thread.h"

#include "gamesMonitor.h"
#include "playerHandler.h"

class ClientAcceptor: public Thread {
private:
    Socket serverSocket;
    GamesMonitor& gamesMonitor;
    std::atomic<bool> isAlive{true};
    std::vector<std::unique_ptr<PlayerHandler>> playerHandlers;

public:
    explicit ClientAcceptor(const std::string& servname, GamesMonitor& gamesMonitor);

    virtual void run() override;
    virtual void stop() override;
    void cleanUpInactiveHandlers();
    void cleanUpAllHandlers();
};

#endif  // SERVER_CLIENT_ACCEPTOR_H_
