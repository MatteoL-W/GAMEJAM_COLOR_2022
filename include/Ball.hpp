#pragma once

#include "DynamicObject.hpp"

const float DECELERATION_FACTOR = 0.98;

class Ball : public DynamicObject {
public:
    Ball(float radius)
        : DynamicObject(radius)
    {
    }

    void shot(Point2D position) override;

    float getSpeed() const { return speed; };

    void decelerate() { speed = speed * DECELERATION_FACTOR; };

private:
    float speed;
};
