#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include "Game.hpp"
#include "Geometry.hpp"

class DynamicObject {
public:
    explicit DynamicObject(float radius)
        : position(Point2D(0, 0)), radius(radius), speed(0)
    {
    }

    ~DynamicObject() = default;

    void move(Point2D position)
    {
        // TODO: move function
    }

    static void draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect dstRect)
    {
        SDL_RenderCopy(Game::renderer, texture, &srcRect, &dstRect);
    }

    virtual void intersect(Point2D position) = 0;

    void changePosition(Point2D newPosition) { position = newPosition; };

    void changeSpeed(float newSpeed) { speed = newSpeed; };

    Point2D getPosition() const { return position; };

    float getRadius() const { return radius; };

private:
    Point2D position;

    float radius;

    float speed;
};

void nearestIntersectionPlayers(const Point2D& positionClick, const DynamicObject& currentObject, std::vector<Player*> players, Point2D& intersection);

void nearestIntersectionFieldLimits(const Point2D& positionClick, const DynamicObject& currentObject, std::vector<Point2D*> fieldLimits, Point2D& intersection);

void nearestIntersection(const Point2D& positionClick, const DynamicObject& currentObject, std::vector<Player*> players, std::vector<Point2D*> fieldLimits, Point2D& intersection);