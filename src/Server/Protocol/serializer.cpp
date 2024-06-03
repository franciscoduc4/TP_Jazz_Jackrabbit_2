#include "serializer.h"

#include <map>
#include <string>
#include <utility>

#include <arpa/inet.h>

Serializer::Serializer(std::shared_ptr<Socket> socket): socket(socket) {}

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
        // case Command::CHARACTER_TYPE:
        //     buffer = serializeCharacterType(static_cast<const CharacterTypeDTO&>(dto));
        //     break;
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
    unsigned char const* p = reinterpret_cast<unsigned char const*>(&gameId);
    buffer.insert(buffer.end(), p, p + sizeof(int32_t));
    return buffer;
}

std::vector<char> Serializer::serializeGamesList(const CommandDTO& dto) {
    std::vector<char> buffer;
    buffer.push_back(static_cast<char>(Command::GAMES_LIST));
    return buffer;
}

std::vector<char> Serializer::serializeMove(const MoveDTO& dto) {
    std::vector<char> buffer;
    buffer.push_back(static_cast<char>(Command::MOVE));
    Direction moveType = dto.getMoveType();
    buffer.push_back(static_cast<char>(moveType));
    return buffer;
}

std::vector<char> Serializer::serializeStart(const CommandDTO& dto) {
    std::vector<char> buffer;
    buffer.push_back(static_cast<char>(Command::START_GAME));
    return buffer;
}

void Serializer::sendId(int32_t id) {
    int32_t idToSend = htonl(id);
    unsigned char const* p = reinterpret_cast<unsigned char const*>(&idToSend);
    socket->sendall(p, sizeof(int32_t), nullptr);
}
void Serializer::serializeGamesList(const std::map<int32_t, std::string>& games,
                                    std::vector<char>& buffer) {
    for (const auto& pair: games) {
        std::string key = std::to_string(pair.first);
        std::string value = pair.second;
        buffer.insert(buffer.end(), key.begin(), key.end());
        buffer.push_back(':');
        buffer.insert(buffer.end(), value.begin(), value.end());
        buffer.push_back(',');
    }
}

void Serializer::sendLobbyDTO(const std::unique_ptr<LobbyDTO> dto) {
    std::vector<char> buffer;
    bool gameIsCreated = dto->getGameCreated();
    buffer.push_back(static_cast<char>(gameIsCreated));
    bool gameIsJoined = dto->getGameJoined();
    buffer.push_back(static_cast<char>(gameIsJoined));
    bool gameIsStarted = dto->getGameStarted();
    buffer.push_back(static_cast<char>(gameIsStarted));
    GamesListDTO gamesList = dto->getGamesList();
    serializeGamesList(gamesList.getGames(), buffer);

    socket->sendall(buffer.data(), buffer.size(), nullptr);
}

std::vector<char> Serializer::serializePlayerDTO(const std::unique_ptr<PlayerDTO> dto) {
    std::vector<char> buffer;
    buffer.push_back(static_cast<char>(dto->getPlayerId()));
    buffer.push_back(static_cast<char>(dto->getDamage()));
    buffer.push_back(static_cast<char>(dto->getHealth()));
    buffer.push_back(static_cast<char>(dto->getSpeed()));
    buffer.push_back(static_cast<char>(dto->getRespawnTime()));
    buffer.push_back(static_cast<char>(dto->getX()));
    buffer.push_back(static_cast<char>(dto->getY()));
    // buffer.push_back(static_cast<char>(dto->getCurrentWeapon()));
    return buffer;
}

std::vector<char> Serializer::serializeEnemyDTO(const std::unique_ptr<EnemyDTO> dto) {
    std::vector<char> buffer;
    buffer.push_back(static_cast<char>(dto->getEnemyId()));
    buffer.push_back(static_cast<char>(dto->getDamage()));
    buffer.push_back(static_cast<char>(dto->getHealth()));
    buffer.push_back(static_cast<char>(dto->getSpeed()));
    buffer.push_back(static_cast<char>(dto->getX()));
    buffer.push_back(static_cast<char>(dto->getY()));
    return buffer;
}

