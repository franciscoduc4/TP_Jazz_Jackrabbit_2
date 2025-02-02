#include "senderThread.h"

SenderThread::SenderThread(std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>>& queue,
                           std::shared_ptr<Socket>& socket, std::atomic<bool>& was_closed):
        queue(queue),
        socket(socket),
        was_closed(was_closed),
        closed(false),
        additionalData(std::unordered_map<char, bool>()) {
    this->additionalData[static_cast<char>(Command::IDLE)] = false;
    this->additionalData[static_cast<char>(Command::CREATE_GAME)] = true;
    this->additionalData[static_cast<char>(Command::JOIN_GAME)] = true;
    this->additionalData[static_cast<char>(Command::GAMES_LIST)] = false;
    this->additionalData[static_cast<char>(Command::MAPS_LIST)] = false;
    this->additionalData[static_cast<char>(Command::GAME_MODE)] = false;
    this->additionalData[static_cast<char>(Command::CHARACTER_TYPE)] = false;
    this->additionalData[static_cast<char>(Command::START_GAME)] = true;
    this->additionalData[static_cast<char>(Command::SHOOT)] = true;
    this->additionalData[static_cast<char>(Command::SWITCH_WEAPON)] = true;
    this->additionalData[static_cast<char>(Command::MOVE)] = true;
    this->additionalData[static_cast<char>(Command::SPRINT)] = false;  
    this->additionalData[static_cast<char>(Command::JUMP)] = true;
    this->additionalData[static_cast<char>(Command::INTOXICATED)] = false;
    this->additionalData[static_cast<char>(Command::TAKE_DAMAGE)] = false;
    this->additionalData[static_cast<char>(Command::DEATH)] = false;
    this->additionalData[static_cast<char>(Command::REVIVE)] = false;
    this->additionalData[static_cast<char>(Command::HEAL)] = false;
    this->additionalData[static_cast<char>(Command::UPPERCUT)] = true;
    this->additionalData[static_cast<char>(Command::SHORT_KICK)] = true;
    this->additionalData[static_cast<char>(Command::SIDE_KICK)] = true;
    this->additionalData[static_cast<char>(Command::CHEAT)] = true;
    this->additionalData[static_cast<char>(Command::SPECIAL_ATTACK)] = true;
    this->additionalData[static_cast<char>(Command::INVALID)] = false;
}

void SenderThread::sendCommandDTO(const CommandDTO& cmd) {
    Command command = cmd.getCommand();
    std::cout << "[CLIENT SENDER] Getting command" << std::endl;
    this->socket->sendall(&command, sizeof(char), &this->closed);
    std::cout << "[CLIENT SENDER] Sent command" << std::endl;
    std::cout << "EL VALOR DE COMMAND ES " << static_cast<int>(command) << '\n';
    this->was_closed.store(closed);
    if (this->was_closed.load()) {
        std::cout << "[CLIENT SENDER] Socket was closed, exiting sendCommandDTO" << std::endl;
        return;
    }
    if (this->additionalData[static_cast<char>(command)]) {
        this->sendAditionalData(cmd);
    }
}

void SenderThread::sendAditionalData(const CommandDTO& cmd) {
    std::vector<char> data = cmd.getData();
    if (data.empty()) {
        return;
    }
    std::cout << "[CLIENT SENDER] Sending additional data: " << data.size() << " bytes"
              << std::endl;
    this->socket->sendall(data.data(), data.size(), &this->closed);
    std::cout << "[CLIENT SENDER] Sent additional data" << std::endl;
    this->was_closed.store(this->closed);
    if (this->was_closed.load()) {
        std::cout << "[CLIENT SENDER] Socket was closed after sending movement data" << std::endl;
    }
}

void SenderThread::run() {
    try {
        while (_keep_running) {
            std::unique_ptr<CommandDTO> msg = queue->pop();

            auto* cmd = dynamic_cast<CommandDTO*>(msg.get());
            this->sendCommandDTO(*cmd);

            if (this->was_closed.load()) {
                stop();
            }
        }
    } catch (const std::exception& e) {
        if (_keep_running) {
            std::cerr << "Error occurred: " << e.what() << '\n';
            stop();
        }
    }
}
