#pragma once

class Point2D {
private:
    float x;
    float y;

public:
    Point2D(float x, float y)
        : x(x), y(y){};
    Point2D(const Point2D& p)
        : x(p.getX()), y(p.getY()){};

    ~Point2D() = default;

    float getX() const { return x; };
    float getY() const { return y; };
};