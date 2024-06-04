#ifndef SCENESPRITESWIDGET_H
#define SCENESPRITESWIDGET_H

#include <QKeyEvent>
#include <QPainter>
#include <QPixmap>
#include <vector>

#include "../../../Common/sprite.h"

class SceneSpritesWidget : public QWidget {
    Q_OBJECT

public:
    SceneSpritesWidget(QWidget* parent = nullptr, std::tuple<int, int, int> colourKey);
    size_t getCurrentSpriteIndex() const { return currentSpriteIndex; }

protected:
    void paintEvent(QPaintEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    std::vector<QPixmap> sprites;
    size_t currentSpriteIndex;
    std::vector<RectangularSprites> spritePositions;
    QColor colorKey;
};

#endif  // SCENESPRITESWIDGET_H
