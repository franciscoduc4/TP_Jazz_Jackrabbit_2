#ifndef PLAYER_H_
#define PLAYER_H_

#include <atomic>
#include <memory>
#include <string>
#include <utility>

#include "../Physics/character.h"
#include "../../Common/Models/gameTypes.h"
#include "../../Common/protocol.h"
#include "../../Common/queue.h"
#include "../../Common/socket.h"
#include "../Threads/receiverThread.h"
#include "../Threads/senderThread.h"

class Player {
private:
    Protocol protocol;
    int id;
    std::string gameName;
    std::string name;
    bool inGame;
    std::unique_ptr<ReceiverThread> receiver;
    std::unique_ptr<SenderThread> sender;
    std::unique_ptr<Character> character;

public:
    explicit Player(Protocol&& protocol);
    std::string getGameName() const;
    std::string getName() const;
    int getId() const;
    void setInGame();
    void setCharacter(std::unique_ptr<Character>&& character);
    std::unique_ptr<Character> getCharacter();

    std::unique_ptr<SenderThread> initSender(std::shared_ptr<Queue<std::string>> eventQueue);
    std::unique_ptr<ReceiverThread> initReceiver(
            std::shared_ptr<Queue<GameTypes::Action>> gameQueue);
};

#endif  // PLAYER_H_
