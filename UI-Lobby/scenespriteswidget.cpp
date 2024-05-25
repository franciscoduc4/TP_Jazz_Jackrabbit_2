#include "scenespriteswidget.h"
#include <QVBoxLayout>
#include <QPainter>
#include <QKeyEvent>

SceneSpritesWidget::SceneSpritesWidget(QWidget *parent)
    : QWidget{parent}, currentSpriteIndex(0)
{
    QPixmap spritesheet("path_to_your_spritesheet.png");  // Replace with the path to your spritesheet

    // Sprites: {x, y, ancho, alto}, x e y son las coordenadas del vértice superior izquierdo.
    spritePositions = {
        {9, 9, 495, 354},
        {505, 9, 496, 354},
        {1002, 9, 531, 354},
        {1534, 9, 469, 354},
        {9, 367, 445, 353},
        {455, 367, 513, 353},
        {969, 367, 525, 353},
        {1495, 367, 498, 353}
    };

    // Extract the sprites
    for (const Sprite& sprite : spritePositions) {
        QPixmap extractedSprite = spritesheet.copy(sprite.x, sprite.y, sprite.width, sprite.height);
        sprites.push_back(extractedSprite);
    }

    setFocusPolicy(Qt::StrongFocus);
}

void SceneSpritesWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, sprites[currentSpriteIndex]);
}

void SceneSpritesWidget::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Left) {
        // Go to the previous sprite
        if (currentSpriteIndex > 0) {
            --currentSpriteIndex;
        }
    } else if (event->key() == Qt::Key_Right) {
        // Go to the next sprite
        if (currentSpriteIndex < sprites.size() - 1) {
            ++currentSpriteIndex;
        }
    }

    // Redraw the widget with the new sprite
    update();
}
