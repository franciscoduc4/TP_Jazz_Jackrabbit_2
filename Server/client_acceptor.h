#ifndef SERVER_CLIENT_ACCEPTOR_H_
#define SERVER_CLIENT_ACCEPTOR_H_

#include "../Common/thread.h"
#include "../Common/queue.h"
#include "../Common/socket.h"
#include "player_handler.h"
#include "memory"
#include <vector>
#include <string>
#include <atomic>

class ClientAcceptor: public Thread {
    private:
        Socket serverSocket;
        std::atomic<bool> isAlive{true};
        std::vector<std::unique_ptr<PlayerHandler>> playerHandlers;
        
    public:
        explicit ClientAcceptor(std::string& servname);

        virtual void run() override;
        virtual void stop() override;
        void cleanUpInactiveHandlers();
        void cleanUpAllHandlers();

};


#endif // SERVER_CLIENT_ACCEPTOR_H_
