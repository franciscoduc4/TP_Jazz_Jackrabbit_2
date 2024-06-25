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
        clientJoinedGame(clientJoinedGame),
        recvQueue() {
    ui->setupUi(this);

    this->clientJoinedGame = true; // Al llegar acá y no poder volver atrás, se asume que el cliente se unió al juego

    connect(&updateTimer, &QTimer::timeout, this, &WaitingRoom::fetchUpdates);

    updateTimer.start(1000);

    GameInfo selected = this->controller.getSelectedGame();
    QString numPlayers = QString::number(selected.getCurrentPlayers());
    ui->numPlayers->setText(numPlayers);

    QString gameName = QString::fromStdString(this->msg.getGameName());
    ui->labelGameName->setText(gameName);
    std::cout << "[WAITING ROOM] Game name set: " << gameName.toStdString() << std::endl;

    QString maxPlayers = QString::number(this->msg.getMaxPlayers());
    ui->maxPlayers->setText(maxPlayers);

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

    QFile file(":/Lobby/Styles/waitingroom.qss");
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        ui->centralwidget->setStyleSheet(styleSheet);
    }

    ui->labelTitle->setAttribute(Qt::WA_TranslucentBackground);
    ui->labelGameName->setAttribute(Qt::WA_TranslucentBackground);
    ui->labelPlayers->setAttribute(Qt::WA_TranslucentBackground);
    ui->labelSlash->setAttribute(Qt::WA_TranslucentBackground);
    ui->numPlayers->setAttribute(Qt::WA_TranslucentBackground);
    ui->maxPlayers->setAttribute(Qt::WA_TranslucentBackground);

    connect(this, &WaitingRoom::numPlayersUpdated, this, &WaitingRoom::updateNumPlayers);
}

void WaitingRoom::fetchUpdates() {
    std::unique_ptr<DTO> updateDto;
    if (controller.hasGameUpdates(updateDto)) {
        std::cout << "[WAITING ROOM] Received update" << std::endl;
        int numPlayers;
        bool startGameReceived = false;
        auto* cmdDto = dynamic_cast<CommandDTO*>(updateDto.get());
        updateDto.release();
        std::unique_ptr<CommandDTO> cmdDtoPtr(cmdDto);
        std::tie(startGameReceived, numPlayers) = controller.processGameUpdate(cmdDtoPtr);
        emit numPlayersUpdated(startGameReceived, numPlayers);
    } else {
        std::cout << "[WAITING ROOM] No updates received" << std::endl;
    }
}

void WaitingRoom::updateNumPlayers(bool startGameReceived, int numPlayers) {
    ui->numPlayers->setText(QString::number(numPlayers));
    if (startGameReceived) {
        QCoreApplication::exit(0);
        return;
    }
}

WaitingRoom::~WaitingRoom() {
    delete ui;
}