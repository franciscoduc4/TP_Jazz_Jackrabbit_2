#include "characterselectionwidget.h"

CharacterSelectionWidget::CharacterSelectionWidget(QWidget* parent,
                                                   const std::tuple<int, int, int>& colourKey):
        QWidget{parent},
        currentCharacterIndex(0),
        colourKey(std::get<0>(colourKey), std::get<1>(colourKey), std::get<2>(colourKey)) {
    setFocusPolicy(Qt::StrongFocus);
    // Create a new QHBoxLayout as the main layout
    auto* mainLayout = new QHBoxLayout(this);

    // Initialize buttons
    leftButton = new QPushButton(this);
    rightButton = new QPushButton(this);

    std::string path = ClientConfig::getInterfaceFontFile();
    if (path.substr(0, 3) == "../") {
        path = path.substr(3);
    }
    QString fontSpritesheet = ":/" + QString::fromStdString(path);
    QPixmap spriteSheet(fontSpritesheet);

    if (spriteSheet.isNull()) {
        throw std::runtime_error("Failed to load sprite sheet");
    }
    RectangularSprite leftBtnSprite = RectangularSprite(ClientConfig::getLessThan());
    std::cout << "Left button sprite: " << leftBtnSprite.getX() << ", " << leftBtnSprite.getY() << ", "
              << leftBtnSprite.getWidth() << ", " << leftBtnSprite.getHeight() << std::endl;
    QRect leftRect(leftBtnSprite.getX(), leftBtnSprite.getY(), leftBtnSprite.getWidth(), leftBtnSprite.getHeight());
    QPixmap leftButtonPixmap = spriteSheet.copy(leftRect);
    QIcon leftButtonIcon(leftButtonPixmap);
    leftButton->setIcon(leftButtonIcon);

    RectangularSprite rightBtnSprite = RectangularSprite(ClientConfig::getGreaterThan());
    QRect rightRect(rightBtnSprite.getX(), rightBtnSprite.getY(), rightBtnSprite.getWidth(), rightBtnSprite.getHeight());
    QPixmap rightButtonPixmap = spriteSheet.copy(rightRect);
    QIcon rightButtonIcon(rightButtonPixmap);
    rightButton->setIcon(rightButtonIcon);

    // Set font for the buttons
    QFont buttonFont("Jazz Jackrabbit 2", 30);
    leftButton->setFont(buttonFont);
    rightButton->setFont(buttonFont);

    // Add buttons to the main layout with stretch factors for width
    mainLayout->addWidget(leftButton, 1); // 5% of width

    // Add stretch before QVBoxLayout
    mainLayout->addStretch(1); // Adjust this value as needed

    // Create a QVBoxLayout for the views
    auto* viewLayout = new QVBoxLayout();
    nameAnimationView = new QGraphicsView(this);
    characterAnimationView = new QGraphicsView(this);
    viewLayout->addWidget(nameAnimationView);
    viewLayout->addWidget(characterAnimationView);

    // Set stretch factors for height
    viewLayout->setStretchFactor(nameAnimationView, 1); // 10% of height
    viewLayout->setStretchFactor(characterAnimationView, 9); // 90% of height

    // Add the view layout to the main layout
    mainLayout->addLayout(viewLayout, 18); // 90% of width

    // Add stretch after QVBoxLayout
    mainLayout->addStretch(1); // Adjust this value as needed

    mainLayout->addWidget(rightButton, 1); // 5% of width

    // Set the main layout on the widget
    setLayout(mainLayout);


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


    // Initialize timers
    nameAnimationTimer = new QTimer(this);
    characterAnimationTimer = new QTimer(this);

    // Connect timers to slots
    connect(nameAnimationTimer, &QTimer::timeout, this, &CharacterSelectionWidget::updateNameAnimation);
    connect(characterAnimationTimer, &QTimer::timeout, this, &CharacterSelectionWidget::updateCharacterAnimation);

    // Start timers
    nameAnimationTimer->start(100); // 100ms for a smooth continuous animation
    characterAnimationTimer->start(100);

    // Connect buttons to slots
    connect(leftButton, &QPushButton::clicked, this, &CharacterSelectionWidget::onLeftButtonClicked);
    connect(rightButton, &QPushButton::clicked, this, &CharacterSelectionWidget::onRightButtonClicked);

    updateCharacter(currentCharacterIndex);
}

