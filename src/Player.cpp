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
void Player::shoot(const Point2D& positionClick, Ball& ball, bool touchesBall, std::vector<Player*> players, std::vector<Point2D*> fieldLimits, Point2D& intersection, Point2D direction)
{
    if (!touchesBall) {
        float distance = this->getPosition().getDistance(intersection);
        if (this->getSpeed() > 0 && distance > 40) {
            this->move(this->getPosition() + direction * this->getSpeed());
        }
        else {
            stopShooting();
        }
    }
    else {
        // std::cout << "BALLE" << std::endl;
        // std::vector<DynamicObject*> playersDynamic;
        // for (int i = 0; i < 8; i++) {
        //     playersDynamic.push_back(players[i]);
        // }
        // nearestIntersection(positionClick, *this, playersDynamic, fieldLimits, intersection);
        float distance = this->getPosition().getDistance(intersection);
        if (this->getSpeed() > 0 && distance > 40) {
            this->move(this->getPosition() + direction * this->getSpeed());
        }
        else {
            if (!(intersection == this->getIntersectionFieldLimits())) {
                float distance = ball.getPosition().getDistance(intersection);
                if (ball.getSpeed() > 0) {
                    ball.move(ball.getPosition() + direction * ball.getSpeed());
                }
                else {
                    stopShooting();
                }
                std::cout << "touches player first" << std::endl;
            }
            else {
                if (intersection.getY() >= (Game::WINDOW_HEIGHT / 2) - 100 && intersection.getY() <= (Game::WINDOW_HEIGHT / 2) + 100) {
                    // std::cout << "marque un goooal" << std::endl;
                }
                else {
                    // std::cout << "touche les murs là " << std::endl;
                }
            }
        }
    }
    // if (touchesBall)
    //     Point2D currentIntersection(2000, 2000);
}

/* Pour plus tard:

 void Map::updatePlayerSprite() {
   int speed = 100;
   int frames = 4;
   srcPlayer.x = srcPlayer.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
}

 */