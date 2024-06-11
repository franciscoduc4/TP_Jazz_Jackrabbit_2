#include "./client.h"
#include "./SDL/gamescreen.h"
#include "../Common/Types/direction.h"
#include "../Common/DTO/move.h"

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
        gameController(this->serializer, this->deserializer, this->gameQueue),
        playerId(-1) {
    this->sender.start();
    this->receiver.start();
}

void Client::start() {
    /*
    bool clientJoinedGame = false;
    do {
        LobbyInit init;
        clientJoinedGame = init.launchQT(this->lobbyController, (bool&) clientJoinedGame);

      if (!clientJoinedGame) {
          return;
      }
      // TODO: Continue with SDL.

      GameScreen game(*this);
      // GameScreen game(this->gameController);
      game.run();
    } while (clientJoinedGame);
    */
    GameScreen game(this->gameController);
    game.run();
}
