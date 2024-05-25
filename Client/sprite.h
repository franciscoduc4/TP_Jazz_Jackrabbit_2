#ifndef SPRITE_H
#define SPRITE_H

#include <vector>
#include <tuple> 
#include <stdexcept>

struct Sprite {
    int x;
    int y;
    int width;
    int height;

    Sprite(int x, int y, int width, int height)
        : x(x), y(y), width(width), height(height) {}

    explicit Sprite(const std::vector<int>& values) {
        if (values.size() != 4) {
            throw std::invalid_argument("Vector must contain exactly four elements");
        }
        x = values[0];
        y = values[1];
        width = values[2];
        height = values[3];
    }

    explicit Sprite(const std::tuple<int, int, int, int>& values)
        : x(std::get<0>(values)),
        y(std::get<1>(values)),
        width(std::get<2>(values)),
        height(std::get<3>(values)) {}
};

#endif  // SPRITE_H
