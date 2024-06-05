#ifndef SCENESPRITESWIDGET_H
#define SCENESPRITESWIDGET_H

#include <QKeyEvent>
#include <QPainter>
#include <QPixmap>
#include <vector>

#include "../src/Common/sprite.h"

class SceneSpritesWidget : public QWidget {
    Q_OBJECT

public:
    SceneSpritesWidget(QWidget* parent = nullptr);
    size_t getCurrentSpriteIndex() const { return currentSpriteIndex; }

protected:
    void paintEvent(QPaintEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    std::vector<QPixmap> sprites;
    size_t currentSpriteIndex;
    std::vector<Sprite> spritePositions;
};

#endif // SCENESPRITESWIDGET_H
