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
        playerCmdsQueue(std::make_shared<Queue<std::unique_ptr<DTO>>>()),
        receiverQueue(std::make_shared<Queue<std::unique_ptr<DTO>>>()),
        sender(this->senderQueue, this->skt, this->was_closed),
        serializer(this->senderQueue),
        // cmdReader(this->serializer, this->playerCmdsQueue),
        deserializer(this->receiverQueue),
        receiver(this->deserializer, this->skt, this->was_closed),
        playerId(0) {
    this->sender.start();
    this->receiver.start();
    // this->cmdReader.start();
}

void Client::start() {
	/*
    bool clientJoinedGame = false;
    LobbyInit init;
    clientJoinedGame = init.launchQT(*this, (bool&) clientJoinedGame);

    if (!clientJoinedGame) {
        return;
    }
	*/
    // TODO: Continue with SDL.
    
    GameScreen game(*this);
    game.run();


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
    }
}

void Client::move_msg(std::vector<uint8_t>& parameters) {
    Direction dir = static_cast<Direction>(parameters[0]);
    std::unique_ptr<DTO> move = std::make_unique<MoveDTO>(this->playerId, dir);
    serializer.sendMsg(move);
}

