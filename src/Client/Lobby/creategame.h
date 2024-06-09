#ifndef CREATEGAME_H
#define CREATEGAME_H

#include <QDialog>

#include "../Protocol/Types/lobbyMessage.h"
#include "../client.h"

namespace Ui {
class CreateGame;
}

class CreateGame : public QDialog
{
    Q_OBJECT
    

public:
    explicit CreateGame(QWidget *parent, Client& client, LobbyMessage& msg, bool& clientJoinedGame);
    ~CreateGame();

private slots:
    void on_btnCreate_clicked();

    void on_btnBack_clicked();

private:
    Ui::CreateGame *ui;
    Client& client;
    LobbyMessage& msg;
    bool& clientJoinedGame;
};

#endif // CREATEGAME_H
