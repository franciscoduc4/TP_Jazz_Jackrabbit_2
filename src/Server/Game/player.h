#ifndef PLAYER_H_
#define PLAYER_H_

#include <atomic>
#include <memory>
#include <string>
#include <utility>

#include "../../Common/Models/gameTypes.h"
#include "../../Common/queue.h"
#include "../../Common/socket.h"
#include "../Game/gameMonitor.h"
#include "../Physics/character.h"
#include "../Threads/receiver.h"
#include "../Threads/sender.h"

class Player {
private:
<<<<<<< Updated upstream
    uint8_t id;
    std::shared_ptr<Socket> socket;
    std::atomic<bool> inGame{false};
    std::atomic<bool> keepPlaying{true};
    SenderThread sender;
=======
    //Protocol protocol;
    Socket& socket;
    int32_t id;
    std::string gameName;
    std::string name;
    std::unique_ptr<Character> character;
    bool inGame;
    //std::unique_ptr<ReceiverThread> receiver;
    std::unique_ptr<SenderThread> sender;
>>>>>>> Stashed changes

public:
    explicit Player(std::shared_ptr<Socket> socket, GameMonitor& gameMonitor, uint8_t id);
    void disconnect();
    bool isPlaying() const;
};

#endif  // PLAYER_H_
