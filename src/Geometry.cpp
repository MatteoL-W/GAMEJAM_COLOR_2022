#include "../include/Geometry.hpp"
#include <cmath>

Point2D& Point2D::operator=(const Point2D& point)
{
    if (this != &point) {
        x = point.getX();
        y = point.getY();
    }
    return *this;
}

Point2D Point2D::operator+(const Point2D& point) const
{
    Point2D sum(x, y);
    sum.addPoint(point);
    return sum;
}

Point2D Point2D::operator-() const
{
    Point2D opposite(-x, -y);
    return opposite;
}

Point2D Point2D::operator-(const Point2D& point) const
{
    Point2D substraction(x, y);
    substraction.addPoint(-point);
    return substraction;
}

Point2D Point2D::operator*(const float& a) const
{
    Point2D multiply(a * x, a * y);
    return multiply;
}

Point2D Point2D::operator/(const float& a) const
{
    Point2D multiply(x / a, y / a);
    return multiply;
}

float dot(Point2D vector1, Point2D vector2)
{
    return sqrt(vector1.getX() * vector2.getX() + vector1.getY() * vector1.getY());
}

float norm(Point2D vector)
{
    return dot(vector, vector);
}

Point2D normalize(Point2D vector)
{
    Point2D normal;
    normal = vector / norm(vector);
    return normal;
}

Point2D vectorFromPoints(Point2D const& vector1, Point2D const& vector2)
{
    Point2D vector;
    vector = vector2 - vector1;
    return vector;
}

Point2D Point2D::getDirection(Point2D position) const
{
    Point2D direction;
    direction = normalize(vectorFromPoints(*this, position));
    return direction;
}
