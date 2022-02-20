#include "../include/Player.hpp"

bool Player::intersectBall(const Point2D& positionClick, Ball& ball, std::vector<Player*> players, std::vector<Point2D*> fieldLimits, Point2D& intersection)
{
    playerShoots();
    notRebounding();
    intersection.setPoint(2000, 2000);
    this->setIntersectionBall(2000, 2000);
    this->setDirectionPlayer(this->getPosition().getDirection(positionClick));
    this->setDirectionPlayer(this->getDirectionPlayer());
    std::vector<DynamicObject*> playersDynamic;
    for (int i = 0; i < 8; i++) {
        playersDynamic.push_back(players[i]);
    }
    nearestIntersection(positionClick, *this, playersDynamic, fieldLimits, intersection);
    intersection.print();
    Point2D tmpIntersection;
    if (intersectCircle(ball.getPosition(), ball.getRadius(), this->getPosition(), this->getDirectionPlayer(), tmpIntersection)) {
        float distance        = this->getPosition().getDistance(tmpIntersection);
        float nearestDistance = this->getPosition().getDistance(intersection);
        if (distance < nearestDistance) {
            intersection = tmpIntersection;
            nearestIntersection(ball.getPosition() + this->getDirectionPlayer() * 30., ball, playersDynamic, fieldLimits, tmpIntersection);
            this->setIntersectionBall(tmpIntersection);
            this->setDirectionBall(ball.getPosition().getDirection(tmpIntersection));
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
void Player::shoot(const Point2D& positionClick, Ball& ball, bool touchesBall, std::vector<Player*> players, std::vector<Point2D*> fieldLimits, Point2D& intersection)
{
    Point2D direction     = this->getDirectionPlayer();
    Point2D directionBall = this->getDirectionBall();
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
        float distance = this->getPosition().getDistance(ball.getPosition());
        if (this->getSpeed() > 0 && distance > 40) {
            this->move(this->getPosition() + direction * this->getSpeed());
        }
        else {
            this->changeSpeed(0);
            float distance = ball.getPosition().getDistance(this->getIntersectionBall());
            ball.getPosition().print();
            this->getIntersectionBall().print();
            if (!(this->getIntersectionBall() == ball.getIntersectionFieldLimits())) {
                if (ball.getSpeed() > 0 && distance > 40 && isLooking(ball.getPosition(), directionBall, this->getIntersectionBall())) {
                    ball.move(ball.getPosition() + direction * ball.getSpeed());
                }
                else {
                    stopShooting();
                }
                std::cout << "touches player first" << std::endl;
            }
            else {
                if (this->getIntersectionBall().getY() >= (Game::WINDOW_HEIGHT / 2) - 100 && this->getIntersectionBall().getY() <= (Game::WINDOW_HEIGHT / 2) + 100) {
                    if (ball.getSpeed() > 0 && distance > 40 && isLooking(ball.getPosition(), directionBall, this->getIntersectionBall())) {
                        ball.move(ball.getPosition() + direction * ball.getSpeed());
                    }
                    else {
                        //rajouter test pour savoir quel but
                        std::cout << "distance : " << distance << " et is looking dir : ";
                        direction.print();
                        std::cout << " at intersect : ";
                        this->getIntersectionBall().print();
                        std::cout << std::endl;
                        stopShooting();
                    }
                    std::cout << "marque un goooal" << std::endl;
                }
                else {
                    if (ball.getSpeed() > 0 && distance > 40 && isLooking(ball.getPosition(), directionBall, this->getIntersectionBall())) {
                        ball.move(ball.getPosition() + direction * ball.getSpeed());
                    }
                    else {
                        std::cout << "distance : " << distance << " et is looking dir : ";
                        direction.print();
                        std::cout << " at intersect : ";
                        this->getIntersectionBall().print();
                        std::cout << std::endl;
                        if (!rebound) {
                            std::cout << rebound << std::endl;
                            std::vector<DynamicObject*> playersDynamic;
                            Point2D                     tmpIntersection;
                            for (int i = 0; i < 8; i++) {
                                playersDynamic.push_back(players[i]);
                            }
                            this->setDirectionBallRebound(this->getIntersectionBall());
                            nearestIntersection(ball.getPosition() + this->getDirectionBallRebound() * 30., ball, playersDynamic, fieldLimits, tmpIntersection);
                            this->setIntersectionBall(tmpIntersection);
                        }
                        //float distance = ball.getPosition().getDistance(this->getIntersectionBall());
                        //if (ball.getSpeed() > 0 && distance > 40 && isLooking(ball.getPosition(), directionBall, this->getIntersectionBall())) {
                        this->getDirectionBallRebound().print();
                        ball.move(ball.getPosition() + this->getDirectionBallRebound() * 100);
                        //}
                        //else {
                        stopShooting();
                        //}
                    }
                    std::cout << "touche les murs là " << std::endl;
                }
            }
        }
    }
}

/* Pour plus tard:

 void Map::updatePlayerSprite() {
   int speed = 100;
   int frames = 4;
   srcPlayer.x = srcPlayer.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
}

 */