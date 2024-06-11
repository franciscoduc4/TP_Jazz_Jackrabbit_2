#include "./receiverThread.h"
#include "../../Common/Types/command.h"

#include <netinet/in.h>

ReceiverThread::ReceiverThread(Deserializer& deserializer, std::shared_ptr<Socket>& socket, std::atomic<bool>& was_closed) :
        deserializer(deserializer),
        socket(socket),
        was_closed(was_closed),
        closed(false) {}

void ReceiverThread::receiveCommandDTO() {
    // Do Something
}

void ReceiverThread::receiveGameDTO() {
    // Do Something
}

void ReceiverThread::receiveGamesList() {
    uint32_t gamesAmount;
    socket->recvall(&gamesAmount, sizeof(uint32_t), &closed);
    this->was_closed.store(closed);
    if (this->was_closed.load()) {
        return;
    }
    uint32_t games = ntohl(gamesAmount);
    std::map<uint32_t, GameInfo> gamesMap;
    for (int i = 0; i < games; i++) {
        uint32_t gameId;
        socket->recvall(&gameId, sizeof(uint32_t), &closed);
        this->was_closed.store(closed);
        if (this->was_closed.load()) {
            return;
        }
        uint32_t id = ntohl(gameId);
        char nameLength;
        socket->recvall(&nameLength, sizeof(char), &closed);
        this->was_closed.store(closed);
        if (this->was_closed.load()) {
            return;
        }
        std::string name;
        name.resize(nameLength);
        socket->recvall(&name[0], nameLength, &closed);
        this->was_closed.store(closed);
        if (this->was_closed.load()) {
            return;
        }
        uint32_t maxPlayers;
        socket->recvall(&maxPlayers, sizeof(uint32_t), &closed);
        this->was_closed.store(closed);
        if (this->was_closed.load()) {
            return;
        }
        uint32_t max = ntohl(maxPlayers);
        uint32_t currentPlayers;
        socket->recvall(&currentPlayers, sizeof(uint32_t), &closed);
        this->was_closed.store(closed);
        if (this->was_closed.load()) {
            return;
        }
        uint32_t current = ntohl(currentPlayers);

        GameInfo gameInfo = GameInfo(id, name, max, current);
        gamesMap[id] = gameInfo;
    }
    std::unique_ptr<DTO> message = std::make_unique<GamesListDTO>(gamesMap);
    this->deserializer.deserialize_lobbyMsg(message);
}

void ReceiverThread::receiveLobbyDTO() {
    char lobbyTypeChar;
    socket->recvall(&lobbyTypeChar, sizeof(char), &closed);
    this->was_closed.store(closed);
    if (this->was_closed.load()) {
        return;
    }
    if (!DTOValidator::validateLobbyState(lobbyTypeChar)) {
        return;
    }
    auto lobbyState = static_cast<LobbyState>(lobbyTypeChar);
    if (lobbyState == LobbyState::GAMES_LIST) {
        this->receiveGamesList();
    }
}

void ReceiverThread::run() {
    uint32_t playerId;
    socket->recvall(&playerId, sizeof(uint32_t), &closed);
    playerId = ntohl(playerId);
    std::cout << "Player ID: " << playerId << std::endl;
    this->deserializer.setPlayerId(playerId);
    
    while (!this->was_closed.load() && _keep_running) {
        try {
            char dtoTypeChar;
            socket->recvall(&dtoTypeChar, sizeof(char), &closed);
            std::cout << "Received DTO type: " << dtoTypeChar << std::endl;
            this->was_closed.store(closed);
            if (this->was_closed.load()) {
                return;
            }
            if (!DTOValidator::validateDTOType(dtoTypeChar)) {
                continue;
            }
            auto dtoType = static_cast<DTOType>(dtoTypeChar);
            std::cout << "DTO type post cast: " << static_cast<char>(dtoType) << std::endl;
            switch (dtoType) {
                case DTOType::GAME_DTO:
                    this->receiveGameDTO();
                    break;
                case DTOType::LOBBY_DTO:
                    this->receiveLobbyDTO();
                    break;
                case DTOType::COMMAND_DTO:
                    this->receiveCommandDTO();
                    break;
                default:
                    break;
            }
        } catch (const std::exception& e) {
            if (!this->was_closed.load() || _keep_running) {
                std::cerr << "ReceiverThread error: " << e.what() << std::endl;
            }
        }
    }
}   
