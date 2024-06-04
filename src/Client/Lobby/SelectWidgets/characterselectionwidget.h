#ifndef CHARACTERSELECTIONWIDGET_H
#define CHARACTERSELECTIONWIDGET_H

#include <QKeyEvent>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "../../../Common/Config/ClientConfig.h"
#include "../../../Common/sprite.h"

struct CharacterData {
    std::function<std::vector<Sprite>()> nameSpritesGetter;
    std::function<std::vector<Sprite>()> characterSpritesGetter;
};

class CharacterSelectionWidget : public QWidget {
    Q_OBJECT

public:
    CharacterSelectionWidget(QWidget* parent, std::tuple<int, int, int> colourKey);
    void updateCharacter(int index);

protected:
    void keyPressEvent(QKeyEvent* event) override;

private:
    QGraphicsView* nameAnimationView;
    QGraphicsView* characterAnimationView;
    std::vector<CharacterData> characters;
    int currentCharacterIndex;
    QColor colourKey;
};

#endif  // CHARACTERSELECTIONWIDGET_H
