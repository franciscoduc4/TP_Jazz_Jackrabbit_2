#ifndef CREATEGAME_H
#define CREATEGAME_H

#include <QMainWindow>
#include "../Client/senderThread.h"
#include "../Client/receiverThread.h"
#include "../Client/qtMonitor.h"
#include "../Client/lobbyMessage.h"

namespace Ui {
class CreateGame;
}

class CreateGame : public QMainWindow
{
    Q_OBJECT
    SenderThread& sender;
    ReceiverThread& receiver;
    QTMonitor& monitor;
    LobbyMessage& msg;

public:
    explicit CreateGame(QWidget *parent = nullptr, SenderThread& sender, ReceiverThread& receiver, QTMonitor& monitor, LobbyMessage& msg);
    ~CreateGame();

private slots:
    void on_btnCreate_clicked();

    void on_btnBack_clicked();

private:
    Ui::CreateGame *ui;
};

#endif // CREATEGAME_H