std::vector<char> Serializer::serializeBulletDTO(const std::unique_ptr<BulletDTO> dto) {
    std::vector<char> buffer;
    buffer.push_back(static_cast<char>(dto->getBulletId()));
    buffer.push_back(static_cast<char>(dto->getDamage()));
    buffer.push_back(static_cast<char>(dto->getSpeed()));
    buffer.push_back(static_cast<char>(dto->getX()));
    buffer.push_back(static_cast<char>(dto->getY()));
    return buffer;
}

std::vector<char> Serializer::serializeItemDTO(const std::unique_ptr<ItemDTO> dto) {
    std::vector<char> buffer;
    buffer.push_back(static_cast<char>(dto->getX()));
    buffer.push_back(static_cast<char>(dto->getY()));
    return buffer;
}

// std::vector<char> Serializer::serializeSprite(const std::unique_ptr<Sprite> sprite){
//     std::vector<char> buffer;
//     buffer.push_back(static_cast<char>(sprite->getSpriteSheetPath()));
//     buffer.push_back(static_cast<char>(sprite->getVertices()));
//     buffer.push_back(static_cast<char>(sprite->getColourKey()));
//     return buffer;
// }

std::vector<char> Serializer::serializeTileDTO(const std::unique_ptr<TileDTO> dto) {
    std::vector<char> buffer;
    buffer.push_back(static_cast<char>(dto->getX()));
    buffer.push_back(static_cast<char>(dto->getY()));
    // buffer.push_back(static_cast<char>(dto->getSprite()));
    return buffer;
}


std::vector<char> Serializer::serializeWeaponDTO(const std::unique_ptr<WeaponDTO> dto) {
    std::vector<char> buffer;
    buffer.push_back(static_cast<char>(dto->getWeaponId()));
    buffer.push_back(static_cast<char>(dto->getDamage()));
    buffer.push_back(static_cast<char>(dto->getAmmo()));
    buffer.push_back(static_cast<char>(dto->getShootSpeed()));
    buffer.push_back(static_cast<char>(dto->getX()));
    buffer.push_back(static_cast<char>(dto->getY()));
    std::vector<char> bullet = serializeBulletDTO(dto->getBullet());
    buffer.insert(buffer.end(), bullet.begin(), bullet.end());
    // std::vector<char> sprite = serializeSprite(dto->getSprite());
    // buffer.insert(buffer.end(), sprite.begin(), sprite.end());
    return buffer;
}

void Serializer::sendGameDTO(const std::unique_ptr<GameDTO> dto) {
    std::vector<char> buffer;


    std::vector<PlayerDTO> players = dto->getPlayers();
    for (const auto& player: players) {
        std::vector<char> playerBuffer = serializePlayerDTO(std::make_unique<PlayerDTO>(player));
        buffer.insert(buffer.end(), playerBuffer.begin(), playerBuffer.end());
    }

    std::vector<EnemyDTO> enemies = dto->getEnemies();
    for (const auto& enemy: enemies) {
        std::vector<char> enemyBuffer = serializeEnemyDTO(std::make_unique<EnemyDTO>(enemy));
        buffer.insert(buffer.end(), enemyBuffer.begin(), enemyBuffer.end());
    }

    std::vector<BulletDTO> bullets = dto->getBullets();
    for (const auto& bullet: bullets) {
        std::vector<char> bulletBuffer = serializeBulletDTO(std::make_unique<BulletDTO>(bullet));
        buffer.insert(buffer.end(), bulletBuffer.begin(), bulletBuffer.end());
    }

    std::vector<ItemDTO> items = dto->getItems();
    for (const auto& item: items) {
        std::vector<char> itemBuffer = serializeItemDTO(std::make_unique<ItemDTO>(item));
        buffer.insert(buffer.end(), itemBuffer.begin(), itemBuffer.end());
    }

    std::vector<WeaponDTO> weapons = dto->getWeapons();
    for (const auto& weapon: weapons) {
        std::vector<char> weaponBuffer = serializeWeaponDTO(std::make_unique<WeaponDTO>(weapon));
        buffer.insert(buffer.end(), weaponBuffer.begin(), weaponBuffer.end());
    }

    std::vector<TileDTO> tiles = dto->getTiles();
    for (const auto& tile: tiles) {
        std::vector<char> tileBuffer = serializeTileDTO(std::make_unique<TileDTO>(tile));
        buffer.insert(buffer.end(), tileBuffer.begin(), tileBuffer.end());
    }


    socket->sendall(buffer.data(), buffer.size(), nullptr);
}
