#ifndef GAMELIST_H
#define GAMELIST_H

#include <QMainWindow>

#include "../Client/senderThread.h"
#include "../Client/receiverThread.h"
#include "../Client/qtMonitor.h"
#include "../Client/lobbyMessage.h"

namespace Ui {
class GameList;
}

class GameList : public QMainWindow
{
    Q_OBJECT
    SenderThread& sender;
    ReceiverThread& receiver;
    QTMonitor& monitor;
    LobbyMessage& msg;

public:
    explicit GameList(QWidget *parent = nullptr, SenderThread& sender, ReceiverThread& receiver, QTMonitor& monitor, LobbyMessage& msg);
    ~GameList();

private slots:
    void on_btnBack_clicked();

    void on_btnJoin_clicked();

private:
    Ui::GameList *ui;
};

#endif // GAMELIST_H
