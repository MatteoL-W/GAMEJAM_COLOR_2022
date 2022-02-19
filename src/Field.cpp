#include "../include/Field.hpp"
#include <SDL2/SDL_image.h>
#include "../include/Game.hpp"
#include "../include/Random.hpp"

const int xPadding = 58;
const int yPadding = 42;

Field::Field()
{
    loadAndInitialize();
}

/**
 * @brief Load assets and objects
 */
void Field::loadAndInitialize()
{
    // Initializing assets
    blueCone       = IMG_LoadTexture(Game::renderer, "assets/images/cone1.png");
    yellowCone     = IMG_LoadTexture(Game::renderer, "assets/images/cone2.png");
    ballTexture    = IMG_LoadTexture(Game::renderer, "assets/images/ball.png");
    fieldTexture   = IMG_LoadTexture(Game::renderer, "assets/images/field.png");
    playersTexture = IMG_LoadTexture(Game::renderer, "assets/images/sprite_players.png");

    srcPlayers.w = SRC_PLAYERS_DIMENSIONS_W;
    srcPlayers.h = SRC_PLAYERS_DIMENSIONS_H;

    srcPlayers.y = SRC_PLAYERS_DIMENSIONS_H;
    srcPlayers.x = 0;

    dstPlayers.w = DST_PLAYERS_DIMENSIONS_W;
    dstPlayers.h = DST_PLAYERS_DIMENSIONS_H;

    dstBall.w = dstBall.h = BALL_RADIUS;

    dstGoal.w = dstGoal.h = CONE_RADIUS;

    // initialize ball
    ball = new Ball(BALL_RADIUS / 2);

    // Initializing vectors
    // set Limit Fields
    fieldLimits.push_back(new Point2D(xPadding, yPadding));
    fieldLimits.push_back(new Point2D(Game::WINDOW_WIDTH - xPadding, yPadding));
    fieldLimits.push_back(new Point2D(Game::WINDOW_WIDTH - xPadding, Game::WINDOW_HEIGHT - yPadding));
    fieldLimits.push_back(new Point2D(xPadding, Game::WINDOW_HEIGHT - yPadding));

    // set Players
    for (int i = 0; i < 8; i++) {
        players.push_back(new Player(DST_PLAYERS_DIMENSIONS_H / 2, i / 4));
    }

    // set Goals
    int                           goalGap = 100;
    std::pair<Point2D*, Point2D*> tempGoal;
    tempGoal.first  = new Point2D(xPadding, (Game::WINDOW_HEIGHT / 2) - goalGap);
    tempGoal.second = new Point2D(xPadding, (Game::WINDOW_HEIGHT / 2) + goalGap);
    goals.push_back(tempGoal);

    tempGoal.first  = new Point2D(Game::WINDOW_WIDTH - xPadding, (Game::WINDOW_HEIGHT / 2) - goalGap);
    tempGoal.second = new Point2D(Game::WINDOW_WIDTH - xPadding, (Game::WINDOW_HEIGHT / 2) + goalGap);
    goals.push_back(tempGoal);

    loadPlayersPattern();
    resetBallPosition();
}

/**
 * @brief Place the players depending on pattern
 */
void Field::loadPlayersPattern()
{
    for (int i = 0; i < 8; i++) {
        int radius = players[i]->getRadius();
        if (i < 4) {
            players[i]->setPosition(Point2D(
                randomUniformDistribution(
                    xPadding + radius,
                    Game::WINDOW_WIDTH / 2 - 110),
                (yPadding + radius + 20) + i * (Game::WINDOW_HEIGHT / 4)));
        }
        else {
            players[i]->setPosition(Point2D(
                randomUniformDistribution(
                    xPadding + radius + Game::WINDOW_WIDTH / 2,
                    Game::WINDOW_WIDTH - xPadding - radius),
                (yPadding + radius + 20) + (i % 4) * (Game::WINDOW_HEIGHT / 4)));
        }
    }
}

/**
 * @brief Reset the ball position
 */
void Field::resetBallPosition()
{
    ball->setPosition(Point2D(Game::WINDOW_WIDTH / 2., Game::WINDOW_HEIGHT / 2.));
}

/**
 * @brief Update the menu
 */
void Field::update()
{
}

/**
 * @brief Draw the menu
 */
void Field::draw()
{
    // Drawing the field
    SDL_RenderCopy(Game::renderer, fieldTexture, nullptr, nullptr);

    drawPlayers();
    drawBall();
    drawGoals();
}

/**
 * @brief Draw the players
 */
void Field::drawPlayers()
{
    for (auto& player : players) {
        dstPlayers.x = player->getXOnDraw();
        dstPlayers.y = player->getYOnDraw();
        srcPlayers.x = (player->getTeam() == 0) ? 0 : SRC_PLAYERS_DIMENSIONS_W * 4;
        SDL_RenderCopy(Game::renderer, playersTexture, &srcPlayers, &dstPlayers);
    }
}

/**
 * @brief Draw the ball
 */
void Field::drawBall()
{
    dstBall.x = ball->getXOnDraw();
    dstBall.y = ball->getYOnDraw();
    SDL_RenderCopy(Game::renderer, ballTexture, nullptr, &dstBall);
}

void Field::drawGoals()
{
    for (int i = 0; i < 2; i++) {
        dstGoal.x = goals[i].first->getX() - CONE_RADIUS / 2;
        dstGoal.y = goals[i].first->getY() - CONE_RADIUS / 2;
        SDL_RenderCopy(Game::renderer, blueCone, nullptr, &dstGoal);

        dstGoal.x = goals[i].second->getX() - CONE_RADIUS / 2;
        dstGoal.y = goals[i].second->getY() - CONE_RADIUS / 2;
        SDL_RenderCopy(Game::renderer, yellowCone, nullptr, &dstGoal);
    }
}
