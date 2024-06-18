#ifndef GAMELIST_H
#define GAMELIST_H

#include <QButtonGroup>
#include <QDialog>
#include <QMessageBox>
#include <QTimer>

#include <utility>
#include <string>

#include "../../Common/Config/ClientConfig.h"
#include "../../Common/Types/lobbyMessage.h"
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
    void onGameSelected(int id);
    void joinGame(const uint8_t& gameId, const QString& gameName);


private slots:
    void on_btnBack_clicked();
    void on_btnJoin_clicked();

private:
    Ui::GameList* ui;
    LobbyController& controller;
    LobbyMessage& msg;
    bool& clientJoinedGame;
    QTimer* timer;
    QButtonGroup* buttonGroup;
    uint8_t selectedGameId;
    QString selectedGameName;
    uint8_t selectedGameMapId;
};

#endif  // GAMELIST_H
