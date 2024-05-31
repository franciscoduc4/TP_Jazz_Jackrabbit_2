#include "serializer.h"
#include <arpa/inet.h>

Serializer::Serializer(std::shared_ptr<Socket> socket) : socket(socket) {}

void Serializer::sendCommand(const CommandDTO& dto, bool& wasClosed) {
    Command command = dto.getCommand();
    socket->sendall(&command, 1, &wasClosed);
    std::vector<char> buffer;

    switch (command) {
        case Command::CREATE_GAME:
            buffer = serializeCreateGame(static_cast<const CreateGameDTO&>(dto));
            break;
        case Command::JOIN_GAME:
            buffer = serializeJoinGame(static_cast<const JoinGameDTO&>(dto));
            break;
        case Command::GAMES_LIST:
            buffer = serializeGamesList(dto);
            break;
        case Command::CHARACTER_TYPE:
            buffer = serializeCharacterType(static_cast<const CharacterTypeDTO&>(dto));
            break;
        case Command::MOVE:
            buffer = serializeMove(static_cast<const MoveDTO&>(dto));
            break;
        case Command::START_GAME:
            buffer = serializeStart(dto);
            break;
        // case Command::SHOOT:
        //     buffer = serializeShooting(dto);
        //     break;
        // case Command::RELOAD:
        //     buffer = serializeReloading(dto);
        //     break;
        // case Command::SWITCH_WEAPON:
        //     buffer = serializeSwitchWeapon(dto);
        //   break;
        default:
            return;
    }
    socket->sendall(buffer.data(), buffer.size(), &wasClosed);
}

std::vector<char> Serializer::serializeCreateGame(const CreateGameDTO& dto) {
    std::vector<char> buffer;
    buffer.push_back(static_cast<char>(Command::CREATE_GAME));
    Episode episodeName = dto.getEpisodeName();
    buffer.push_back(static_cast<char>(episodeName));
    GameMode gameMode = dto.getGameMode();
    buffer.push_back(static_cast<char>(gameMode));
    uint8_t maxPlayers = dto.getMaxPlayers();
    buffer.push_back(static_cast<char>(maxPlayers));
    return buffer;
}

std::vector<char> Serializer::serializeJoinGame(const JoinGameDTO& dto) {
    std::vector<char> buffer;
    buffer.push_back(static_cast<char>(Command::JOIN_GAME));
    int32_t gameId = htonl(dto.getGameId());
    unsigned char const * p = reinterpret_cast<unsigned char const *>(&gameId);
    buffer.insert(buffer.end(), p, p + sizeof(int32_t));
    return buffer;
}

std::vector<char> Serializer::serializeGamesList(const CommandDTO& dto) {
    std::vector<char> buffer;
    buffer.push_back(static_cast<char>(Command::GAMES_LIST));
    return buffer;
}

std::vector<char> Serializer::serializeCharacterType(const CharacterTypeDTO& dto) {
    std::vector<char> buffer;
    buffer.push_back(static_cast<char>(Command::CHARACTER_TYPE));
    Character character = dto.getCharacter();
    buffer.push_back(static_cast<char>(character));
    return buffer;
}

std::vector<char> Serializer::serializeMove(const MoveDTO& dto) {
    std::vector<char> buffer;
    buffer.push_back(static_cast<char>(Command::MOVE));
    Move moveType = dto.getMoveType();
    buffer.push_back(static_cast<char>(moveType));
    return buffer;
}

std::vector<char> Serializer::serializeStart(const CommandDTO& dto) {
    std::vector<char> buffer;
    buffer.push_back(static_cast<char>(Command::START_GAME));
    return buffer;
}

// std::vector<char> Serializer::serializeShooting(const CommandDTO& dto) {
//     std::vector<char> buffer;
//     buffer.push_back(static_cast<char>(Command::SHOOT));
//     return buffer;
// }

// std::vector<char> Serializer::serializeReloading(const CommandDTO& dto) {
//     std::vector<char> buffer;
//     buffer.push_back(static_cast<char>(Command::RELOAD));
//     return buffer;
// }

// std::vector<char> Serializer::serializeSwitchWeapon(const CommandDTO& dto) {
//     std::vector<char> buffer;
//     buffer.push_back(static_cast<char>(Command::SWITCH_WEAPON));
//     return buffer;
// }
