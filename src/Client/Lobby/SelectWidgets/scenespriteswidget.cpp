#include "scenespriteswidget.h"

#include <QKeyEvent>
#include <QPainter>
#include <QBitmap>
#include <QVBoxLayout>

#include "../../../Common/Config/ClientConfig.h"

SceneSpritesWidget::SceneSpritesWidget(QWidget *parent, const std::tuple<int, int, int>& colourKey)
    : QWidget{parent}, currentSpriteIndex(0), colourKey(std::get<0>(colourKey), std::get<1>(colourKey), std::get<2>(colourKey))
{
    QPixmap spritesheet(QString::fromStdString(ClientConfig::getEpisodeFile()));

    // RectangularSprite: {x, y, ancho, alto}, x e y son las coordenadas del vértice superior izquierdo.
    spritePositions = {
        RectangularSprite::createSprites(ClientConfig::getEpisodesSprites())
    };

    for (const RectangularSprite& sprite : spritePositions) {
        QPixmap extractedSprite = spritesheet.copy(sprite.getX(), sprite.getY(), sprite.getWidth(), sprite.getHeight());
        sprites.push_back(extractedSprite);
    }

    setFocusPolicy(Qt::StrongFocus);
}

void SceneSpritesWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    QPixmap sprite = sprites[currentSpriteIndex];
    sprite.setMask(sprite.createMaskFromColor(this->colourKey, Qt::MaskInColor));
    painter.drawPixmap(0, 0, sprite);
}

void SceneSpritesWidget::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Left) {
        if (currentSpriteIndex > 0) {
            --currentSpriteIndex;
        } else if (currentSpriteIndex == 0) {
            currentSpriteIndex = sprites.size() - 1;
        }
    } else if (event->key() == Qt::Key_Right) {
        if (currentSpriteIndex < sprites.size() - 1) {
            ++currentSpriteIndex;
        } else if (currentSpriteIndex == sprites.size() - 1) {
            currentSpriteIndex = 0;
        }
    }

    update();
}
