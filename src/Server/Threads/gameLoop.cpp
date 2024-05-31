#include "gameLoop.h"


GameLoopThread::GameLoopThread(int32_t gameId, std::string gameName, 
        int32_t& playerId, Episode episode, GameMode gameMode,
        uint8_t maxPlayers, std::shared_ptr<Queue<GameDTO>> sendQueue) :
        gameId(gameId), 
        gameName(gameName), 
        keepRunning(true), 
        recvQueue(queueMonitor.createQueue()),
        maxPlayers(maxPlayers), 
        isFull(false),
        sendQueue(sendQueue)
        {}

