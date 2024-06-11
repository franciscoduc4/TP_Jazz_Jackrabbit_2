#include "senderThread.h"

SenderThread::SenderThread(std::shared_ptr<Queue<std::unique_ptr<DTO>>>& queue, std::shared_ptr<Socket>& socket, std::atomic<bool>& was_closed):
    queue(queue),
    socket(socket),
    was_closed(was_closed),
    closed(false){}

void SenderThread::sendCommandDTO(const CommandDTO& cmd) {
    Command command = cmd.getCommand();
    this->socket->sendall(&command, sizeof(char), &this->closed);
    this->was_closed.store(this->closed);
    if (this->was_closed.load()) { return; }
    if (command != Command::GAMES_LIST) {
        std::vector<char> data = cmd.getData();
        this->socket->sendall(data.data(), data.size(), &this->closed);
        this->was_closed.store(this->closed);
    }
}

void SenderThread::sendMovement(const CommandDTO& cmd) {
    Command command = cmd.getCommand();
    this->socket->sendall(&command, sizeof(char), &this->closed);
    this->was_closed.store(this->closed);
    if (this->was_closed.load()) { return; }
    std::vector<char> data = cmd.getData();
    this->socket->sendall(data.data(), data.size(), &this->closed);
    this->was_closed.store(this->closed);
}

void SenderThread::run() {
    try {
        while (_keep_running) {
            std::unique_ptr<DTO> msg = queue->pop();
            DTOType type = msg->getType();
            switch (type) {
                case DTOType::COMMAND_DTO: 
                    {
                        CommandDTO* cmd = dynamic_cast<CommandDTO*>(msg.get());
                        this->sendCommandDTO(*cmd);
                    }
                case DTOType::GAME_DTO:
                    {
                        CommandDTO* cmd = dynamic_cast<CommandDTO*>(msg.get());
                        this->sendCommandDTO(static_cast<CommandDTO>(*cmd));
                    }
            }
            
            if (was_closed) {
                stop();
            }
        }
    } catch (std::exception e) {
        if (_keep_running) {
            std::cerr << "Ocurrio un error: " << e.what() << '\n';
            stop();
        }
    }
}

SenderThread::~SenderThread() {
    this->join();
}
