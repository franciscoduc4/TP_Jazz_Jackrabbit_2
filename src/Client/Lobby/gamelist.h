#ifndef GAMELIST_H
#define GAMELIST_H

#include <QMainWindow>

#include "../Protocol/Types/lobbyMessage.h"
#include "../client.h"

namespace Ui {
class GameList;
}

class GameList: public QMainWindow {
    Q_OBJECT


public:
    explicit GameList(QWidget* parent, Client& client, LobbyMessage& msg, bool& clientJoinedGame);
    ~GameList();

    void updateGameList();

    void joinGame(const QString& gameName);


private slots:
    void on_btnBack_clicked();

    void on_btnJoin_clicked();

private:
    Ui::GameList* ui;
    Client& client;
    LobbyMessage& msg;
    bool& clientJoinedGame;
};

#endif  // GAMELIST_H
