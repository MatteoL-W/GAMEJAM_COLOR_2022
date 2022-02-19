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

Point2D Point2D::getDirection(const float x, const float y) const
{
    Point2D direction;
    Point2D position(x, y);
    direction = normalize(vectorFromPoints(*this, position));
    return direction;
}

float Point2D::getDistance(Point2D point) const
{
    return sqrt((point.getX() - x) * (point.getX() - x) + (point.getY() - y) * (point.getY() - y));
}
float Point2D::getDistance(float xPoint, float yPoint) const
{
    Point2D point(xPoint, yPoint);
    return sqrt((point.getX() - x) * (point.getX() - x) + (point.getY() - y) * (point.getY() - y));
}

int solveQuadratic(const float a, const float b, const float c, float* x0, float* x1)
{
    float delta = b * b - 4 * a * c;

    if (delta < 0)
        return 0;
    else if (delta == 0)
        *x0 = *x1 = -b / (2. * a);
    else {
        *x0 = (-b + sqrt(delta)) / (2. * a);
        *x1 = (-b - sqrt(delta)) / (2. * a);
    }

    return 1;
}

int intersectCircle(Point2D circleOrigin, float radius, Point2D position, Point2D direction, Point2D& intersection)
{
    float   x0, x1;
    float   y;
    float   a  = circleOrigin.getX();
    float   b  = circleOrigin.getY();
    float   r  = radius;
    Point2D p1 = position;
    Point2D p2 = position + direction;
    float   m  = (p2.getY() - p1.getY()) / (p2.getX() - p1.getX());
    float   c  = p1.getY() - p1.getX() * m;

    float A = 1 + m * m;
    float B = 2 * (m * c - b * m - a);
    float C = a * a + c * c + b * b - 2 * b * c - r * r;

    if (!solveQuadratic(A, B, C, &x0, &x1)) {
        return 0;
    }

    if (position.getDistance(x0, m * x0 + c) > position.getDistance(x1, m * x1 + c)) {
        x0 = x1;
    }
    y = m * x0 + c;
    intersection.setPoint(x0, y);
    intersection.print();
    return 1;
}
