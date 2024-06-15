#include "creategame.h"

#include <QMessageBox>

#include "characterselection.h"
#include "ui_creategame.h"

CreateGame::CreateGame(QWidget* parent, LobbyController& controller, LobbyMessage& msg,
                       bool& clientJoinedGame):
        QDialog(parent),
        ui(new Ui::CreateGame),
        controller(controller),
        msg(msg),
        clientJoinedGame(clientJoinedGame) {
    ui->setupUi(this);
    std::cout << "[CREATE GAME] UI setup completed" << std::endl;

    QFile file(":/Lobby/Styles/creategame.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    ui->centralwidget->setStyleSheet(styleSheet);
    ui->labelTitle->setAttribute(Qt::WA_TranslucentBackground);
    ui->labelName->setAttribute(Qt::WA_TranslucentBackground);
    ui->labelNumPlayers->setAttribute(Qt::WA_TranslucentBackground);
    std::cout << "[CREATE GAME] Stylesheet applied" << std::endl;
}

CreateGame::~CreateGame() {
    delete ui;
    std::cout << "[CREATE GAME] Destructor called, UI deleted" << std::endl;
}

void CreateGame::on_btnCreate_clicked() {
    std::cout << "[CREATE GAME] Create button clicked" << std::endl;

    QString gameName = ui->gameName->text();
    int numPlayers = ui->numPlayers->value();

    if (gameName.isEmpty()) {
        QMessageBox::warning(this, "Error", "Ingrese un nombre para la partida");
        std::cout << "[CREATE GAME] No game name provided, showing error message" << std::endl;
        return;
    }

    this->msg.setLobbyCmd(Command::CREATE_GAME);

    this->msg.setGameName(gameName.toStdString());
    std::cout << "[CREATE GAME] Game name set: " << gameName.toStdString() << std::endl;

    this->msg.setMaxPlayers(numPlayers);
    std::cout << "[CREATE GAME] Number of players set: " << numPlayers << std::endl;

    this->hide();
    std::cout << "[CREATE GAME] CreateGame dialog hidden" << std::endl;

    auto cs = new CharacterSelection(this, this->controller, this->msg, this->clientJoinedGame);
    cs->show();
    std::cout << "[CREATE GAME] CharacterSelection dialog shown" << std::endl;
}

void CreateGame::on_btnBack_clicked() {
    std::cout << "[CREATE GAME] Back button clicked" << std::endl;

    this->msg.setGameName("");
    this->msg.setMaxPlayers(0);
    std::cout << "[CREATE GAME] Game name and number of players reset" << std::endl;

    this->hide();
    std::cout << "[CREATE GAME] CreateGame dialog hidden" << std::endl;

    QWidget* parent = this->parentWidget();
    if (parent) {
        parent->show();
        std::cout << "[CREATE GAME] Parent widget shown" << std::endl;
    }

    this->deleteLater();
    std::cout << "[CREATE GAME] CreateGame dialog marked for deletion" << std::endl;
}
