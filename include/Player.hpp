#pragma once

#include "Ball.hpp"
#include "DynamicObject.hpp"

class Player : public DynamicObject {
public:
    Player(float radius, int team)
        : DynamicObject(radius), collision(false), team(team)
    {
    }

    int getTeam() const { return team; };

    bool intersectBall(const Point2D& positionClick, const Ball& ball, std::vector<Player*> players, std::vector<Point2D*> fieldLimits, Point2D& intersection);

    void shoot(const Ball& ball, bool touchesBall, std::vector<Player*> players, std::vector<Point2D*> fieldLimits, Point2D& intersectionPoint2D, Point2D direction);

    bool isPlayerShooting() const { return isShooting; };

    void playerShoots() { isShooting = true; };

    void stopShooting() { isShooting = false; };

private:
    bool collision;

    bool isShooting;

    int team;
};
