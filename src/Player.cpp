#include "../include/Player.hpp"

/**
 * @brief Anticipate the player behaviour (is he intersecting something and moving)
 * @param position
 */
void Player::shot(Point2D position)
{
    // TODO: intersection function
}

bool Player::intersectBall(const Point2D& positionClick, const Ball& ball, std::vector<DynamicObject*> players, std::vector<Point2D*> fieldLimits, Point2D& intersection)
{
    nearestIntersection(positionClick, *this, players, fieldLimits, intersection);
    return true;
}
