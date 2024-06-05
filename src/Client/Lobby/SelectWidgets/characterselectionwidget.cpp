#include "characterselectionwidget.h"

#include "../../../Common/Config/ClientConfig.h"
#include "../../../Common/Types/character.h"

CharacterSelectionWidget::CharacterSelectionWidget(QWidget* parent, const std::tuple<int, int, int>& colourKey)
        : QWidget{parent}, currentCharacterIndex(0), colourKey(std::get<0>(colourKey), std::get<1>(colourKey), std::get<2>(colourKey))
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    nameAnimationView = new QGraphicsView(this);
    characterAnimationView = new QGraphicsView(this);
    layout->addWidget(nameAnimationView);
    layout->addWidget(characterAnimationView);

    characters = {
        CharacterData([](){ return Sprite::createSprites(ClientConfig::getJazzSelectNameSprites()); }, [](){ return Sprite::createSprites(ClientConfig::getJazzSelectSprites()); }),
        CharacterData([](){ return Sprite::createSprites(ClientConfig::getSpazSelectNameSprites()); }, [](){ return Sprite::createSprites(ClientConfig::getSpazSelectSprites()); }),
        CharacterData([](){ return Sprite::createSprites(ClientConfig::getLoriSelectNameSprites()); }, [](){ return Sprite::createSprites(ClientConfig::getLoriSelectSprites()); })
};

    updateCharacter(currentCharacterIndex);
}

void CharacterSelectionWidget::updateCharacter(int index) {
    currentCharacterIndex = index;
    auto nameSprites = characters[index].nameSpritesGetter();
    auto characterSprites = characters[index].characterSpritesGetter();

    QGraphicsScene* nameScene = new QGraphicsScene(this);
    QGraphicsScene* characterScene = new QGraphicsScene(this);

    for (const auto& sprite : nameSprites) {
        QPixmap pixmap = this->spriteToPixmap(sprite);
        QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pixmap);
        nameScene->addItem(item);
    }

    for (const auto& sprite : characterSprites) {
        QPixmap pixmap = this->spriteToPixmap(sprite);
        QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pixmap);
        characterScene->addItem(item);
    }

    nameAnimationView->setScene(nameScene);
    characterAnimationView->setScene(characterScene);
}

QPixmap CharacterSelectionWidget::spriteToPixmap(const Sprite& sprite) {

    QPixmap spriteSheet(QString::fromStdString(sprite.getSpriteSheetPath()));

    auto vertices = sprite.getVertices();

    int minX = std::min_element(vertices.begin(), vertices.end(), [](const auto& a, const auto& b) { return a.first < b.first; })->first;
    int minY = std::min_element(vertices.begin(), vertices.end(), [](const auto& a, const auto& b) { return a.second < b.second; })->second;
    int maxX = std::max_element(vertices.begin(), vertices.end(), [](const auto& a, const auto& b) { return a.first < b.first; })->first;
    int maxY = std::max_element(vertices.begin(), vertices.end(), [](const auto& a, const auto& b) { return a.second < b.second; })->second;

    QPixmap spritePixmap = spriteSheet.copy(minX, minY, maxX - minX, maxY - minY);

    QBitmap mask(spritePixmap.size());

    QPainter painter(&mask);
    painter.fillRect(mask.rect(), Qt::color0);

    QVector<QPoint> points;
    std::transform(vertices.begin(), vertices.end(), std::back_inserter(points),
                   [minX, minY](const std::pair<int, int>& vertex) {
                       return QPoint(vertex.first - minX, vertex.second - minY);
                   });

    painter.setBrush(Qt::color1);
    painter.drawPolygon(points.data(), points.size());

    spritePixmap.setMask(mask);

    return spritePixmap;
}

void CharacterSelectionWidget::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Left) {
        if (currentCharacterIndex > 0) {
            updateCharacter(currentCharacterIndex - 1);
        }
    } else if (event->key() == Qt::Key_Right) {
        if (currentCharacterIndex < characters.size() - 1) {
            updateCharacter(currentCharacterIndex + 1);
        }
    }

    update();
}


CharacterType CharacterSelectionWidget::getSelectedCharacter() const {
    switch (currentCharacterIndex) {
        case 0:
            return CharacterType::JAZZ;
        case 1:
            return CharacterType::SPAZ;
        case 2:
            return CharacterType::LORI;
        default:
            throw std::runtime_error("Invalid character index");
    }
}
