#include "./client.h"

#include "../Common/DTO/gameCommand.h"
#include "../Common/Types/direction.h"
#include "./SDL/gamescreen.h"

Client::Client(char* ip, char* port):
        ip(ip),
        port(port),
        skt(std::make_shared<Socket>(ip, port)),
        was_closed(false),
        senderQueue(std::make_shared<Queue<std::unique_ptr<CommandDTO>>>()),
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
    std::unique_ptr<DTO> dto = this->gameQueue->pop();
    CommandDTO* commandDTO = dynamic_cast<CommandDTO*>(dto.get());
    this->playerId = commandDTO->getPlayerId();
}

void Client::start() {

    bool clientJoinedGame = false;
    do {
        LobbyInit init;
        std::pair<bool, LobbyMessage> qtResult = init.launchQT(this->lobbyController,
        (bool&)clientJoinedGame); clientJoinedGame = qtResult.first; if (!clientJoinedGame) {
              return;
        }
        // TODO: Continue with SDL.
        // START - TESTING SKIP QT

        /*Command cmd = (this->playerId == 0) ? Command::CREATE_GAME : Command::JOIN_GAME;

        LobbyMessage msg;
        msg.setCharacter(CharacterType::JAZZ);
        msg.setMap(0);
        msg.setGameName("Dummy");
        msg.setLobbyCmd(cmd);
        msg.setMaxPlayers(1);
        msg.setPlayerName("Test");
        if (cmd == Command::JOIN_GAME) {
            msg.setGameId(0);
        }
        clientJoinedGame = true;

        this->lobbyController.sendRequest(msg);
        std::cout << "Request sent." << std::endl;
        std::pair<bool, GameInfo> response = this->lobbyController.recvResponse();
        bool responseReceived = response.first;
        GameInfo gameInfo = response.second;
        std::cout << "Response received: " << responseReceived << std::endl;

        std::pair<bool, GameInfo> sResponse = this->lobbyController.recvResponse();
        bool sResponseReceived = sResponse.first;
        GameInfo sGameInfo = sResponse.second;

        LobbyMessage msg2;
        msg2.setLobbyCmd(Command::START_GAME);
        msg2.setGameId(0);
        if (responseReceived && sResponseReceived) {
            this->lobbyController.startGame(msg2);
            bool gameStartAck = this->lobbyController.recvStartGame();
            std::cout << "Game start ack: " << gameStartAck << std::endl;
            if (!gameStartAck) {
                std::cerr << "Failed to start game." << std::endl;
                return;
            }
        } else {
            std::cerr << "Failed to receive response for create game." << std::endl;
            return;
        }*/

        // END - TESTING SKIP QT
        //CharacterType pj = qtResult.second.getCharacter();
        //uint8_t mapId = qtResult.second.getMap();
        }

        // // END - TESTING SKIP QT
        // CharacterType pj = qtResult.second.getCharacter();
        // uint8_t mapId = qtResult.second.getMap();
        GameScreen game(this->gameController, this->playerId, 0);
        std::map<uint8_t, int> scores = game.run();
        FinalStats stats(scores);
        init.displayStats(qtResult.second, stats, (bool&)clientJoinedGame, this->playerId);
    } while (clientJoinedGame);

    this->finish();
}


void Client::finish() {
    // Close Queues
    this->lobbyQueue->close();
    this->gameQueue->close();
    this->senderQueue->close();
    // Close Socket
    this->receiver.stopReceiving();
    // Stop Threads
    this->sender.stop();
    this->receiver.stop();
    // Join Threads
    this->sender.join();
    this->receiver.join();
}
