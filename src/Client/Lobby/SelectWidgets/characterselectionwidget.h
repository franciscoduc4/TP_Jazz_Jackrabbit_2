#ifndef CHARACTERSELECTIONWIDGET_H
#define CHARACTERSELECTIONWIDGET_H

#include <QBitmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <utility>

#include "../../../Common/Config/ClientConfig.h"
#include "../../../Common/Types/character.h"
#include "../../../Common/sprite.h"

struct CharacterData {
    std::function<std::vector<Sprite>()> nameSpritesGetter;
    std::function<std::vector<Sprite>()> characterSpritesGetter;

    CharacterData(std::function<std::vector<Sprite>()> nameGetter,
                  std::function<std::vector<Sprite>()> characterGetter):
            nameSpritesGetter(std::move(nameGetter)), characterSpritesGetter(std::move(characterGetter)) {}
};

class CharacterSelectionWidget: public QWidget {
    Q_OBJECT

public:
    CharacterSelectionWidget(QWidget* parent, const std::tuple<int, int, int>& colourKey);
    static QPixmap spriteToPixmap(const Sprite& sprite);
    CharacterType getSelectedCharacter() const;
    void updateCharacter(int index);

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

private:
    QGraphicsView* nameAnimationView;
    QGraphicsView* characterAnimationView;
    std::vector<CharacterData> characters;
    int currentCharacterIndex;
    QColor colourKey;
};

#endif  // CHARACTERSELECTIONWIDGET_H
