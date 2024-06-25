#include "gamelist.h"

#include <QFile>
#include <QHBoxLayout>
#include <QTimer>

#include "ui_gamelist.h"
#include "waitingroom.h"

GameList::GameList(QWidget* parent, LobbyController& controller, LobbyMessage& msg,
                   bool& clientJoinedGame):
        QDialog(parent),
        ui(new Ui::GameList),
        controller(controller),
        msg(msg),
        clientJoinedGame(clientJoinedGame),
        selectedGameId(-1),
        selectedGameName(""),
        selectedGameMapId(-1),
        gamesList({}) {
    ui->setupUi(this);
    QFile file(":/Lobby/Styles/gameslist.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    ui->centralwidget->setStyleSheet(styleSheet);
    ui->labelTitle->setAttribute(Qt::WA_TranslucentBackground);

    if (this->msg.getLobbyCmd() != Command::GAMES_LIST) {
        this->msg.setLobbyCmd(Command::GAMES_LIST);
    }

    buttonGroup = new QButtonGroup(this);
    connect(buttonGroup, &QButtonGroup::idClicked, this, &GameList::onGameSelected);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameList::updateGameList);
    timer->start(ClientConfig::getGamesListRefreshInterval());
}

GameList::~GameList() { delete ui; }

void GameList::updateGameList() {
    // Fetch available games
    this->controller.sendRequest(this->msg);
    // Receive available games
    this->gamesList = this->controller.getGamesList();
    std::cout << "[GAME LIST] Number of games in map: " << static_cast<int>(gamesList.size())
              << std::endl;
    if (ui->listGamesWidget->layout() != nullptr) {
        QLayoutItem* item;
        while ((item = ui->listGamesWidget->layout()->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete ui->listGamesWidget->layout();
    }
    buttonGroup->setExclusive(false);
    QList<QAbstractButton*> buttons = buttonGroup->buttons();
    for (QAbstractButton* button: buttons) {
        buttonGroup->removeButton(button);
    }
    buttonGroup->setExclusive(true);

    auto* layout = new QVBoxLayout(ui->listGamesWidget);

    if (gamesList.empty()) {
        auto* label = new QLabel("No hay partidas disponibles para que te unas");
        label->setAlignment(Qt::AlignCenter);
        label->setAttribute(Qt::WA_TranslucentBackground);
        QFont font("Jazz Jackrabbit 2", 30);
        label->setFont(font);
        label->setWordWrap(true);
        label->setStyleSheet("QLabel { color : red; }");
        layout->addWidget(label);

        ui->btnJoin->hide();
    } else {
        ui->btnJoin->show();

        for (const auto& game: gamesList) {
            auto* button =
                    new QPushButton(QString::fromStdString("Game Name: " + game.second.getGameName()) +
                                    " | Map: " + QString::fromStdString(game.second.getMapName()) +
                                    " | (" + QString::number(game.second.getCurrentPlayers()) + "/" +
                                    QString::number(game.second.getMaxPlayers()) + ")");
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            button->setCheckable(true);

            QFont font("Jazz Jackrabbit 2");
            font.setPointSize(30);
            QFontMetrics fm(font);
            int textWidth = fm.horizontalAdvance(button->text());

            while (textWidth > button->width() && font.pointSize() > 1) {
                font.setPointSize(font.pointSize() - 1);
                fm = QFontMetrics(font);
                textWidth = fm.horizontalAdvance(button->text());
            }

            button->setFont(font);
            buttonGroup->addButton(button, game.first);
            connect(button, &QPushButton::clicked, this,
                    [this, game]() { this->onGameSelected(game.first); });
            layout->addWidget(button);
        }
    }

    ui->listGamesWidget->setLayout(layout);
}

void GameList::onGameSelected(int gameId) {
    auto game = gamesList.find(gameId);
    if (game != gamesList.end()) {
        selectedGameId = gameId;
        selectedGameName = QString::fromStdString(game->second.getGameName());
        selectedGameMapId = game->second.getMapId();
    }
}

void GameList::joinGame(const uint8_t& gameId, const QString& gameName) {
    this->timer->stop();

    this->clientJoinedGame = true;

    this->msg.setGameId(gameId);
    this->msg.setGameName(gameName.toStdString());
    this->msg.setMap(selectedGameMapId);
    this->msg.setLobbyCmd(Command::JOIN_GAME);
    this->msg.setMaxPlayers(gamesList[gameId].getMaxPlayers());

    // Send Join Game
    this->controller.sendRequest(this->msg);
    // Receive Join Game
    std::pair<bool, GameInfo> jgAck = this->controller.recvResponse();
    // Receive Game Update
    std::pair<bool, GameInfo> guAck = this->controller.recvResponse();

    if (!jgAck.first || !guAck.first) {
        QMessageBox::warning(this, "Error", "No se pudo unir a la partida.");
        this->clearFocus();
        this->deleteLater();
        QCoreApplication::exit(37);
        return;
    }

    if (this->controller.canStartGame()) {
        this->msg.setLobbyCmd(Command::START_GAME);
        this->controller.startGame(this->msg);
        std::pair<bool, GameInfo> sgAck = this->controller.recvResponse();
        if (!sgAck.first) {
            QMessageBox::warning(this, "Error", "No se pudo iniciar la partida.");
            this->clearFocus();
            this->deleteLater();
            QCoreApplication::exit(37);
            return;
        }
        this->clearFocus();
        this->deleteLater();
        QCoreApplication::exit(0);
        return;
    }

    this->hide();

    auto wr = new WaitingRoom(this, this->controller, this->msg, this->clientJoinedGame);
    wr->show();
}

void GameList::on_btnJoin_clicked() {
    QAbstractButton* selectedButton = buttonGroup->checkedButton();

    if (selectedButton) {
        selectedGameId = buttonGroup->id(selectedButton);
        selectedGameName = QString::fromStdString(gamesList[selectedGameId].getGameName());
        joinGame(selectedGameId, selectedGameName);
    } else {
        QMessageBox::information(this, "Error", "Seleccione un juego para unirse.");
    }
}

void GameList::on_btnBack_clicked() {
    this->msg.setGameName("");
    this->msg.setGameId(-1);
    this->msg.setLobbyCmd(Command::JOIN_GAME);

    this->hide();

    QWidget* parent = this->parentWidget();
    if (parent) {
        parent->show();
    }

    this->deleteLater();
}
