#ifndef LOBBY_H
#define LOBBY_H

#include <QMainWindow>

#include "../Client/QTMonitor.h"
#include "../Client/lobbyMessage.h"

namespace Ui {
class Lobby;
}

class Lobby : public QMainWindow
{
    Q_OBJECT

public:
    explicit Lobby(QWidget *parent, QTMonitor& monitor, LobbyMessage& msg);
    ~Lobby();

private slots:
    void on_btnCreateGame_clicked();

    void on_btnJoinGame_clicked();

    void on_btnBack_clicked();

private:
    Ui::Lobby *ui;
    QTMonitor& monitor;
    LobbyMessage& msg;
};

#endif // LOBBY_H
