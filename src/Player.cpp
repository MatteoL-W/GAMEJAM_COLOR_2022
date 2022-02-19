#include "../include/Player.hpp"

/**
 * @brief Anticipate the player behaviour (is he intersecting something and moving)
 * @param position
 */
void Player::shot(Point2D position)
{
    // TODO: intersection function
}

bool Player::intersectBall(const Point2D& positionClick, const Ball& ball, std::vector<Player*> players, std::vector<Point2D*> fieldLimits, Point2D& intersection)
{
    std::vector<DynamicObject*> playersDynamic;
    for (int i = 0; i < 8; i++) {
        playersDynamic.push_back(players[i]);
    }
    nearestIntersection(positionClick, *this, playersDynamic, fieldLimits, intersection);
    Point2D tmpIntersection;
    if (intersectCircle(ball.getPosition(), ball.getRadius(), this->getPosition(), this->getPosition().getDirection(positionClick), tmpIntersection)) {
        float distanceBall    = this->getPosition().getDistance(tmpIntersection);
        float nearestDistance = this->getPosition().getDistance(intersection);
        if (distanceBall < nearestDistance) {
            intersection.print();
            return true;
        }
    }
    intersection.print();
    return false;
}

/* Pour plus tard:

 void Map::updatePlayerSprite() {
   int speed = 100;
   int frames = 4;
   srcPlayer.x = srcPlayer.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
}

 */