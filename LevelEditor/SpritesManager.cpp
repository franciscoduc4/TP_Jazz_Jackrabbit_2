#include "SpritesManager.h"

SpritesManager* SpritesManager::instance = nullptr;
QMap<QString, QPixmap> SpritesManager::sprites;
QMap<QString, int> SpritesManager::widths;
QMap<QString, int> SpritesManager::heights;

SpritesManager::SpritesManager() {
    root = YAML::LoadFile("Sprites/sprites.yaml");
    for (YAML::const_iterator it = root.begin(); it != root.end(); ++it) {
        QString name = QString::fromStdString(it->first.as<std::string>());
        auto sprite = it->second["SPRITE"].as<std::vector<int>>();
        QString path = QString::fromStdString(it->second["PATH"].as<std::string>());
        auto colour_key = it->second["COLOUR_KEY"].as<std::vector<int>>();
        widths[name] = it->second["WIDTH"].as<int>();
        heights[name] = it->second["HEIGHT"].as<int>();

        QPixmap pixmap(path);
        if (!sprite.empty()) {
            pixmap = pixmap.copy(sprite[0], sprite[1], sprite[2], sprite[3]);
        }
        pixmap.setMask(pixmap.createMaskFromColor(QColor(colour_key[0], colour_key[1], colour_key[2]), Qt::MaskInColor));
        sprites[name] = pixmap;
    }
}
SpritesManager* SpritesManager::getInstance() {
    if (!instance) {
        instance = new SpritesManager();
    }
    return instance;
}

QPixmap SpritesManager::get(const QString& name) {
    return sprites[name].scaled(widths[name], heights[name], Qt::KeepAspectRatio);
}

void SpritesManager::deleteInstance() {
    if (instance) {
        delete instance;
        instance = nullptr;
    }
}