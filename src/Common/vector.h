#ifndef VECTOR_H
#define VECTOR_H

template <typename T>
struct Vector {
    T x;
    T y;

    Vector(): x(0), y(0) {}
    Vector(T x, T y): x(x), y(y) {}

    Vector operator+(const Vector& other) const { return Vector(x + other.x, y + other.y); }

    Vector operator-(const Vector& other) const { return Vector(x - other.x, y - other.y); }

    Vector operator*(T scalar) const { return Vector(x * scalar, y * scalar); }

    void operator+=(const Vector& other) {
        x += other.x;
        y += other.y;
    }

    void operator-=(const Vector& other) {
        x -= other.x;
        y -= other.y;
    }

    void operator*=(T scalar) {
        x *= scalar;
        y *= scalar;
    }
};

#endif  // VECTOR_H
