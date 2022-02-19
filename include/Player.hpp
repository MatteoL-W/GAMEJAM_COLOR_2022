#pragma once

#include "DynamicObject.hpp"
#include "Geometry.hpp"

class Player : public DynamicObject {
public:
    Player(float radius, int team)
        : DynamicObject(radius), collision(false), team(team)
    {
    }

    void intersect(Point2D position) override;

    int getTeam() const { return team; };

private:
    bool collision;

    int team;
};
