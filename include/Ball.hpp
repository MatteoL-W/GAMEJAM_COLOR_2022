#pragma once

#include "DynamicObject.hpp"

class Ball : public DynamicObject {
public:
    Ball(float radius)
        : DynamicObject(radius)
    {
    }
};
