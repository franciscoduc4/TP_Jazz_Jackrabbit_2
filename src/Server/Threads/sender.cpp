#include "sender.h"

#include <iostream>
#include <memory>

SenderThread::SenderThread(const std::shared_ptr<Socket>& socket, std::atomic<bool>& keepPlaying,
                           std::atomic<bool>& inGame, uint8_t playerId,
                           const std::shared_ptr<Queue<std::unique_ptr<DTO>>>& sendQueue) :
        socket(socket),
        keepPlaying(keepPlaying),
        inGame(inGame),
        playerId(playerId),
        sendQueue(sendQueue),
        serializer(socket, keepPlaying, inGame),
        deserializer(socket, keepPlaying, inGame) {}

void SenderThread::run() {
    std::cout << "[SERVER SENDER] Sender started" << std::endl;
    serializer.sendId(playerId);

    while (keepPlaying.load()) {
        std::cout << "[SERVER SENDER] Running lobby" << std::endl;
        runLobby();
        while (inGame.load()) {
            try {
                std::unique_ptr<DTO> dto = sendQueue->pop();
                std::cout << "[SERVER SENDER] DTO popped from sendQueue" << std::endl;
                auto gameDTO = dynamic_cast<GameDTO*>(dto.get());
                dto.release();
                std::cout << "[SERVER SENDER] Sending gameDTO" << std::endl;
                serializer.sendGameDTO(std::unique_ptr<GameDTO>(gameDTO));
            } catch (const std::exception& e) {
                std::cerr << "[SERVER SENDER] Exception in game: " << e.what() << std::endl;
                if (!inGame.load() || !keepPlaying.load()){
                    std::cout << "[SERVER SENDER] Socket was closed, exiting game" << std::endl;
                    return;
                }
            }
        }
    }
    std::cout << "[SERVER SENDER] Exiting run" << std::endl;
}

void SenderThread::runLobby() {
    while (keepPlaying.load() && !inGame.load()) {
        try {
            std::unique_ptr<DTO> dtoToSend = sendQueue->pop();
            auto* commandDTO = dynamic_cast<CommandDTO*>(dtoToSend.get());
            dtoToSend.release();
            std::cout << "[SERVER SENDER LOBBY] Sending DTO" << std::endl;
            serializer.sendCommand(std::unique_ptr<CommandDTO>(commandDTO));
            std::cout << "[SERVER SENDER LOBBY] DTO sent" << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "[SERVER SENDER LOBBY] Exception: " << e.what() << std::endl;
            if (!keepPlaying.load()) {
                std::cout << "[SERVER SENDER LOBBY] Socket was closed, exiting lobby" << std::endl;
                return;
            }
        }
    }
    std::cout << "[SERVER SENDER LOBBY] Out of lobby" << std::endl;
}