/*void CharacterSelectionWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    if (!characters.empty()) {
        const auto& characterSprites = characters[currentCharacterIndex].characterSpritesGetter();
        if (!characterSprites.empty()) {
            const auto& sprite = characterSprites[0];
            QPixmap pixmap = CharacterSelectionWidget::spriteToPixmap(sprite);
            // painter.drawPixmap(0, 0, pixmap);
        }
    }

    QWidget::paintEvent(event);
}*/

void CharacterSelectionWidget::updateCharacter(int index) {
    currentCharacterIndex = index;
    auto nameSprites = characters[index].nameSpritesGetter();
    auto characterSprites = characters[index].characterSpritesGetter();

    auto* nameScene = new QGraphicsScene(this);
    auto* characterScene = new QGraphicsScene(this);

    for (const auto& sprite: nameSprites) {
        QPixmap pixmap = CharacterSelectionWidget::spriteToPixmap(sprite);
        auto* item = new QGraphicsPixmapItem(pixmap);
        nameScene->addItem(item);
    }

    for (const auto& sprite: characterSprites) {
        QPixmap pixmap = CharacterSelectionWidget::spriteToPixmap(sprite);
        auto* item = new QGraphicsPixmapItem(pixmap);
        characterScene->addItem(item);
    }

    nameAnimationView->setScene(nameScene);
    characterAnimationView->setScene(characterScene);
}

QPixmap CharacterSelectionWidget::spriteToPixmap(const Sprite& sprite) {
    QString spriteSheetPath = ":/" + QString::fromStdString(sprite.getSpriteSheetPath());

    if (!QFile::exists(spriteSheetPath)) {
        return {};
    }

    QPixmap spriteSheet(spriteSheetPath);

    if (spriteSheet.isNull()) {
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

    QImage image = spritePixmap.toImage();
    std::tuple<int, int, int> spriteColourKey = sprite.getColourKey();
    QColor colourKey(std::get<0>(spriteColourKey), std::get<1>(spriteColourKey), std::get<2>(spriteColourKey));

    // Create a QPolygon from the vertices
    QPolygon polygon;
    for (const auto& vertex : vertices) {
        polygon << QPoint(vertex.first - minX, vertex.second - minY);
    }

    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            if (!polygon.containsPoint(QPoint(x, y), Qt::OddEvenFill)) {
                image.setPixelColor(x, y, colourKey);
            }
        }
    }

    QPixmap finalSprite = QPixmap::fromImage(image);
    QBitmap mask = finalSprite.createMaskFromColor(colourKey, Qt::MaskInColor);
    finalSprite.setMask(mask);

    return finalSprite;
}

void CharacterSelectionWidget::updateNameAnimation() {
    // Increment frame index and wrap around if necessary
    nameAnimationFrameIndex = (nameAnimationFrameIndex + 1) % characters[currentCharacterIndex].nameSpritesGetter().size();

    // Get the new frame as a QPixmap
    QPixmap newFrame = spriteToPixmap(characters[currentCharacterIndex].nameSpritesGetter()[nameAnimationFrameIndex]);

    // Create a new QGraphicsScene
    auto* scene = new QGraphicsScene(this);

    // Add the new frame to the scene
    scene->addPixmap(newFrame);

    // Set the scene on the QGraphicsView
    nameAnimationView->setScene(scene);
}

void CharacterSelectionWidget::updateCharacterAnimation() {
    // Increment frame index and wrap around if necessary
    characterAnimationFrameIndex = (characterAnimationFrameIndex + 1) % characters[currentCharacterIndex].characterSpritesGetter().size();

    // Get the new frame as a QPixmap
    QPixmap newFrame = spriteToPixmap(characters[currentCharacterIndex].characterSpritesGetter()[characterAnimationFrameIndex]);

    // Create a new QGraphicsScene
    auto* scene = new QGraphicsScene(this);

    // Add the new frame to the scene
    scene->addPixmap(newFrame);

    // Set the scene on the QGraphicsView
    characterAnimationView->setScene(scene);
}

void CharacterSelectionWidget::onLeftButtonClicked() {
    if (currentCharacterIndex > 0) {
        updateCharacter(currentCharacterIndex - 1);
    } else {
        updateCharacter(characters.size() - 1); // Wrap around to the last character
    }
}

void CharacterSelectionWidget::onRightButtonClicked() {
    if (currentCharacterIndex < characters.size() - 1) {
        updateCharacter(currentCharacterIndex + 1);
    } else {
        updateCharacter(0); // Wrap around to the first character
    }
}

void CharacterSelectionWidget::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Left) {
        onLeftButtonClicked();
    } else if (event->key() == Qt::Key_Right) {
        onRightButtonClicked();
    }
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
