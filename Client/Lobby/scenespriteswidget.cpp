#include "scenespriteswidget.h"
#include <QVBoxLayout>
#include <QPainter>
#include <QKeyEvent>

#include "../Common/Config/ClientConfig.h"

SceneSpritesWidget::SceneSpritesWidget(QWidget *parent)
    : QWidget{parent}, currentSpriteIndex(0)
{
    QPixmap spritesheet(ClientConfig::getEpisodesFiles());

    // Sprites: {x, y, ancho, alto}, x e y son las coordenadas del vértice superior izquierdo.
    spritePositions = {
        RectangularSprites::createSprites(ClientConfig::getEpisodesSprites());
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
