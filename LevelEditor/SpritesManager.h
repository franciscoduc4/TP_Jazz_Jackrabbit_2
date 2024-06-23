#include <QColor>
#include <QMap>
#include <QPixmap>
#include <QString>
#include <QVector>
#include <QBitmap>
#include <yaml-cpp/yaml.h>

class SpritesManager {
public:
    static SpritesManager* getInstance();

    static QPixmap get(const QString& name);
    static void deleteInstance();

private:
    static SpritesManager* instance;
    YAML::Node root;
    static QMap<QString, QPixmap> sprites;
    static QMap<QString, int> widths;
    static QMap<QString, int> heights;

    SpritesManager();

    SpritesManager(const SpritesManager&) = delete;
    void operator=(const SpritesManager&) = delete;
};