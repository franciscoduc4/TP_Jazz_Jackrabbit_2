#ifndef SERVER_PLAYER_HANDLER_H_
#define SERVER_PLAYER_HANDLER_H_

#include <atomic>
#include <memory>
#include <string>

#include "../Common/gameTypes.h"
#include "../Common/protocol.h"
#include "../Common/queue.h"
#include "../Common/socket.h"

#include "receiverThread.h"
#include "senderThread.h"

class Player {
private:
    Socket socket;
    int id;
    Protocol protocol;
    std::string name;
    std::string gameName;
    bool inGame;
    std::shared_ptr<ReceiverThread> receiver;
    std::shared_ptr<SenderThread> sender;


public:
    explicit Player(Socket&& playerSocket);

    std::string getGameName() const;
    std::string getName() const;
    int getId() const;
    void setInGame();
    Socket& getSocketRef();

    std::shared_ptr<SenderThread> initSender(std::shared_ptr<Queue<GameTypes::Event>> eventQueue);
    std::shared_ptr<ReceiverThread> initReceiver(Queue<GameTypes::Action>& gameQueue);
};

#endif  // SERVER_PLAYER_HANDLER_H_
