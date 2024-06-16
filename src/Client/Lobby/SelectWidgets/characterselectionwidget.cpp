#include "characterselectionwidget.h"

CharacterSelectionWidget::CharacterSelectionWidget(QWidget* parent,
                                                   const std::tuple<int, int, int>& colourKey):
        QWidget{parent},
        currentCharacterIndex(0),
        colourKey(std::get<0>(colourKey), std::get<1>(colourKey), std::get<2>(colourKey)) {
    std::cout << "[CHARACTER SELECTION] Initializing CharacterSelectionWidget" << std::endl;

    auto* layout = new QVBoxLayout(this);
    nameAnimationView = new QGraphicsView(this);
    characterAnimationView = new QGraphicsView(this);
    layout->addWidget(nameAnimationView);
    layout->addWidget(characterAnimationView);

    layout->setStretchFactor(nameAnimationView, 1);
    layout->setStretchFactor(characterAnimationView, 9);


    characters = {
            CharacterData(
                    []() {
                        return Sprite::createSpritesWithSpritesheetAndColourKey(ClientConfig::getJazzSelectNameSprites(),
                                                                                ClientConfig::getCharacterSelectFile(),
                                                                                ClientConfig::getCharacterSelectColourKey());
                    },
                    []() { return Sprite::createSpritesWithSpritesheetAndColourKey(ClientConfig::getJazzSelectSprites(),
                                                                                   ClientConfig::getCharacterSelectFile(),
                                                                                   ClientConfig::getCharacterSelectColourKey()); }),
            CharacterData(
                    []() {
                        return Sprite::createSpritesWithSpritesheetAndColourKey(ClientConfig::getSpazSelectNameSprites(),
                                                                                ClientConfig::getCharacterSelectFile(),
                                                                                ClientConfig::getCharacterSelectColourKey());
                    },
                    []() { return Sprite::createSpritesWithSpritesheetAndColourKey(ClientConfig::getSpazSelectSprites(),
                                                                                   ClientConfig::getCharacterSelectFile(),
                                                                                   ClientConfig::getCharacterSelectColourKey()); }),
            CharacterData(
                    []() {
                        return Sprite::createSpritesWithSpritesheetAndColourKey(ClientConfig::getLoriSelectNameSprites(),
                                                                                ClientConfig::getCharacterSelectFile(),
                                                                                ClientConfig::getCharacterSelectColourKey());
                    },
                    []() { return Sprite::createSpritesWithSpritesheetAndColourKey(ClientConfig::getLoriSelectSprites(),
                                                                                   ClientConfig::getCharacterSelectFile(),
                                                                                   ClientConfig::getCharacterSelectColourKey()); })};

    std::cout << "[CHARACTER SELECTION] Character data initialized" << std::endl;

    updateCharacter(currentCharacterIndex);
}

void CharacterSelectionWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    if (!characters.empty()) {
        const auto& characterSprites = characters[currentCharacterIndex].characterSpritesGetter();
        if (!characterSprites.empty()) {
            const auto& sprite = characterSprites[0];
            QPixmap pixmap = CharacterSelectionWidget::spriteToPixmap(sprite);
            painter.drawPixmap(0, 0, pixmap);
        }
    }

    QWidget::paintEvent(event);
}

void CharacterSelectionWidget::updateCharacter(int index) {
    std::cout << "[CHARACTER SELECTION] Updating character to index: " << index << std::endl;
    currentCharacterIndex = index;
    auto nameSprites = characters[index].nameSpritesGetter();
    auto characterSprites = characters[index].characterSpritesGetter();

    auto* nameScene = new QGraphicsScene(this);
    auto* characterScene = new QGraphicsScene(this);

    for (const auto& sprite: nameSprites) {
        QPixmap pixmap = CharacterSelectionWidget::spriteToPixmap(sprite);
        auto* item = new QGraphicsPixmapItem(pixmap);
        nameScene->addItem(item);
        std::cout << "[CHARACTER SELECTION] Added name sprite to scene" << std::endl;
    }

    for (const auto& sprite: characterSprites) {
        QPixmap pixmap = CharacterSelectionWidget::spriteToPixmap(sprite);
        auto* item = new QGraphicsPixmapItem(pixmap);
        characterScene->addItem(item);
        std::cout << "[CHARACTER SELECTION] Added character sprite to scene" << std::endl;
    }

    nameAnimationView->setScene(nameScene);
    characterAnimationView->setScene(characterScene);
    std::cout << "[CHARACTER SELECTION] Scenes updated" << std::endl;
}

QPixmap CharacterSelectionWidget::spriteToPixmap(const Sprite& sprite) {
    std::cout << "[CHARACTER SELECTION] Converting sprite to pixmap" << std::endl;
    QString spriteSheetPath = ":/" + QString::fromStdString(sprite.getSpriteSheetPath());

    if (!QFile::exists(spriteSheetPath)) {
        std::cerr << "[CHARACTER SELECTION] Sprite sheet file does not exist: " << spriteSheetPath.toStdString() << std::endl;
        return {};
    }

    QPixmap spriteSheet(spriteSheetPath);

    if (spriteSheet.isNull()) {
        std::cerr << "[CHARACTER SELECTION] Sprite sheet pixmap is null" << std::endl;
        return {};
    }
    std::vector<std::pair<int, int>> vertices = sprite.getVertices();

    int minX = std::min_element(vertices.begin(), vertices.end(), [](const auto& a, const auto& b) {
                   return a.first < b.first;
               })->first;
    int minY = std::min_element(vertices.begin(), vertices.end(), [](const auto& a, const auto& b) {
                   return a.second < b.second;
               })->second;
    int maxX = std::max_element(vertices.begin(), vertices.end(), [](const auto& a, const auto& b) {
                   return a.first < b.first;
               })->first;
    int maxY = std::max_element(vertices.begin(), vertices.end(), [](const auto& a, const auto& b) {
                   return a.second < b.second;
               })->second;

    QPixmap spritePixmap = spriteSheet.copy(minX, minY, maxX - minX, maxY - minY);
    std::cout << "[CHARACTER SELECTION] Sprite copied to pixmap" << std::endl;

    std::tuple<int, int, int> spriteColourKey = sprite.getColourKey();
    QColor colourKey(std::get<0>(spriteColourKey), std::get<1>(spriteColourKey), std::get<2>(spriteColourKey));
    QBitmap mask = spritePixmap.createMaskFromColor(colourKey, Qt::MaskInColor);

    spritePixmap.setMask(mask);

    std::cout << "[CHARACTER SELECTION] Pixmap mask set" << std::endl;

    return spritePixmap;
}

void CharacterSelectionWidget::keyPressEvent(QKeyEvent* event) {
    std::cout << "[CHARACTER SELECTION] Key press event: " << event->key() << std::endl;
    if (event->key() == Qt::Key_Left) {
        if (currentCharacterIndex > 0) {
            updateCharacter(currentCharacterIndex - 1);
            std::cout << "[CHARACTER SELECTION] Character index decreased to "
                      << currentCharacterIndex << std::endl;
        }
    } else if (event->key() == Qt::Key_Right) {
        if (currentCharacterIndex < characters.size() - 1) {
            updateCharacter(currentCharacterIndex + 1);
            std::cout << "[CHARACTER SELECTION] Character index increased to "
                      << currentCharacterIndex << std::endl;
        }
    }

    update();
}

CharacterType CharacterSelectionWidget::getSelectedCharacter() const {
    std::cout << "[CHARACTER SELECTION] Getting selected character type for index: "
              << currentCharacterIndex << std::endl;
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
