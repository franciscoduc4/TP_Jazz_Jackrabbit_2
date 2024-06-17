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

    clientJoinedGame = true; // Al llegar acá y no poder volver atrás, se asume que el cliente se unió al juego

    // Se crea un hilo para que el cliente pueda recibir actualizaciones de la cantidad de jugadores en la sala
    updateThread = QThread::create([this] { this->pollForUpdates(); });
    connect(this, &WaitingRoom::destroyed, updateThread, &QThread::quit);
    updateThread->start();

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

    this->msg.setLobbyCmd(Command::START_GAME);
    this->controller.sendRequest(this->msg);
    this->controller.recvStartGame();
}

void WaitingRoom::pollForUpdates() {
    while (true) {
        QMutexLocker locker(&mutex);
        std::unique_ptr<DTO> updateDto;
        if (controller.hasGameUpdates(updateDto)) {
            int numPlayers = controller.processGameUpdate(updateDto);
            emit numPlayersUpdated(numPlayers);
        } else {
            condition.wait(&mutex);
        }
    }
}

void WaitingRoom::updateNumPlayers(int numPlayers) {
    ui->numPlayers->setText(QString::number(numPlayers));
}

WaitingRoom::~WaitingRoom() {
    updateThread->quit();
    updateThread->wait();
    delete ui;
}
