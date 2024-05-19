#ifndef PLAYER_H_
#define PLAYER_H_

#include <atomic>
#include <memory>
#include <string>
#include <utility>

#include "../../Common/gameTypes.h"
#include "../../Common/protocol.h"
#include "../../Common/queue.h"
#include "../../Common/socket.h"
#include "../Threads/receiverThread.h"
#include "../Threads/senderThread.h"
#include "character.h"

class Player {
private:
    Protocol protocol;
    int id;
        std::string gameName;
        std::string name;
        bool inGame;
        std::shared_ptr<ReceiverThread> receiver;
        std::shared_ptr<SenderThread> sender;
        std::shared_ptr<Character> character; 

    public:
        explicit Player(Protocol&& protocol);
        std::string getGameName() const;
        std::string getName() const;
        int getId() const;
        void setInGame();
        void setCharacter(std::shared_ptr<Character> character);
        std::shared_ptr<Character> getCharacter() const;

    std::shared_ptr<SenderThread> initSender(std::shared_ptr<Queue<std::string>> eventQueue);
    std::shared_ptr<ReceiverThread> initReceiver(Queue<GameTypes::Action>& gameQueue);
};

#endif  // PLAYER_H_
