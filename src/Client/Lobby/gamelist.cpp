#include "gamelist.h"

#include <QFile>

#include "ui_gamelist.h"
#include "waitingroom.h"

GameList::GameList(QWidget* parent, LobbyController& controller, LobbyMessage& msg, bool& clientJoinedGame):
        QDialog(parent),
        ui(new Ui::GameList),
        controller(controller),
        msg(msg),
        clientJoinedGame(clientJoinedGame) {
    ui->setupUi(this);
    QFile file(":/Lobby/Styles/gameslist.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    ui->centralwidget->setStyleSheet(styleSheet);
    ui->labelTitle->setAttribute(Qt::WA_TranslucentBackground);
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

    this->msg.setLobbyCmd(Command::JOIN_GAME);

    this->hide();

    auto wr = new WaitingRoom(this, this->controller, this->msg, this->clientJoinedGame);
    wr->show();
}

void GameList::on_btnJoin_clicked() {
    this->hide();
    auto wr = new WaitingRoom(this, this->controller, this->msg, this->clientJoinedGame);
    wr->show();
}

void GameList::on_btnBack_clicked() {
    this->msg.setGameName("");

    this->hide();

    QWidget* parent = this->parentWidget();
    if (parent) {
        parent->show();
    }

    this->deleteLater();
}
