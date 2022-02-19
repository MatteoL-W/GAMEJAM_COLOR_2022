#include "../include/Geometry.hpp"
#include <cmath>

float epsilon = 0.01;

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

bool Point2D::operator==(const Point2D& p) const
{
    return (std::abs(x - p.getX()) < epsilon) && (std::abs(y - p.getY()) < epsilon);
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

/**
 * @brief Returns scalar product
 * @param vector1
 * @param vector2
 */
float dot(Point2D vector1, Point2D vector2)
{
    return vector1.getX() * vector2.getX() + vector1.getY() * vector1.getY();
}

/**
 * @brief Returns norm of vector
 * @param vector
 */
float norm(Point2D vector)
{
    return sqrt(dot(vector, vector));
}

/**
 * @brief Returns the normalized version of a vector without changing it
 * @param vector
 */

Point2D normalize(Point2D vector)
{
    Point2D normal;
    normal = vector / norm(vector);
    return normal;
}

/**
 * @brief Returns a vector created from 2 points
 * @param point1
 * @param point2
 */
Point2D vectorFromPoints(Point2D const& point1, Point2D const& point2)
{
    Point2D vector;
    vector = point2 - point1;
    return vector;
}

/**
 * @brief Returns the direction of the point pointing at a position
 * @param position
 */
Point2D Point2D::getDirection(Point2D position) const
{
    Point2D direction;
    direction = normalize(vectorFromPoints(*this, position));
    return direction;
}

/**
 * @brief Returns the direction of the point pointing at a position (x,y)
 * @param x
 * @param y
 */
Point2D Point2D::getDirection(const float x, const float y) const
{
    Point2D direction;
    Point2D position(x, y);
    direction = normalize(vectorFromPoints(*this, position));
    return direction;
}

/**
 * @brief Returns the distance between the point and another point
 * @param point
 */
float Point2D::getDistance(Point2D point) const
{
    return sqrt((point.getX() - x) * (point.getX() - x) + (point.getY() - y) * (point.getY() - y));
}

/**
 * @brief Returns the distance between the point and another point (x,y)
 * @param x
 * @param y
 */
float Point2D::getDistance(float xPoint, float yPoint) const
{
    Point2D point(xPoint, yPoint);
    return sqrt((point.getX() - x) * (point.getX() - x) + (point.getY() - y) * (point.getY() - y));
}

/**
 * @brief Solves a*x²+b*x+c = 0 and gives the (x0,x1) results
 * @param a
 * @param b
 * @param c
 * @param x0
 * @param x1
 */
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

/**
 * @brief When there is an intersection between a line and an object, checks if 
 * the vector is pointing at the intersection 
 * Returns true if is looking, false if the intersection is behind
 * @param position
 * @param direction
 * @param intersection
 */
int isLooking(const Point2D& position, const Point2D& direction, const Point2D& intersection)
{
    Point2D lookAt             = vectorFromPoints(position, position + direction);
    Point2D lookAtIntersection = vectorFromPoints(position, intersection);

    if (dot(lookAt, lookAtIntersection) < 0) {
        return 0;
    }
    return 1;
}

/**
 * @brief Returns true if intersect and give intersection the value of the intersection
 * 
 * @param circleOrigin 
 * @param radius 
 * @param position 
 * @param direction 
 * @param intersection 
 * @return int 
 */
int intersectCircle(const Point2D& circleOrigin, float radius, const Point2D& position, const Point2D& direction, Point2D& intersection)
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
    Point2D closestIntersection(x0, y);
    if (!isLooking(position, direction, closestIntersection)) {
        return 0;
    }
    intersection = closestIntersection;
    return 1;
}

/**
 * @brief Returns true if intersection and set intersection value
 * 
 * @param position 
 * @param direction 
 * @param a 
 * @param b 
 * @param intersection 
 * @return int 
 */
int intersectLine(const Point2D& position, const Point2D& direction, Point2D a, Point2D b, Point2D& intersection)
{
    Point2D p1 = position;
    Point2D p2 = position + direction;
    float   x  = 2000;
    float   y  = 2000;

    //cas 1, horizontal, cad a et b ont le même y et sont d'equation y=a.getY()
    if (std::abs(a.getY() - b.getY()) < epsilon) {
        if (std::abs(p1.getY() - p2.getY()) < epsilon) {
            return 0;
        }
        float m = (p2.getY() - p1.getY()) / (p2.getX() - p1.getX());
        float p = p1.getY() - p1.getX() * m;
        y       = a.getY();
        x       = (y - p) / m;
    }

    //cas 2, vertical, cad a et b même x et d'équation x=a.getX();, c'est forcément le cas on a que des seg horizontaux ou verticaux
    else {
        if (std::abs(p1.getX() - p2.getX()) < epsilon) {
            std::cout << std::abs(p1.getX() - p2.getX()) << std::endl;
            return 0;
        }
        float m = (p2.getY() - p1.getY()) / (p2.getX() - p1.getX());
        float p = p1.getY() - p1.getX() * m;
        x       = a.getX();
        y       = m * x + p;
    }

    Point2D closestIntersection(x, y);
    intersection = closestIntersection;
    return 1;
}

/**
 * @brief Returns true if intersect the segment
 * 
 * @param position 
 * @param direction 
 * @param a 
 * @param b 
 * @param intersection 
 * @return int 
 */
int intersectSegment(const Point2D& position, const Point2D& direction, Point2D a, Point2D b, Point2D& intersection)
{
    if (!intersectLine(position, direction, a, b, intersection)) {
        return 0;
    }
    if (!isLooking(position, direction, intersection)) {
        return 0;
    }
    Point2D vectorAI = vectorFromPoints(a, intersection);
    Point2D vectorAB = vectorFromPoints(a, b);

    if (dot(vectorAI, vectorAB) < 0) {
        return 0;
    }
    return 1;
}