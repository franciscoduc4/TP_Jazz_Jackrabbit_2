#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <vector>
#include <utility>
#include <tuple> 
#include <stdexcept>


class Sprite {
 private:
    std::vector<std::pair<int, int>> vertices;
    std::string spriteSheetPath;
    std::tuple<int, int, int> colourKey;

 public:
    explicit Sprite(const std::vector<std::pair<int, int>>& vertices) : vertices(vertices) {
        if (vertices.empty() || vertices.front() != vertices.back()) {
            throw std::invalid_argument("Vertices must form a closed polygon");
        }
    }

    static std::vector<Sprite> createSprites(const std::vector<std::vector<std::pair<int, int>>>& valuesList) {
        std::vector<Sprite> sprites;
        for (const auto& values : valuesList) {
            sprites.push_back(Sprite(values));
        }
        return sprites;
    }

    void setSpriteSheetPath(const std::string& path) {
        spriteSheetPath = path;
    }

    void setColourKey(const std::tuple<int, int, int>& key) {
        colourKey = key;
    }

    std::string getSpriteSheetPath() const {
        return spriteSheetPath;
    }

    std::tuple<int, int, int> getColourKey() const {
        return colourKey;
    }

};

class RectangularSprite : public Sprite {
 private:
    int x, y, width, height;

 public:
    RectangularSprite(int x, int y, int width, int height) : 
    x(x), y(y), width(width), height(height), 
    Sprite({{this->x, this->y},
            {this->x + this->width, this->y},
            {this->x + this->width, this->y + this->height},
            {this->x, this->y + this->height}, 
            {this->x, this->y}}) {}

    explicit RectangularSprite(const std::vector<int>& values)
        : Sprite({{values[0], values[1]},
                {values[0] + values[2], values[1]},
                {values[0] + values[2], values[1] + values[3]},
                {values[0], values[1] + values[3]},
                {values[0], values[1]}}),
            x(values[0]), y(values[1]), width(values[2]), height(values[3]) {
        if (values.size() != 4) {
            throw std::invalid_argument("Vector must contain exactly four elements");
        }
    }

    explicit RectangularSprite(const std::tuple<int, int, int, int>& values) :
        Sprite({{std::get<0>(values), std::get<1>(values)},
            {std::get<0>(values) + std::get<2>(values), std::get<1>(values)},
            {std::get<0>(values) + std::get<2>(values), std::get<1>(values) + std::get<3>(values)},
            {std::get<0>(values), std::get<1>(values) + std::get<3>(values)},
            {std::get<0>(values), std::get<1>(values)}}),
        x(std::get<0>(values)),
        y(std::get<1>(values)),
        width(std::get<2>(values)),
        height(std::get<3>(values)) {}

    static std::vector<RectangularSprite> createSprites(
            const std::vector<std::vector<int>>& valuesList) {
        std::vector<RectangularSprite> sprites;
        for (const auto& values : valuesList) {
            sprites.push_back(RectangularSprite(values));
        }
        return sprites;
    }

    static std::vector<RectangularSprite> createSprites(
            const std::vector<std::tuple<int, int, int, int>>& valuesList) {
        std::vector<RectangularSprite> sprites;
        for (const auto& values : valuesList) {
            sprites.push_back(RectangularSprite(values));
        }
        return sprites;
    }

    int get_x() const {
        return this->x;
    } 

    int get_y() const {
        return this->y;
    }

    int get_width() const {
        return this->width;
    }

    int get_height() const {
        return this->height;
    }
};

#endif  // SPRITE_H
