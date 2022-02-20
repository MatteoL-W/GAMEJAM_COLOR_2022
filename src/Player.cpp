#include "../include/Player.hpp"

bool Player::intersectBall(const Point2D& positionClick, Ball& ball, std::vector<Player*> players, std::vector<Point2D*> fieldLimits, Point2D& intersection)
{
    ball.changeSpeed(20);
    playerShoots();
    notRebounding();
    noGoalYet();
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
    if (intersectCircle(ball.getPosition(), ball.getRadius()+15, this->getPosition(), this->getDirectionPlayer(), tmpIntersection)) {
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
        if (this->getSpeed() > 1 && distance > 40) {
            this->move(this->getPosition() + direction * this->getSpeed());
        }
        else {
            stopShooting();
        }
    }
    else {
        float distance = this->getPosition().getDistance(intersection);
        if (this->getSpeed() > 1 && distance > 50) {
            this->move(this->getPosition() + direction * this->getSpeed());
        }
        else {
            float distance = ball.getPosition().getDistance(this->getIntersectionBall());
//            ball.getPosition().print();
//            this->getIntersectionBall().print();
            std::cout << "dist"<<distance<<std::endl;
            if (ball.getSpeed() > 1 && distance > 40 && isLooking(ball.getPosition(), direction, this->getIntersectionBall())) {
                ball.move(ball.getPosition() + direction * ball.getSpeed());
            }
            else {
                if (
                    ((std::abs(Game::xPadding - ball.getPosition().getX())<50 ) or (std::abs(Game::WINDOW_WIDTH-Game::xPadding - ball.getPosition().getX())<50))
                    &&( this->getIntersectionBall() == ball.getIntersectionFieldLimits())
                    && (this->getIntersectionBall().getY() >= (Game::WINDOW_HEIGHT / 2) - 100
                        && this->getIntersectionBall().getY() <= (Game::WINDOW_HEIGHT / 2) + 100)) {
                    if (std::abs(this->getIntersectionBall().getX() - Game::xPadding) < 0.1) {
                        rightTeamScores();
                        std::cout << "goal team 2" << std::endl;
                    }
                    else {
                        leftTeamScores();
                        std::cout << "goal team 1" << std::endl;
                    }
                }
                stopShooting();
            }
        }
    }
}