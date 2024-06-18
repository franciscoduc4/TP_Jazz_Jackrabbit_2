#include "characterselection.h"

#include <QMessageBox>

#include "../../Common/Types/character.h"
#include "../../Common/Types/lobbyMessage.h"

#include "gamelist.h"
#include "ui_characterselection.h"
#include "waitingroom.h"

CharacterSelection::CharacterSelection(QWidget* parent, LobbyController& controller,
                                       LobbyMessage& msg, bool& clientJoinedGame):
        QDialog(parent),
        ui(new Ui::CharacterSelection),
        controller(controller),
        msg(msg),
        clientJoinedGame(clientJoinedGame),
        characterSelectionWidget(
                new CharacterSelectionWidget(this, ClientConfig::getCharacterSelectColourKey())) {
    ui->setupUi(this);

    auto* layout = new QVBoxLayout(ui->widgetCharacters);
    layout->addWidget(characterSelectionWidget);
    std::cout << "[CHARACTER SELECTION] CharacterSelectionWidget added to layout" << std::endl;

    QFile file(":/Lobby/Styles/characterselection.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    ui->centralwidget->setStyleSheet(styleSheet);
    ui->labelTitle->setAttribute(Qt::WA_TranslucentBackground);
    std::cout << "[CHARACTER SELECTION] Stylesheet applied" << std::endl;
}

CharacterSelection::~CharacterSelection() { delete ui; }

void CharacterSelection::on_btnChoose_clicked() {
    this->msg.setCharacter(characterSelectionWidget->getSelectedCharacter());
    std::cout << "[Character Selection] Selected character: "
              << static_cast<int>(this->msg.getCharacter()) << std::endl;

    this->hide();

    if (this->msg.getLobbyCmd() == Command::CREATE_GAME) {
        std::cout << "[CHARACTER SELECTION] Creating game, requesting game ID" << std::endl;
        // Send Request with CREATE_GAME
        this->controller.sendRequest(this->msg);
        // Receive Create Game
        std::pair<bool, GameInfo> cgAck = this->controller.recvResponse();
        // Receive Game Update
        std::pair<bool, GameInfo> guAck = this->controller.recvResponse();

        if (!cgAck.first || !guAck.first) {
            QMessageBox::warning(this, "Error", "No se pudo crear la partida.");
            QCoreApplication::exit(37);
            return;
        }

        this->msg.setGameId(cgAck.second.getGameId());

        this->clientJoinedGame = true;

        if (this->controller.canStartGame()) {
            this->msg.setLobbyCmd(Command::START_GAME);
            this->controller.startGame(this->msg);
            std::pair<bool, GameInfo> sgAck = this->controller.recvResponse();
            if (!sgAck.first) {
                QMessageBox::warning(this, "Error", "No se pudo iniciar la partida.");
                QCoreApplication::exit(37);
                return;
            }
            QCoreApplication::exit(0);
            return;
        }

        auto wr = new WaitingRoom(this, this->controller, this->msg, this->clientJoinedGame);
        wr->show();

        std::cout << "[CHARACTER SELECTION] WaitingRoom dialog shown" << std::endl;
    } else if (this->msg.getLobbyCmd() == Command::JOIN_GAME) {
        std::cout << "[CHARACTER SELECTION] Joining game, requesting game list" << std::endl;
        this->msg.setLobbyCmd(Command::GAMES_LIST);
        auto gl = new GameList(this, this->controller, this->msg, this->clientJoinedGame);
        gl->show();
        gl->updateGameList();
        std::cout << "[CHARACTER SELECTION] GameList dialog shown" << std::endl;
    } else {
        std::cout << "[CHARACTER SELECTION] Unexpected command" << std::endl;
        QMessageBox::warning(this, "Error", "Ocurrió un error inesperado.");
        return;
    }
}

void CharacterSelection::on_btnBack_clicked() {
    std::cout << "[CHARACTER SELECTION] Back button clicked" << std::endl;
    this->msg.setCharacter(CharacterType::INVALID);
    std::cout << "[CHARACTER SELECTION] Character set to INVALID in message" << std::endl;

    this->hide();
    std::cout << "[CHARACTER SELECTION] Dialog hidden" << std::endl;

    QWidget* parent = this->parentWidget();
    if (parent) {
        parent->show();
        std::cout << "[CHARACTER SELECTION] Parent widget shown" << std::endl;
    }

    this->deleteLater();
    std::cout << "[CHARACTER SELECTION] Dialog marked for deletion" << std::endl;
}

void CharacterSelection::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        on_btnChoose_clicked();
    } else {
        QDialog::keyPressEvent(event);
    }
}
