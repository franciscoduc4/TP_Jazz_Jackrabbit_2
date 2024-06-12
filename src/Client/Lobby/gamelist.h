#ifndef GAMELIST_H
#define GAMELIST_H

#include <QDialog>

#include "../../Common/Types/lobbyMessage.h"
#include "../client.h"
#include "../../Common/Config/ClientConfig.h"

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

private:
    Ui::GameList* ui;
    LobbyController& controller;
    LobbyMessage& msg;
    bool& clientJoinedGame;
    QTimer* timer;
};

#endif  // GAMELIST_H
