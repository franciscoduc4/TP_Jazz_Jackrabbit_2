#ifndef WAITINGROOM_H
#define WAITINGROOM_H

#include <QDialog>
#include <QTimer>
#include <QMessageBox>

#include <utility>
#include <memory>

#include "../../Common/Types/lobbyMessage.h"
#include "../../Common/DTO/command.h"
#include "../../Common/queue.h"
#include "../client.h"

namespace Ui {
class WaitingRoom;
}

class WaitingRoom : public QDialog
{
    Q_OBJECT

signals:
    void numPlayersUpdated(bool startGameReceived, int numPlayers);

private slots:
    void updateNumPlayers(bool startGameReceived, int numPlayers);
    void fetchUpdates();

public:
    explicit WaitingRoom(QWidget *parent, LobbyController& controller, LobbyMessage& msg, bool& clientJoinedGame);
    ~WaitingRoom();

private:
    Ui::WaitingRoom *ui;
    LobbyController& controller;
    LobbyMessage& msg;
    bool& clientJoinedGame;
    QTimer updateTimer;  // Replace QThread, QMutex, and QWaitCondition with QTimer
    Queue<std::unique_ptr<CommandDTO>> recvQueue;
};

#endif // WAITINGROOM_H
