#pragma once

#include "Geometry.hpp"
#include "DynamicObject.hpp"

const float DECELERATION_FACTOR = 0.98;

class Ball : public DynamicObject {
public:
    void shot(Point2D position) override;

    float getSpeed() { return speed; };

    void decelerate() { speed = speed * DECELERATION_FACTOR;};

private:
    float speed;
};
