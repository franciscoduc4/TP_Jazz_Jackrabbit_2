#include "waitingroom.h"

#include <QFile>
#include <iostream>

#include "ui_waitingroom.h"

WaitingRoom::WaitingRoom(QWidget* parent, LobbyController& controller, LobbyMessage& msg,
                         bool& clientJoinedGame):
        QDialog(parent),
        ui(new Ui::WaitingRoom),
        controller(controller),
        msg(msg),
        clientJoinedGame(clientJoinedGame) {
    ui->setupUi(this);
    std::cout << "[WAITING ROOM] UI setup completed" << std::endl;

    std::cout << "[WAITING ROOM] Initializing WaitingRoom" << std::endl;
    QString gameName = QString::fromStdString(this->msg.getGameName());
    ui->labelGameName->setText(gameName);
    std::cout << "[WAITING ROOM] Game name set: " << gameName.toStdString() << std::endl;

    if (this->msg.getLobbyCmd() == Command::CREATE_GAME) {
        QString maxPlayers = QString::number(this->msg.getMaxPlayers());
        ui->maxPlayers->setText(maxPlayers);
        std::cout << "[WAITING ROOM] Max players set: " << maxPlayers.toStdString() << std::endl;
    }

    QFont font = ui->labelGameName->font();
    QFontMetrics fm(font);
    int pointSize = font.pointSize();

    int minSize = 12;
    for (int i = pointSize; i >= minSize; --i) {
        font.setPointSize(i);
        int textWidth = fm.horizontalAdvance(ui->labelGameName->text());

        if (textWidth <= ui->labelGameName->width()) {
            break;
        }
    }

    ui->labelGameName->setFont(font);
    std::cout << "[WAITING ROOM] Adjusted font size for game name" << std::endl;

    QFile file(":/Lobby/Styles/waitingroom.qss");
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        ui->centralwidget->setStyleSheet(styleSheet);
        std::cout << "[WAITING ROOM] Applied stylesheet" << std::endl;
    } else {
        std::cerr << "[WAITING ROOM] Failed to open stylesheet" << std::endl;
    }

    ui->labelTitle->setAttribute(Qt::WA_TranslucentBackground);
    ui->labelGameName->setAttribute(Qt::WA_TranslucentBackground);
    ui->labelPlayers->setAttribute(Qt::WA_TranslucentBackground);
    ui->labelSlash->setAttribute(Qt::WA_TranslucentBackground);
    ui->numPlayers->setAttribute(Qt::WA_TranslucentBackground);
    ui->maxPlayers->setAttribute(Qt::WA_TranslucentBackground);
    std::cout << "[WAITING ROOM] Set translucent background for labels" << std::endl;


    this->msg.setLobbyCmd(Command::START_GAME);
    std::cout << "[WAITING ROOM] Lobby command set to START_GAME" << std::endl;
    this->controller.sendRequest(this->msg);
    std::cout << "[WAITING ROOM] Sent request to controller" << std::endl;
    this->controller.recvStartGame();
    std::cout << "[WAITING ROOM] Received start game command from controller" << std::endl;
    this->hide();
}

WaitingRoom::~WaitingRoom() {
    delete ui;
    std::cout << "[WAITING ROOM] Destructor called, UI deleted" << std::endl;
}
