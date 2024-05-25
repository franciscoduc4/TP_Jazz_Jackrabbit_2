#ifndef SPRITE_H
#define SPRITE_H

struct Sprite {
    int x;
    int y;
    int width;
    int height;

    Sprite(int x, int y, int width, int height)
        : x(x), y(y), width(width), height(height) {}
};

#endif  // SPRITE_H
