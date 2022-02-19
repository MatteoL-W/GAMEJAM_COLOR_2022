#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include "Game.hpp"
#include "Geometry.hpp"

const float DECELERATION_FACTOR = 0.90;

class DynamicObject {
public:
    explicit DynamicObject(float radius)
        : position(Point2D(0, 0)), radius(radius), speed(50)
    {
    }

    ~DynamicObject() = default;

    void decelerate() { speed = speed * DECELERATION_FACTOR; };

    /**
     * @brief Change the position to a new position
     * @param newPosition
     */
    void changePosition(Point2D newPosition) { position = newPosition; };

    /**
     * @brief Change the speed
     * @param newSpeed
     */
    void changeSpeed(float newSpeed) { speed = newSpeed; };

    /**
     * @brief Move the dynamic object depending on the arrival position
     * @param position
     */
    void move(Point2D newPosition)
    {
        this->position = newPosition;
        decelerate();
    }

    void setPosition(Point2D newPosition) { position = newPosition; };

    Point2D getPosition() const { return position; };

    float getRadius() const { return radius; };

    float getXOnDraw() const { return getPosition().getX() - getRadius(); };

    float getYOnDraw() const { return getPosition().getY() - getRadius(); };

    float getSpeed() const { return speed; };

private:
    Point2D position;

    float radius;

    float speed;
};

void nearestIntersectionPlayers(const Point2D& positionClick, const DynamicObject& currentObject, std::vector<DynamicObject*> players, Point2D& intersection);

void nearestIntersectionFieldLimits(const Point2D& positionClick, const DynamicObject& currentObject, std::vector<Point2D*> fieldLimits, Point2D& intersection);

void nearestIntersection(const Point2D& positionClick, const DynamicObject& currentObject, std::vector<DynamicObject*> players, std::vector<Point2D*> fieldLimits, Point2D& intersection);