#ifndef LOBBY_H
#define LOBBY_H

#include <QDialog>

#include "../../Common/Types/lobbyMessage.h"
#include "../client.h"

namespace Ui {
class Lobby;
}

class Lobby : public QDialog
{
    Q_OBJECT

public:
    explicit Lobby(QWidget *parent, LobbyController& controller, LobbyMessage& msg, bool& clientJoinedGame);
    ~Lobby();

private slots:
    void on_btnCreateGame_clicked();

    void on_btnJoinGame_clicked();

    void on_btnBack_clicked();

private:
    Ui::Lobby *ui;
    LobbyController& controller;
    LobbyMessage& msg;
    bool& clientJoinedGame;
};

#endif // LOBBY_H
