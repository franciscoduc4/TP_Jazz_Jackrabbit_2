#ifndef LOBBY_H
#define LOBBY_H

#include <QMainWindow>

#include "../Common/socket.h"
#include "../Client/senderThread.h"
#include "../Client/receiverThread.h"
#include "../Client/qtMonitor.h"
#include "../Client/lobbyMessage.h"

namespace Ui {
class Lobby;
}

class Lobby : public QMainWindow
{
    Q_OBJECT
    SenderThread& sender;
    ReceiverThread& receiver;
    QTMonitor& monitor;
    LobbyMessage& msg;

public:
    explicit Lobby(QWidget *parent = nullptr, SenderThread& sender, ReceiverThread& receiver, QTMonitor& monitor, LobbyMessage& msg);
    ~Lobby();

private slots:
    void on_btnCreateGame_clicked();

    void on_btnJoinGame_clicked();

    void on_btnBack_clicked();

private:
    Ui::Lobby *ui;
};

#endif // LOBBY_H
