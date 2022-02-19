#include "../include/Field.hpp"
#include <SDL2/SDL_image.h>
#include <math.h>
#include "../include/Random.hpp"
#include "../include/Utils.hpp"
#include "../include/variables/Color.hpp"

const int xPadding = 58;
const int yPadding = 42;

Field::Field()
{
    loadAssets();
    initRect();
    initVectors();

    ball = new Ball(BALL_RADIUS / 2);

    loadOverlay();
    loadPlayersPattern();
    resetBallPosition();
}

/**
 * @brief Load assets
 */
void Field::loadAssets()
{
    blueCone           = IMG_LoadTexture(Game::renderer, "assets/images/cone1.png");
    yellowCone         = IMG_LoadTexture(Game::renderer, "assets/images/cone2.png");
    ballTexture        = IMG_LoadTexture(Game::renderer, "assets/images/ball.png");
    fieldTexture       = IMG_LoadTexture(Game::renderer, "assets/images/field.png");
    playersTexture     = IMG_LoadTexture(Game::renderer, "assets/images/sprite_players.png");
    playersFaceTexture = IMG_LoadTexture(Game::renderer, "assets/images/sprite_players_face.png");
    arrowTexture       = IMG_LoadTexture(Game::renderer, "assets/images/arrow.png");
}

/**
 * @brief Load assets and objects
 */
void Field::initRect()
{
    srcPlayers.w = SRC_PLAYERS_DIMENSIONS_W;
    srcPlayers.h = SRC_PLAYERS_DIMENSIONS_H;

    srcPlayers.y = SRC_PLAYERS_DIMENSIONS_H;
    srcPlayers.x = 0;

    dstPlayers.w = DST_PLAYERS_DIMENSIONS_W;
    dstPlayers.h = DST_PLAYERS_DIMENSIONS_H;

    dstBall.w = dstBall.h = BALL_RADIUS;

    dstGoal.w = dstGoal.h = CONE_RADIUS;

    overlayRect.w = 315;
    overlayRect.h = 90;
    overlayRect.x = getPadding(Game::WINDOW_WIDTH, 315);
    overlayRect.y = Game::WINDOW_HEIGHT - 90;

    dstFace.w = srcFace.w = PLAYERS_FACE_W;
    dstFace.h = srcFace.h = PLAYERS_FACE_H;

    dstArrow.h = 20;
}

/**
 * @brief Initialize field limits, players and goals vector
 */
void Field::initVectors()
{
    // Limit Fields
    fieldLimits.push_back(new Point2D(xPadding, yPadding));
    fieldLimits.push_back(new Point2D(Game::WINDOW_WIDTH - xPadding, yPadding));
    fieldLimits.push_back(new Point2D(Game::WINDOW_WIDTH - xPadding, Game::WINDOW_HEIGHT - yPadding));
    fieldLimits.push_back(new Point2D(xPadding, Game::WINDOW_HEIGHT - yPadding));

    // Players
    for (int i = 0; i < 8; i++) {
        players.push_back(new Player(DST_PLAYERS_DIMENSIONS_H / 2, i / 4));
    }

    // Goals
    int                           goalGap = 100;
    std::pair<Point2D*, Point2D*> tempGoal;
    tempGoal.first  = new Point2D(xPadding, (Game::WINDOW_HEIGHT / 2) - goalGap);
    tempGoal.second = new Point2D(xPadding, (Game::WINDOW_HEIGHT / 2) + goalGap);
    goals.push_back(tempGoal);

    tempGoal.first  = new Point2D(Game::WINDOW_WIDTH - xPadding, (Game::WINDOW_HEIGHT / 2) - goalGap);
    tempGoal.second = new Point2D(Game::WINDOW_WIDTH - xPadding, (Game::WINDOW_HEIGHT / 2) + goalGap);
    goals.push_back(tempGoal);
}

/**
 * @brief Load assets and objects
 */
void Field::loadOverlay()
{
    leftTeamScoreText = new Text();
    leftTeamScoreText->create(std::to_string(leftTeamScore), WhiteColor, "Press");
    leftTeamScoreText->changeDestRect(Game::WINDOW_WIDTH / 2 - 60, Game::WINDOW_HEIGHT - 50);

    rightTeamScoreText = new Text();
    rightTeamScoreText->create(std::to_string(rightTeamScore), WhiteColor, "Press");
    rightTeamScoreText->changeDestRect(Game::WINDOW_WIDTH / 2 + 40, Game::WINDOW_HEIGHT - 50);
}

/**
 * @brief Place the players randomly
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
 * @brief Update the field
 */
void Field::update()
{
}

/**
 * @brief Draw the field
 */
void Field::draw()
{
    // Drawing the background
    SDL_RenderCopy(Game::renderer, fieldTexture, nullptr, nullptr);

    drawPlayers();
    drawBall();
    drawGoals();

    drawOverlay();

    if (focusOn != nullptr) {
        drawArrow();
    }
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

/**
 * @brief Draw the cones
 */
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

/**
 * @brief Draw the score
 */
void Field::drawOverlay()
{
    int gap = 100;
    SDL_SetRenderDrawColor(Game::renderer, 220, 195, 60, 255);
    SDL_RenderFillRect(Game::renderer, &overlayRect);

    dstFace.x = (Game::WINDOW_WIDTH / 2 - PLAYERS_FACE_W / 2) - gap;
    dstFace.y = Game::WINDOW_HEIGHT - PLAYERS_FACE_H;
    srcFace.x = srcFace.y = 0;
    SDL_RenderCopy(Game::renderer, playersFaceTexture, &srcFace, &dstFace);

    dstFace.x += gap * 2;
    srcFace.y = PLAYERS_FACE_H;
    SDL_RenderCopy(Game::renderer, playersFaceTexture, &srcFace, &dstFace);

    rightTeamScoreText->draw();
    leftTeamScoreText->draw();
}
int  angle = 0;
void Field::drawArrow()
{
    int radius = focusOn->getRadius();
    Point2D playerPos = focusOn->getPosition();

    SDL_RendererFlip arrowFlip = SDL_FLIP_NONE;
    SDL_Point        playerPoint;
    (angle++) % 360;

    float distance = playerPos.getDistance(positionMouse);
    dstArrow.w     = (distance > 150) ? 150 : distance;
    dstArrow.h     = 20;
    dstArrow.x     = playerPos.getX() - radius/2 - dstArrow.w / 2;
    dstArrow.y     = playerPos.getY() - dstArrow.h / 2;

    playerPoint.x = dstArrow.w / 2;
    playerPoint.y = dstArrow.h / 2;

    SDL_RenderCopyEx(Game::renderer, arrowTexture, nullptr, &dstArrow, angle, &playerPoint, arrowFlip);
}