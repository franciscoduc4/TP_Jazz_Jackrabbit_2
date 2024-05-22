#ifndef VECTOR_H
#define VECTOR_H


struct Vector {
    float x;
    float y;

    Vector() : x(0), y(0) {}
    Vector(float x, float y) : x(x), y(y) {}

    Vector operator+(const Vector& other) const {
        return Vector(x + other.x, y + other.y);
    }

    Vector operator-(const Vector& other) const {
        return Vector(x - other.x, y - other.y);
    }

    Vector operator*(float scalar) const {
        return Vector(x * scalar, y * scalar);
    }

    void operator+=(const Vector& other) {
        x += other.x;
        y += other.y;
    }

    void operator-=(const Vector& other) {
        x -= other.x;
        y -= other.y;
    }

    void operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
    }
};

#endif // VECTOR_H
