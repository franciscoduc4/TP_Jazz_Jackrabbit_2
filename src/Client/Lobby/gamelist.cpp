#include "gamelist.h"

#include "ui_gamelist.h"
#include "waitingroom.h"

GameList::GameList(QWidget* parent, Client& client, LobbyMessage& msg, bool& clientJoinedGame):
        QMainWindow(parent),
        ui(new Ui::GameList),
        client(client),
        msg(msg),
        clientJoinedGame(clientJoinedGame) {
    ui->setupUi(this);
}

GameList::~GameList() { delete ui; }

void GameList::updateGameList() {
    // ui->listGames->clear();

    // auto games = client.getGameList();
    // for (const auto& game: games) {
    //     GameListItem* itemWidget = new GameListItem(game.name, game.players, game.totalPlayers);
    //     QListWidgetItem* item = new QListWidgetItem(ui->listGames);
    //     item->setSizeHint(itemWidget->sizeHint());
    //     ui->listGames->setItemWidget(item, itemWidget);

    //     connect(itemWidget, &GameListItem::joinGame, this, &GameList::joinGame);
    // }
}

void GameList::joinGame(const QString& gameName) {
    // this->msg.setGameName(gameName);
    // client.joinGame(this->msg);

    // WaitingRoom* wr = new WaitingRoom(this, this->client, this->msg, this->clientJoinedGame);
    // wr->show();
    // this->close();
}

void GameList::on_btnJoin_clicked() {
    // Do Something.
}

void GameList::on_btnBack_clicked() {
    this->msg.setGameName("");
    QWidget* parent = this->parentWidget();
    if (parent) {
        parent->show();
    }
    this->close();
}
