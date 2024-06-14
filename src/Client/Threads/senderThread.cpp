#include "senderThread.h"

#include <iostream>
#include <vector>

#include <arpa/inet.h>

SenderThread::SenderThread(std::shared_ptr<Queue<std::unique_ptr<DTO>>>& queue,
                           std::shared_ptr<Socket>& socket, std::atomic<bool>& was_closed):
        queue(queue), socket(socket), was_closed(was_closed), closed(false) {}

void SenderThread::sendCommandDTO(const CommandDTO& cmd) {
    Command command = cmd.getCommand();
    std::cout << "[CLIENT SENDER] Getting command" << std::endl;
    this->socket->sendall(&command, sizeof(char), &this->closed);
    std::cout << "[CLIENT SENDER] Sent command" << std::endl;

    switch (command) {
        case Command::CREATE_GAME:
            this->sendCreateGame(cmd);
            break;
        case Command::MAPS_LIST:
            std::cout << "[CLIENT SENDER] MAPS_LIST command" << std::endl;
            break;
        case Command::JOIN_GAME:
            std::cout << "[CLIENT SENDER] JOIN_GAME command" << std::endl;
            break;
        case Command::GAMES_LIST:
            std::cout << "[CLIENT SENDER] GAMES_LIST command" << std::endl;
            break;
        case Command::START_GAME:
            this->sendStartGame(cmd);
            break;
        default:
            std::cout << "[CLIENT SENDER] Unknown command: " << (int)command << std::endl;
            break;
    }
    if (this->was_closed.load()) {
        std::cout << "[CLIENT SENDER] Socket was closed, exiting sendCommandDTO" << std::endl;
        return;
    }
}

void SenderThread::sendCreateGame(const CommandDTO& cmd) {
    auto createGame = dynamic_cast<const CreateGameDTO&>(cmd);
    uint32_t mapId = createGame.getMapId();
    uint8_t maxPlayers = createGame.getMaxPlayers();
    CharacterType character = createGame.getCharacterType();
    std::string gameName = createGame.getGameName();

    mapId = htonl(mapId);

    this->socket->sendall(&mapId, sizeof(uint32_t), &this->closed);
    std::cout << "[CLIENT SENDER] Sent mapId: " << mapId << std::endl;
    this->was_closed.store(this->closed);

    if (this->was_closed.load()) {
        std::cout << "[CLIENT SENDER] Socket was closed after sending mapId" << std::endl;
        return;
    }

    this->socket->sendall(&maxPlayers, sizeof(uint8_t), &this->closed);
    std::cout << "[CLIENT SENDER] Sent maxPlayers: " << (int)maxPlayers << std::endl;
    this->was_closed.store(this->closed);
    if (this->was_closed.load()) {
        std::cout << "[CLIENT SENDER] Socket was closed after sending maxPlayers" << std::endl;
        return;
    }

    this->socket->sendall(&character, sizeof(char), &this->closed);
    std::cout << "[CLIENT SENDER] Sent character: " << (int)character << std::endl;
    this->was_closed.store(this->closed);
    if (this->was_closed.load()) {
        std::cout << "[CLIENT SENDER] Socket was closed after sending character" << std::endl;
        return;
    }

    uint8_t gameNameSize = gameName.size();
    this->socket->sendall(&gameNameSize, sizeof(uint8_t), &this->closed);
    std::cout << "[CLIENT SENDER] Sent gameNameSize: " << (int)gameNameSize << std::endl;

    this->socket->sendall(gameName.c_str(), gameName.size(), &this->closed);
    std::cout << "[CLIENT SENDER] Sent gameName: " << gameName << std::endl;
    this->was_closed.store(this->closed);
    if (this->was_closed.load()) {
        std::cout << "[CLIENT SENDER] Socket was closed after sending gameName" << std::endl;
        return;
    }

    this->was_closed.store(this->closed);
}

void SenderThread::sendStartGame(const CommandDTO& cmd) {
    auto startGame = dynamic_cast<const StartGameDTO&>(cmd);
    uint32_t gameId = startGame.getGameId();
    std::cout << "[CLIENT SENDER] Getting gameId for start game: " << gameId << std::endl;
    gameId = htonl(gameId);

    this->socket->sendall(&gameId, sizeof(uint32_t), &this->closed);
    std::cout << "[CLIENT SENDER] Sent gameId for start game: " << gameId << std::endl;
    this->was_closed.store(this->closed);
    if (this->was_closed.load()) {
        std::cout << "[CLIENT SENDER] Socket was closed after sending gameId" << std::endl;
    }
}

void SenderThread::sendMovement(const CommandDTO& cmd) {
    Command command = cmd.getCommand();

    this->socket->sendall(&command, sizeof(char), &this->closed);
    std::cout << "[CLIENT SENDER] Sent movement command: " << (int)command << std::endl;
    this->was_closed.store(this->closed);

    if (this->was_closed.load()) {
        std::cout << "[CLIENT SENDER] Socket was closed after sending movement command"
                  << std::endl;
        return;
    }
    std::vector<char> data = cmd.getData();

    this->socket->sendall(data.data(), data.size(), &this->closed);
    std::cout << "[CLIENT SENDER] Sent movement data" << std::endl;
    this->was_closed.store(this->closed);
    if (this->was_closed.load()) {
        std::cout << "[CLIENT SENDER] Socket was closed after sending movement data" << std::endl;
    }
}

void SenderThread::run() {
    try {
        while (_keep_running) {
            std::unique_ptr<DTO> msg = queue->pop();
            std::cout << "[CLIENT SENDER] Popping message from queue" << std::endl;
            DTOType type = msg->getType();
            std::cout << "[CLIENT SENDER] Got message type: " << (int)type << std::endl;
            switch (type) {
                case DTOType::COMMAND_DTO: {
                    CommandDTO* cmd = dynamic_cast<CommandDTO*>(msg.get());
                    this->sendCommandDTO(*cmd);
                    break;
                }
                case DTOType::GAME_DTO: {
                    CommandDTO* cmd = dynamic_cast<CommandDTO*>(msg.get());
                    this->sendCommandDTO(static_cast<CommandDTO&>(*cmd));
                    break;
                }
                default:
                    std::cout << "[CLIENT SENDER] Unknown DTO type: " << (int)type << std::endl;
                    break;
            }

            if (was_closed.load()) {
                std::cout << "[CLIENT SENDER] Socket was closed, stopping sender thread"
                          << std::endl;
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

SenderThread::~SenderThread() {
    std::cout << "[CLIENT SENDER] Destructor called, joining thread" << std::endl;
    this->join();
}
