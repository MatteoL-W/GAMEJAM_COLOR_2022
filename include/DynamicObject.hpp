#pragma once

#include <SDL2/SDL.h>

#include "Game.hpp"
#include "Geometry.hpp"

class DynamicObject {
public:
    explicit DynamicObject(float radius) : position(Point2D(0,0)), radius(radius), speed(0)
    {
    }

    ~DynamicObject() = default;

    void move(Point2D position)
    {
        // TODO: move function
    }

    static void draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect dstRect) {
        SDL_RenderCopy(Game::renderer, texture, &srcRect, &dstRect);
    }

    virtual void intersect(Point2D position) = 0;

    void changePosition(Point2D newPosition) { position = newPosition; };

    void changeSpeed(float newSpeed) { speed = newSpeed; };

private:
    Point2D position;

    float radius;

    float speed;
};
