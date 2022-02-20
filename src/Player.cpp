#include "../include/Player.hpp"

bool Player::intersectBall(const Point2D& positionClick, const Ball& ball, std::vector<Player*> players, std::vector<Point2D*> fieldLimits, Point2D& intersection)
{
    playerShoots();
    std::vector<DynamicObject*> playersDynamic;
    for (int i = 0; i < 8; i++) {
        playersDynamic.push_back(players[i]);
    }
    nearestIntersection(positionClick, *this, playersDynamic, fieldLimits, intersection);
    intersection.print();
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

/**
 * @brief Anticipate the player behaviour (is he intersecting something and moving)
 * 
 * @param positionClick 
 * @param ball 
 * @param players 
 * @param fieldLimits 
 * @param intersection 
 */
void Player::shoot(const Ball& ball, bool touchesBall, std::vector<Player*> players, std::vector<Point2D*> fieldLimits, Point2D& intersection, Point2D direction)
{
    //if (!touchesBall) {
    float distance = this->getPosition().getDistance(intersection);
    if (this->getSpeed() > 0 && distance > 40) {
        this->move(this->getPosition() + direction * this->getSpeed());
    }
    // }
    // if (touchesBall)
    //     Point2D currentIntersection(2000, 2000);
    else {
        stopShooting();
    }
}

/* Pour plus tard:

 void Map::updatePlayerSprite() {
   int speed = 100;
   int frames = 4;
   srcPlayer.x = srcPlayer.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
}

 */