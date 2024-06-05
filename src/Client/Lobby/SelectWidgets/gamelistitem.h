#ifndef GAMELISTITEM_H
#define GAMELISTITEM_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>

class GameListItem : public QWidget {
    Q_OBJECT

public:
    GameListItem(const QString& gameName, int players, int totalPlayers, QWidget* parent = nullptr);

    QSize sizeHint() const override;

signals:
    void joinGame(const QString& gameName);

private:
    QLabel* gameNameLabel;
    QLabel* playersLabel;
    QPushButton* joinButton;
};

#endif  // GAMELISTITEM_H
