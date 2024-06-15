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
    QVBoxLayout* layout = new QVBoxLayout(ui->widgetCharacters);
    layout->addWidget(characterSelectionWidget);

    QFile file(":/Lobby/Styles/characterselection.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    ui->centralwidget->setStyleSheet(styleSheet);
    ui->labelTitle->setAttribute(Qt::WA_TranslucentBackground);
}

CharacterSelection::~CharacterSelection() {
    delete characterSelectionWidget;
    delete ui;
}

void CharacterSelection::on_btnChoose_clicked() {
    // this->msg.setCharacter(characterSelectionWidget->getSelectedCharacter());
    this->controller.sendRequest(this->msg);
    this->hide();
    if (this->msg.getLobbyCmd() == Command::CREATE_GAME) {
        auto wr = new WaitingRoom(this, this->controller, this->msg, this->clientJoinedGame);
        wr->show();
    } else if (this->msg.getLobbyCmd() == Command::JOIN_GAME) {
        this->msg.setLobbyCmd(Command::GAMES_LIST);
        this->controller.sendRequest(this->msg);
        auto gl = new GameList(this, this->controller, this->msg, this->clientJoinedGame);
        gl->show();
    } else {
        // Este caso no debería suceder.
        QMessageBox::warning(this, "Error", "Ocurrió un error inesperado.");
        return;
    }
}


void CharacterSelection::on_btnBack_clicked() {
    this->msg.setCharacter(CharacterType::INVALID);

    this->hide();

    QWidget* parent = this->parentWidget();
    if (parent) {
        parent->show();
    }

    this->deleteLater();
}
