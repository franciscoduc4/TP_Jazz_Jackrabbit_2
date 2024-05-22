#ifndef GAMELIST_H
#define GAMELIST_H

#include <QMainWindow>

namespace Ui {
class GameList;
}

class GameList : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameList(QWidget *parent = nullptr);
    ~GameList();

private:
    Ui::GameList *ui;
};

#endif // GAMELIST_H
