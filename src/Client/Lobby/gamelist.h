#ifndef GAMELIST_H
#define GAMELIST_H

#include <QDialog>

#include "../Protocol/Types/lobbyMessage.h"
#include "../client.h"

namespace Ui {
class GameList;
}

class GameList: public QDialog {
    Q_OBJECT


public:
    explicit GameList(QWidget* parent, LobbyController& controller, LobbyMessage& msg, bool& clientJoinedGame);
    ~GameList();

    void updateGameList();

    void joinGame(const QString& gameName);


private slots:
    void on_btnBack_clicked();

    void on_btnJoin_clicked();

private:
    Ui::GameList* ui;
    LobbyController& controller;
    LobbyMessage& msg;
    bool& clientJoinedGame;
};

#endif  // GAMELIST_H
