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
        clientJoinedGame(clientJoinedGame),
        selectedGameId(-1),
        selectedGameName("") {
    ui->setupUi(this);
    QFile file(":/Lobby/Styles/gameslist.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    ui->centralwidget->setStyleSheet(styleSheet);
    ui->labelTitle->setAttribute(Qt::WA_TranslucentBackground);

    buttonGroup = new QButtonGroup(this);
    connect(buttonGroup, &QButtonGroup::idClicked, this, &GameList::onGameSelected);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameList::updateGameList);
    timer->start(ClientConfig::getGamesListRefreshInterval());
}

GameList::~GameList() { delete ui; }

void GameList::updateGameList() {
    this->controller.sendRequest(this->msg);
    std::unordered_map<uint8_t, GameInfo> gamesList = this->controller.getGamesList();
    std::cout << "[GAME LIST] Number of games in map: " << static_cast<int>(gamesList.size()) << std::endl;
    QLayoutItem* item;
    while ((item = ui->listGamesWidget->layout()->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
    buttonGroup->setExclusive(false);
    QList<QAbstractButton*> buttons = buttonGroup->buttons();
    for (QAbstractButton* button : buttons) {
        buttonGroup->removeButton(button);
    }
    buttonGroup->setExclusive(true);

    auto* layout = new QVBoxLayout(ui->listGamesWidget);

    if (gamesList.empty()) {
        auto* label = new QLabel("No hay partidas disponibles para que te unas");
        label->setAlignment(Qt::AlignCenter);
        layout->addWidget(label);

        ui->btnJoin->hide();
    } else {
        ui->btnJoin->show();

        for (const auto& game : gamesList) {
            auto* button = new QPushButton(QString::fromStdString(game.second.getGameName()) + " (" + QString::number(game.second.getCurrentPlayers()) + "/" + QString::number(game.second.getMaxPlayers()) + ")");
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            buttonGroup->addButton(button, game.first);
            connect(button, &QPushButton::clicked, this, [this, game](){ this->onGameSelected(game.first); });
            layout->addWidget(button);
        }
    }

    ui->listGamesWidget->setLayout(layout);
}

void GameList::onGameSelected(int gameId) {
    auto gamesList = this->controller.getGamesList();
    auto game = gamesList.find(gameId);
    if (game != gamesList.end()) {
        selectedGameId = gameId;
        selectedGameName = QString::fromStdString(game->second.getGameName());
    }
}

void GameList::joinGame(const uint8_t& gameId, const QString& gameName) {
    this->msg.setGameId(gameId);
    this->msg.setGameName(gameName.toStdString());
    this->timer->stop();

    this->msg.setLobbyCmd(Command::JOIN_GAME);

    this->hide();

    auto wr = new WaitingRoom(this, this->controller, this->msg, this->clientJoinedGame);
    wr->show();
}

void GameList::on_btnJoin_clicked() {
    QAbstractButton* selectedButton = buttonGroup->checkedButton();

    if (selectedButton) {
        selectedGameId = buttonGroup->id(selectedButton);
        selectedGameName = selectedButton->text();
        joinGame(selectedGameId, selectedGameName);
    } else {
        QMessageBox::information(this, "Error", "Seleccione un juego para unirse.");
    }
}

void GameList::on_btnBack_clicked() {
    this->msg.setGameName("");
    this->msg.setGameId(-1);

    this->hide();

    QWidget* parent = this->parentWidget();
    if (parent) {
        parent->show();
    }

    this->deleteLater();
}