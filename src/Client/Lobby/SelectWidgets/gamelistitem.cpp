#include "gamelistitem.h"

GameListItem::GameListItem(const QString& gameName, int players, int totalPlayers, QWidget* parent)
        : QWidget{parent}
{
    gameNameLabel = new QLabel(gameName, this);
    playersLabel = new QLabel(QString("%1/%2").arg(players).arg(totalPlayers), this);
    joinButton = new QPushButton("Join", this);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(gameNameLabel);
    layout->addWidget(playersLabel);
    layout->addWidget(joinButton);

    connect(joinButton, &QPushButton::clicked, [this, gameName] {
        emit joinGame(gameName);
    });
}

QSize GameListItem::sizeHint() const {
    return QSize(200, 50); // Adjust this to your needs
}
