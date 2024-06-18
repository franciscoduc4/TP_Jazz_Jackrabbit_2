#ifndef WAITINGROOM_H
#define WAITINGROOM_H

#include <QDialog>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QMessageBox>

#include <utility>
#include <memory>

#include "../../Common/Types/lobbyMessage.h"
#include "../client.h"

namespace Ui {
class WaitingRoom;
}

class WaitingRoom : public QDialog
{
    Q_OBJECT

signals:
    void numPlayersUpdated(int numPlayers);

private slots:
    void updateNumPlayers(int numPlayers);
    void pollForUpdates();

public:
    explicit WaitingRoom(QWidget *parent, LobbyController& controller, LobbyMessage& msg, bool& clientJoinedGame);
    ~WaitingRoom();

private:
    Ui::WaitingRoom *ui;
    LobbyController& controller;
    LobbyMessage& msg;
    bool& clientJoinedGame;
    QThread* updateThread;
    QMutex mutex;
    QWaitCondition condition;
};

#endif // WAITINGROOM_H
