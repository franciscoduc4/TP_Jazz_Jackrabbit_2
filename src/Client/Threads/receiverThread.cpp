#include "./receiverThread.h"

#include <iostream>
#include <memory>
#include <vector>

#include <netinet/in.h>


ReceiverThread::ReceiverThread(Deserializer& deserializer, std::shared_ptr<Socket>& socket,
                               std::atomic<bool>& was_closed):
        deserializer(deserializer), socket(socket), was_closed(was_closed), protocol(socket, was_closed) {
}

void ReceiverThread::receiveDTOByType(const char& dtoTypeChar) {
    std::cout << "[Client Receiver] Received a DTO" << std::endl;
    auto dtoType = static_cast<DTOType>(dtoTypeChar);
    std::unique_ptr<DTO> dto = nullptr;
    switch (dtoType) {
        case DTOType::GAME_DTO: {
            std::cout << "[CLIENT RECEIVER] Receiving game DTO." << std::endl;
            this->protocol.receiveGameDTO(dto);
            if (was_closed.load()) return;
            this->deserializer.deserialize_gameMsg(dto);
            break;
        }
        case DTOType::COMMAND_DTO: {
            std::cout << "[CLIENT RECEIVER] Receiving command DTO." << std::endl;
            this->protocol.receiveCommandDTO(dto);
            if (was_closed.load()) return;
            this->deserializer.deserialize_lobbyMsg(dto);
            break;
        }
        default:
            std::cout << "[CLIENT RECEIVER] Unknown DTO type received." << std::endl;
            break;
    }
}

void ReceiverThread::run() {
    try {
        uint8_t playerId;
        this->protocol.receivePlayerId(playerId);
        this->deserializer.setPlayerId(playerId);

        while (!this->was_closed.load() && _keep_running) {
            std::cout << "[CLIENT RECEIVER] Waiting for DTO type." << std::endl;
            try {
                char dtoTypeChar;
                this->protocol.receiveDTOType(dtoTypeChar);
                if (this->was_closed.load()) {
                    return;
                }
                std::cout << "[CLIENT RECEIVER] Received DTO type: " << static_cast<int>(dtoTypeChar) << std::endl;
                if (!DTOValidator::validateDTOType(dtoTypeChar)) {
                    std::cerr << "[CLIENT RECEIVER] Invalid DTO type received." << std::endl;
                    continue;
                }
                this->receiveDTOByType(dtoTypeChar);
            } catch (const std::exception& e) {
                if (!this->was_closed.load() || _keep_running) {
                    std::cerr << "[CLIENT RECEIVER] ReceiverThread error: " << e.what()
                              << std::endl;
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "[CLIENT RECEIVER] Error in run: " << e.what() << std::endl;
    }
}

void ReceiverThread::stopReceiving() {
    this->protocol.close();
}