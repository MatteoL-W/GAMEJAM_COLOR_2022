#pragma once

#include "Ball.hpp"
#include "DynamicObject.hpp"

class Player : public DynamicObject {
public:
    Player(float radius, int team)
        : DynamicObject(radius), collision(false), team(team)
    {
    }

    void shot(Point2D position) override;

    int getTeam() const { return team; };

    bool intersectBall(const Point2D& positionClick, const Ball& ball, std::vector<Player*> players, std::vector<Point2D*> fieldLimits, Point2D& intersection);

private:
    bool collision;

    int team;
};
