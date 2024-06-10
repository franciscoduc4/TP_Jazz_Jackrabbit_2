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

}

std::unique_ptr<DTO> Client::getServerMsg() { 
	std::unique_ptr<DTO> dto;
	receiverQueue->try_pop(dto);
	return dto; 
}

void Client::sendMsg(Command& cmd, std::vector<uint8_t>& parameters) {
    switch (cmd) {
        case Command::MOVE:
            move_msg(parameters);
       		break;
       	case Command::SHOOT:
       		shoot_msg();
       		break;
    }
}

void Client::move_msg(std::vector<uint8_t>& parameters) {
    Direction dir = static_cast<Direction>(parameters[0]);
    std::unique_ptr<DTO> move = std::make_unique<MoveDTO>(this->playerId, dir);
    serializer.sendMsg(move);
}

/*
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

void Client::shoot_msg() {
	std::unique_ptr<DTO> shoot = std::make_unique<CommandDTO>(this->playerId, Command::SHOOT);
	serializer.sendMsg(shoot);
}
