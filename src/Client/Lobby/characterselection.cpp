#include "characterselection.h"

#include "../../Common/Types/character.h"
#include "../../Common/Types/lobbyMessage.h"

#include "gamelist.h"
#include "ui_characterselection.h"
#include "waitingroom.h"

#include <QMessageBox>

CharacterSelection::CharacterSelection(QWidget* parent, LobbyController& controller, LobbyMessage& msg,
                                       bool& clientJoinedGame):
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
}

CharacterSelection::~CharacterSelection() { delete ui; }

void CharacterSelection::on_btnChoose_clicked() {
    // this->msg.setCharacter(characterSelectionWidget->getCurrentCharacter());
    // this->controller.sendCharacterSelection(this->msg);
    this->hide();
    if (this->msg.getLobbyCmd() == Command::CREATE_GAME) {
        WaitingRoom wr(this, this->controller, this->msg, this->clientJoinedGame);
        wr.setModal(true);
        wr.exec();
        this->close();
    } else if (this->msg.getLobbyCmd() == Command::JOIN_GAME) {
        GameList gl(this, this->controller, this->msg, this->clientJoinedGame);
        gl.setModal(true);
        gl.exec();
        this->close();
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

    this->close();
}
