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
        clientJoinedGame = init.launchQT(this->lobbyController, (bool&)clientJoinedGame);

        //   if (!clientJoinedGame) {
        //       return;
        //   }
        // TODO: Continue with SDL.
        // START - TESTING SKIP QT

        /*
        Command cmd = (this->playerId == 0) ? Command::CREATE_GAME : Command::JOIN_GAME;

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
        bool responseReceived = this->lobbyController.recvResponse();
        std::cout << "Response received: " << responseReceived << std::endl;
        LobbyMessage msg2;
        msg2.setLobbyCmd(Command::START_GAME);
        msg2.setGameId(0);
        if (responseReceived) {
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
        }
        // END - TESTING SKIP QT
        */
        GameScreen game(this->gameController, this->playerId);
        game.run();
    } while (clientJoinedGame);
}
