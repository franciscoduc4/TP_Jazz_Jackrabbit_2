#ifndef LOBBY_H
#define LOBBY_H

#include <QDialog>

#include "../Protocol/Types/lobbyMessage.h"
#include "../client.h"

namespace Ui {
class Lobby;
}

class Lobby : public QDialog
{
    Q_OBJECT

public:
    explicit Lobby(QWidget *parent, Client& client, LobbyMessage& msg, bool& clientJoinedGame);
    ~Lobby();

private slots:
    void on_btnCreateGame_clicked();

    void on_btnJoinGame_clicked();

    void on_btnBack_clicked();

private:
    Ui::Lobby *ui;
    Client& client;
    LobbyMessage& msg;
    bool& clientJoinedGame;
};

#endif // LOBBY_H
