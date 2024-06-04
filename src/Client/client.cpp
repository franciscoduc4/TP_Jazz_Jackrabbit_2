#include "./client.h"


Client::Client(char* ip, char* port) :
        ip(ip),
        port(port),
        skt(std::make_shared<Socket>(ip, port)),
        was_closed(false),
        senderQueue(std::make_shared<Queue<DTO>>()),
        playerCmdsQueue(std::make_shared<Queue<DTO>>()),
        receiverQueue(std::make_shared<Queue<DTO>>()),
        sender(this->skt, this->senderQueue, this->was_closed),
        serializer(this->sender),
        cmdReader(this->serializer, this->playerCmdsQueue),
        deserializer(),
        receiver(this->skt, this->deserializer){
    this->sender.start();
    this->receiver.start();
    this->cmdReader.start();
}

void Client::start() {
    bool clientJoinedGame = false;
    do {
        LobbyInit init;
        clientJoinedGame = init.launchQT(this);

        if (!clientJoinedGame) {
            break;
        }

        // TODO: Continue with SDL.
        GameScreen game(this);
        game.run();

    } while (clientJoinedGame);
}

DTO Client::getServerMsg() {
    return receiverQueue.pop();
}

void Client::sendMsg(Command& cmd, std::vector<uint8_t>& parameters) {
    switch (cmd) {
        case Command::MOVE:
            move_msg(parameters);
    }
}

void Client::move_msg(std::vector<uint8_t>& parameters) {
    Direction dir = static_cast<int32_t>(parameters[0]);
    MoveDTO move(this->playerId, dir);
    serializer.sendMsg(move);
}
