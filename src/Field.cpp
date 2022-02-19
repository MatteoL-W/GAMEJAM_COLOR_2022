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
    ballTexture           = IMG_LoadTexture(Game::renderer, "assets/images/ball.png");
    fieldTexture          = IMG_LoadTexture(Game::renderer, "assets/images/field.png");
    teamOnePlayersTexture = IMG_LoadTexture(Game::renderer, "assets/images/1_player.png");
    teamTwoPlayersTexture = IMG_LoadTexture(Game::renderer, "assets/images/2_player.png");

    srcPlayers.w = srcPlayers.h = PLAYERS_DIMENSIONS;
    srcPlayers.x = srcPlayers.y = 0;
    dstPlayers.w = dstPlayers.h = PLAYERS_DIMENSIONS;
    dstBall.w = dstBall.h = BALL_RADIUS;

    // Initializing vectors
    // set Limit Fields
    fieldLimits.push_back(new Point2D(xPadding, yPadding));
    fieldLimits.push_back(new Point2D(Game::WINDOW_WIDTH - xPadding, yPadding));
    fieldLimits.push_back(new Point2D(Game::WINDOW_WIDTH - xPadding, Game::WINDOW_HEIGHT - yPadding));
    fieldLimits.push_back(new Point2D(xPadding, Game::WINDOW_HEIGHT - yPadding));

    // set Players
    for (int i = 0; i < 8; i++) {
        players.push_back(new Player(PLAYERS_DIMENSIONS / 2, i / 4));
    }

    // initialize ball
    ball = new Ball(BALL_RADIUS / 2);

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
                    Game::WINDOW_WIDTH - xPadding),
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
}

/**
 * @brief Draw the players
 */
void Field::drawPlayers()
{
    SDL_Texture* tempTexture = nullptr;
    for (auto& player : players) {
        dstPlayers.x = player->getXOnDraw();
        dstPlayers.y = player->getYOnDraw();
        tempTexture  = (player->getTeam() == 0) ? teamOnePlayersTexture : teamTwoPlayersTexture;
        SDL_RenderCopy(Game::renderer, tempTexture, &srcPlayers, &dstPlayers);
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