#pragma once

#include "Ball.hpp"
#include "DynamicObject.hpp"

class Player : public DynamicObject {
public:
    Player(float radius, int team)
        : DynamicObject(radius), collision(false), team(team), intersectionBall(2000, 2000)
    {
    }

    int getTeam() const { return team; };

    bool intersectBall(const Point2D& positionClick, Ball& ball, std::vector<Player*> players, std::vector<Point2D*> fieldLimits, Point2D& intersection);

    void shoot(const Point2D& positionClick, Ball& ball, bool touchesBall, std::vector<Player*> players, std::vector<Point2D*> fieldLimits, Point2D& intersectionPoint2D);

    bool isPlayerShooting() const { return isShooting; };

    void playerShoots() { isShooting = true; };

    void stopShooting() { isShooting = false; };

    Point2D getIntersectionBall() const { return intersectionBall; };
    void    setIntersectionBall(const Point2D& newIntersection) { intersectionBall = newIntersection; };
    void    setIntersectionBall(const float& x, const float& y) { intersectionBall.setPoint(x, y); };

    Point2D getDirectionPlayer() const { return directionPlayer; };
    void    setDirectionPlayer(const Point2D& newIntersection) { directionPlayer = newIntersection; };
    void    setDirectionPlayer(const float& x, const float& y) { directionPlayer.setPoint(x, y); };

    Point2D getDirectionBall() const { return intersectionBall; };
    void    setDirectionBall(const Point2D& newIntersection) { directionBall = newIntersection; };
    void    setDirectionBall(const float& x, const float& y) { directionBall.setPoint(x, y); };

private:
    bool collision;

    bool isShooting;

    int team;

    Point2D intersectionBall;

    Point2D directionPlayer;
    Point2D directionBall;
};
