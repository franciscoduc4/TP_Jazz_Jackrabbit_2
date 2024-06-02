#include "scenespriteswidget.h"
#include <QVBoxLayout>
#include <QPainter>
#include <QKeyEvent>

#include "../Common/Config/ClientConfig.h"
#include "../sprite.h"

SceneSpritesWidget::SceneSpritesWidget(QWidget *parent)
    : QWidget{parent}, currentSpriteIndex(0)
{
    std::string spritesheetFilePath = ClientConfig::getEpisodeFile();
    QPixmap spritesheet(QString::fromStdString(spritesheetFilePath));

    std::vector<std::vector<int>> spritesData = ClientConfig::getEpisodesSprites();
    spritePositions = RectangularSprite::createSprites(spritesData);

    // Extract the sprites
    for (const RectangularSprite& sprite : spritePositions) {
        QPixmap extractedSprite = spritesheet.copy(sprite.get_x(), sprite.get_y(), sprite.get_width(), sprite.get_height());
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
