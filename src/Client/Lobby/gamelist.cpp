#include "gamelist.h"

#include <QFile>
#include <QHBoxLayout>
#include <QTimer>

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

    this->timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameList::updateGameList);
    timer->start(ClientConfig::getGamesListRefreshInterval());
}

GameList::~GameList() { delete ui; }

void GameList::updateGameList() {
    this->controller.sendRequest(this->msg);
    auto gamesList = this->controller.getGamesList();

    // Clear the QListWidget
    ui->listGames->clear();

    std::cout << "Games List size: " << gamesList.size() << std::endl;

    if (gamesList.empty()) {
        // If there are no games, display a message
        QListWidgetItem* item = new QListWidgetItem("No hay juegos disponibles para unirse");
        item->setForeground(Qt::red);
        ui->listGames->addItem(item);
    } else {
        for (const auto& game : gamesList) {
            QListWidgetItem* item = new QListWidgetItem;
            QWidget* widget = new QWidget;
            QHBoxLayout* layout = new QHBoxLayout;
            QLabel* gameNameLabel = new QLabel(QString::fromStdString(game.second.getGameName()));
            QLabel* playersLabel = new QLabel(QString::number(game.second.getCurrentPlayers()) + "/" + QString::number(game.second.getMaxPlayers()));
            QPushButton* joinButton = new QPushButton("Unirme");

            connect(joinButton, &QPushButton::clicked, this, [this, game]() {
                this->joinGame(QString::fromStdString(game.second.getGameName()));
            });

            layout->addWidget(gameNameLabel, 3);
            layout->addWidget(playersLabel, 1);
            layout->addWidget(joinButton, 1);
            widget->setLayout(layout);

            item->setSizeHint(widget->sizeHint());
            ui->listGames->addItem(item);
            ui->listGames->setItemWidget(item, widget);
        }
    }
}

void GameList::joinGame(const QString& gameName) {
    // this->msg.setGameName(gameName);
    // client.joinGame(this->msg);
    this->timer->stop();

    this->msg.setLobbyCmd(Command::JOIN_GAME);

    this->hide();

    auto wr = new WaitingRoom(this, this->controller, this->msg, this->clientJoinedGame);
    wr->show();
}

void GameList::on_btnBack_clicked() {
    // this->msg.setGameName("");

    this->hide();

    QWidget* parent = this->parentWidget();
    if (parent) {
        parent->show();
    }

    this->deleteLater();
}