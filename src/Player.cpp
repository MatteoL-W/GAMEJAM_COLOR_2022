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
    Point2D tmpIntersection;
    if (intersectCircle(ball.getPosition(), ball.getRadius(), this->getPosition(), this->getPosition().getDirection(positionClick), tmpIntersection)) {
        float distanceBall    = this->getPosition().getDistance(tmpIntersection);
        float nearestDistance = this->getPosition().getDistance(intersection);
        if (distanceBall < nearestDistance) {
            intersection = tmpIntersection;
            return true;
        }
    }
    return false;
}
