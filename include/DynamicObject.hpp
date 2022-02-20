#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include "Game.hpp"
#include "Geometry.hpp"

const float DECELERATION_FACTOR = 0.90;

class DynamicObject {
public:
    explicit DynamicObject(float radius)
        : position(Point2D(0, 0)), radius(radius), speed(30)
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
        //decelerate();
    }

    void setPosition(Point2D newPosition) { position = newPosition; };

    Point2D getPosition() const { return position; };

    float getRadius() const { return radius; };

    float getXOnDraw() const { return getPosition().getX() - getRadius(); };

    float getYOnDraw() const { return getPosition().getY() - getRadius(); };

    float getSpeed() const { return speed; };

    void setIntersectionPlayers(const Point2D& intersection) { intersectionPlayers = intersection; };
    void setIntersectionFieldLimits(const Point2D& intersection) { intersectionFieldLimits = intersection; };

    Point2D getIntersectionPlayers() const { return intersectionPlayers; };
    Point2D getIntersectionFieldLimits() const { return intersectionFieldLimits; };

private:
    Point2D position;

    float radius;

    float speed;

    Point2D intersectionPlayers;

    Point2D intersectionFieldLimits;
};

void nearestIntersectionPlayers(const Point2D& positionClick, DynamicObject& currentObject, std::vector<DynamicObject*> players);

void nearestIntersectionFieldLimits(const Point2D& positionClick, DynamicObject& currentObject, std::vector<Point2D*> fieldLimits);

void nearestIntersection(const Point2D& positionClick, DynamicObject& currentObject, std::vector<DynamicObject*> players, std::vector<Point2D*> fieldLimits, Point2D& intersection);

Point2D getNormal(Point2D intersection);
Point2D getReflection(Point2D intersection, Point2D direction);