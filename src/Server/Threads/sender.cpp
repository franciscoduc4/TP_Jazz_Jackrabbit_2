#include "sender.h"

SenderThread::SenderThread(std::shared_ptr<Socket> socket, std::atomic<bool>& keepPlaying,
                           std::atomic<bool>& inGame, GameMonitor& gameMonitor, int32_t playerId,
                           QueueMonitor<GameDTO>& queueMonitor):
        playerId(playerId),
        serializer(socket),
        deserializer(socket),
        keepPlaying(keepPlaying),
        inGame(inGame),
        wasClosed(false),
        sendQueue(queueMonitor.createQueue()),
        receiver(socket, keepPlaying, inGame, sendQueue, playerId),
        gameMonitor(gameMonitor),
        recvQueue() {}

void SenderThread::run() {
    serializer.sendId(playerId);
    while (keepPlaying) {
        runLobby();
    }
}

void SenderThread::runLobby() {
    while (keepPlaying) {
        try {
            std::unique_ptr<CommandDTO> command = deserializer.getCommand(wasClosed, playerId);

            if (command->getCommand() == Command::CREATE_GAME) {
                CreateGameDTO* createGameCommand = dynamic_cast<CreateGameDTO*>(command.get());

                if (createGameCommand) {
                    Episode episode = createGameCommand->getEpisodeName();
                    GameMode gameMode = createGameCommand->getGameMode();
                    uint8_t maxPlayers = createGameCommand->getMaxPlayers();
                    // gameMonitor.createGame(playerId, episode, gameMode, maxPlayers);
                }
            }
        }
    }
}
