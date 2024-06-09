#include "characterselection.h"

#include "../../Common/Types/character.h"
#include "../../Common/Types/lobbyMessage.h"

#include "gamelist.h"
#include "ui_characterselection.h"
#include "waitingroom.h"

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
    /*
    this->msg.setCharacter(characterSelectionWidget->getCurrentCharacter());
    this->client.sendCharacterSelection(this->msg);
    if (this->msg.isCreateGame()) {
        WaitingRoom* wr = new WaitingRoom(this, this->controller, this->msg, this->clientJoinedGame);
        wr->show();
        this->close();
    } else if (this->msg.isJoinGame()) {
        GameList* gl = new GameList(this, this->controller, this->msg, this->clientJoinedGame);
        gl->show();
        this->close();
    } else {
        // Este caso no debería suceder.
        QMessageBox::warning(this, "Ocurrió un error inesperado.", "Error");
        return;
    }
    */
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
