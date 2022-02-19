#pragma once

#include "Geometry.hpp"
#include "DynamicObject.hpp"

class Player : public DynamicObject {
public:
    Player(float radius, int team) : DynamicObject(radius), collision(false), team(team)
    {
    }

    void shot(Point2D position) override;

    int getTeam() const { return team; };

private:
    bool collision;

    int team;
};
