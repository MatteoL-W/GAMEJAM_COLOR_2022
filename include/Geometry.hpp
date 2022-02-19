#pragma once
#include <iostream>

class Point2D {
private:
    float x;
    float y;

public:
    Point2D(float x = 0, float y = 0)
        : x(x), y(y){};
    Point2D(const Point2D& p)
        : x(p.getX()), y(p.getY()){};

    ~Point2D() = default;

    float getX() const { return x; };
    float getY() const { return y; };

    void addPoint(const Point2D& p)
    {
        x += p.getX();
        y += p.getY();
    };

    Point2D& operator=(const Point2D& v);
    Point2D  operator+(const Point2D& p) const;
    Point2D  operator-(const Point2D& p) const;
    Point2D  operator*(const float& a) const;
    Point2D  operator/(const float& a) const;
    Point2D  operator-() const;

    Point2D getDirection(Point2D position) const;

    void print() { std::cout << "Point : (" << x << ", " << y << ")" << std::endl; };
};

float   dot(Point2D vector1, Point2D vector2);
float   norm(Point2D vector);
Point2D normalize(Point2D vector);
Point2D vectorFromPoints(Point2D const& vector1, Point2D const& vector2);