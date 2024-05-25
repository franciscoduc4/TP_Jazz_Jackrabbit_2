#ifndef WAITINGROOM_H
#define WAITINGROOM_H

#include <QMainWindow>

#include "../Client/senderThread.h"
#include "../Client/receiverThread.h"
#include "../Client/qtMonitor.h"
#include "../Client/lobbyMessage.h"

namespace Ui {
class WaitingRoom;
}

class WaitingRoom : public QMainWindow
{
    Q_OBJECT
    SenderThread& sender;
    ReceiverThread& receiver;
    QTMonitor& monitor;
    LobbyMessage& msg;


public:
    explicit WaitingRoom(QWidget *parent = nullptr, SenderThread& sender, ReceiverThread& receiver, QTMonitor& monitor, LobbyMessage& msg);
    ~WaitingRoom();

private slots:
    void on_btnBack_clicked();

private:
    Ui::WaitingRoom *ui;
};

#endif // WAITINGROOM_H
