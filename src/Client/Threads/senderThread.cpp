#include "senderThread.h"

SenderThread::SenderThread(std::shared_ptr<Queue<std::unique_ptr<DTO>>>& queue, std::shared_ptr<Socket>& socket, std::atomic<bool>& was_closed):
    queue(queue),
    socket(socket),
    was_closed(was_closed),
    closed(false){}


// void SenderThread::sendCommandDTO(const CommandDTO& cmd) {
//     Command command = cmd.getCommand();
//     this->socket->sendall(&command, sizeof(char), &this->closed);
//     this->was_closed.store(this->closed);
//     if (this->was_closed.load()) { return; }
//     if (command != Command::GAMES_LIST && command != Command::START_GAME) {
//         std::vector<char> data = cmd.getData();
//         this->socket->sendall(data.data(), data.size(), &this->closed);
//         this->was_closed.store(this->closed);
//     }
// }

void SenderThread::sendCommandDTO(const CommandDTO& cmd) {
    Command command = cmd.getCommand();
    std::cout << "[SENDER] getting command" << std::endl;
    this->socket->sendall(&command, sizeof(char), &this->closed);
    std::cout << "[SENDER] sent command" << std::endl;

    switch (command) {
        case Command::CREATE_GAME:
            this->sendCreateGame(cmd);
            break;
        case Command::MAPS_LIST:
            break;
        case Command::JOIN_GAME:
            break;
        case Command::GAMES_LIST:
            break;
        case Command::START_GAME:
            break;
        default:
            break;
    }
    if (this->was_closed.load()) { return; }
}

void SenderThread::sendCreateGame(const CommandDTO& cmd) {
    auto createGame = dynamic_cast<const CreateGameDTO&>(cmd);
    uint32_t mapId = createGame.getMapId();
    uint8_t maxPlayers = createGame.getMaxPlayers();
    CharacterType character = createGame.getCharacterType();
    std::string gameName = createGame.getGameName();
    
    mapId = htonl(mapId);
    maxPlayers = htonl(maxPlayers);
    
    this->socket->sendall(&mapId, sizeof(uint32_t), &this->closed);
    std::cout << "[SENDER] sent mapId: " << mapId << std::endl;
    this->was_closed.store(this->closed);
    
    if (this->was_closed.load()) { return; }
    
    this->socket->sendall(&maxPlayers, sizeof(uint8_t), &this->closed);
    std::cout << "[SENDER] sent maxPlayers: " << (int)maxPlayers << std::endl;
    this->was_closed.store(this->closed);
    if (this->was_closed.load()) { return; }
    
    this->socket->sendall(&character, sizeof(char), &this->closed);
    std::cout << "[SENDER] sent character: " << (int)character << std::endl;
    this->was_closed.store(this->closed);
    if (this->was_closed.load()) { return; }
    
    uint8_t gameNameSize = gameName.size();
    this->socket->sendall(&gameNameSize, sizeof(uint8_t), &this->closed);
    std::cout << "[SENDER] sent gameNameSize: " << (int)gameNameSize << std::endl;

    this->socket->sendall(gameName.c_str(), gameName.size(), &this->closed);
    std::cout << "[SENDER] sent gameName: " << gameName << std::endl;
    this->was_closed.store(this->closed);
    if (this->was_closed.load()) { return; }

    this->was_closed.store(this->closed);
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
            std::cout << "[SENDER] popping" << std::endl;
            DTOType type = msg->getType();
            std::cout << "[SENDER] got type: " << (int)type << std::endl;
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
