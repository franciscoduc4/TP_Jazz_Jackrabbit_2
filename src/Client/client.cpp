#include "./client.h"

Client::Client(char* ip, char* port):
        ip(ip),
        port(port),
        skt(std::make_shared<Socket>(ip, port)),
        was_closed(false),
        senderQueue(std::make_shared<Queue<std::unique_ptr<DTO>>>()),
        lobbyQueue(std::make_shared<Queue<std::unique_ptr<DTO>>>()),
        gameQueue(std::make_shared<Queue<std::unique_ptr<DTO>>>()),
        sender(this->senderQueue, this->skt, this->was_closed),
        serializer(this->senderQueue),
        deserializer(this->lobbyQueue, this->gameQueue),
        receiver(this->deserializer, this->skt, this->was_closed),
        lobbyController(this->serializer, this->deserializer, this->lobbyQueue),
        gameController(this->serializer, this->deserializer, this->gameQueue) {
    this->sender.start();
    this->receiver.start();
}

void Client::start() {
    bool clientJoinedGame = false;
    do {
        LobbyInit init;
        clientJoinedGame = init.launchQT(this->lobbyController, (bool&) clientJoinedGame);

        if (!clientJoinedGame) {
            break;
        }

        // TODO: Continue with SDL.
        
        GameScreen game(0);
        game.run();

    } while (clientJoinedGame);
}

// std::unique_ptr<DTO> Client::getServerMsg() { return receiverQueue->pop(); }

/*
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



std::map<int32_t, GameInfo> Client::requestGameList(const LobbyMessage& msg) {
    std::map<int32_t, GameInfo> gameMap;
    this->serializer.serializeLobbyMessage(msg);
    try {
        std::pair<int, std::map<int32_t, GameInfo>> result = this->deserializer.getGameList();
        if (result.first > 0) {
            gameMap = result.second;
        }
    } catch (const std::exception &e) {
        std::cerr << "Unexpected Exception retrieving GameList" << e.what() << std::endl;
    }

    return gameMap;
}

*/