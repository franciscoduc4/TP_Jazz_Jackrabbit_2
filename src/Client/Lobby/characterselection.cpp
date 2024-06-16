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
    std::cout << "[CHARACTER SELECTION] UI setup completed" << std::endl;

    QVBoxLayout* layout = new QVBoxLayout(ui->widgetCharacters);
    layout->addWidget(characterSelectionWidget);
    std::cout << "[CHARACTER SELECTION] CharacterSelectionWidget added to layout" << std::endl;

    QFile file(":/Lobby/Styles/characterselection.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    ui->centralwidget->setStyleSheet(styleSheet);
    ui->labelTitle->setAttribute(Qt::WA_TranslucentBackground);
    std::cout << "[CHARACTER SELECTION] Stylesheet applied" << std::endl;
}

// CharacterSelection::CharacterSelection(QWidget* parent, LobbyController& controller,
//                                        LobbyMessage& msg, bool& clientJoinedGame):
//         QDialog(parent),
//         ui(new Ui::CharacterSelection),
//         controller(controller),
//         msg(msg),
//         clientJoinedGame(clientJoinedGame),
//         buttonGroup(new QButtonGroup(this)) {
//     ui->setupUi(this);
//     std::cout << "[CHARACTER SELECTION] UI setup completed" << std::endl;

//     // Add the characters to the button group
//     QStringList characters = {"Jazz", "Spaz", "Lori"};

//     if (!ui->widgetCharacters->layout()) {
//         ui->widgetCharacters->setLayout(new QVBoxLayout());
//     }

//     for (int i = 0; i < characters.size(); ++i) {
//         auto* radioButton = new QRadioButton(characters[i]);
//         buttonGroup->addButton(radioButton, i);
//         ui->widgetCharacters->layout()->addWidget(radioButton);
//         std::cout << "[CHARACTER SELECTION] Added character: " << characters[i].toStdString()
//                   << " with ID: " << i << std::endl;
//     }

//     QFile file(":/Lobby/Styles/characterselection.qss");
//     file.open(QFile::ReadOnly);
//     QString styleSheet = QLatin1String(file.readAll());

//     ui->centralwidget->setStyleSheet(styleSheet);
//     ui->labelTitle->setAttribute(Qt::WA_TranslucentBackground);
//     std::cout << "[CHARACTER SELECTION] Stylesheet applied" << std::endl;
// }

CharacterSelection::~CharacterSelection() {
    // delete characterSelectionWidget;
    delete ui;
    std::cout << "[CHARACTER SELECTION] Destructor called, UI deleted" << std::endl;
}

void CharacterSelection::on_btnChoose_clicked() {
    this->msg.setCharacter(characterSelectionWidget->getSelectedCharacter());
    this->controller.sendRequest(this->msg);
    std::cout << "[CHARACTER SELECTION] Request sent to controller" << std::endl;

    this->hide();
    if (this->msg.getLobbyCmd() == Command::CREATE_GAME) {
        this->msg.setGameId(this->controller.recvCreateGame());
        auto wr = new WaitingRoom(this, this->controller, this->msg, this->clientJoinedGame);
        wr->show();
        std::cout << "[CHARACTER SELECTION] WaitingRoom dialog shown" << std::endl;
    } else if (this->msg.getLobbyCmd() == Command::JOIN_GAME) {
        this->msg.setLobbyCmd(Command::GAMES_LIST);
        auto gl = new GameList(this, this->controller, this->msg, this->clientJoinedGame);
        gl->show();
        std::cout << "[CHARACTER SELECTION] GameList dialog shown" << std::endl;
    } else {
        std::cout << "[CHARACTER SELECTION] Unexpected command" << std::endl;
        QMessageBox::warning(this, "Error", "Ocurrió un error inesperado.");
        return;
    }
}

// void CharacterSelection::on_btnChoose_clicked() {
//     std::cout << "[CHARACTER SELECTION] Choose button clicked" << std::endl;
//     if (buttonGroup->checkedId() == -1) {
//         QMessageBox::information(this, "Error", "Seleccione un personaje para continuar.");
//         std::cout << "[CHARACTER SELECTION] No character selected, showing error message"
//                   << std::endl;
//     } else {
//         int selectedCharacterId = buttonGroup->checkedId();
//         CharacterType selectedCharacter;
//         switch (selectedCharacterId) {
//             case 0:
//                 selectedCharacter = CharacterType::JAZZ;
//                 break;
//             case 1:
//                 selectedCharacter = CharacterType::SPAZ;
//                 break;
//             case 2:
//                 selectedCharacter = CharacterType::LORI;
//                 break;
//             default:
//                 selectedCharacter = CharacterType::INVALID;
//         }

//         this->msg.setCharacter(selectedCharacter);
//         std::cout << "[CHARACTER SELECTION] Character selected with ID: " << selectedCharacterId
//                   << std::endl;
//         this->controller.sendRequest(this->msg);
//         std::cout << "[CHARACTER SELECTION] Request sent to controller" << std::endl;

//         this->hide();
//         if (this->msg.getLobbyCmd() == Command::CREATE_GAME) {
//             this->msg.setGameId(this->controller.recvCreateGame());
//             auto wr = new WaitingRoom(this, this->controller, this->msg, this->clientJoinedGame);
//             wr->show();
//             std::cout << "[CHARACTER SELECTION] WaitingRoom dialog shown" << std::endl;
//         } else if (this->msg.getLobbyCmd() == Command::JOIN_GAME) {
//             this->msg.setLobbyCmd(Command::GAMES_LIST);
//             this->controller.sendRequest(this->msg);
//             auto gl = new GameList(this, this->controller, this->msg, this->clientJoinedGame);
//             gl->show();
//             std::cout << "[CHARACTER SELECTION] GameList dialog shown" << std::endl;
//         } else {
//             std::cout << "[CHARACTER SELECTION] Unexpected command" << std::endl;
//             QMessageBox::warning(this, "Error", "Ocurrió un error inesperado.");
//             return;
//         }
//     }
// }

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
