#include "../include/Field.hpp"
#include <SDL2/SDL_image.h>
#include <cmath>
#include "../include/Random.hpp"
#include "../include/Utils.hpp"
#include "../include/variables/Color.hpp"

Field::Field()
{
    loadAssets();
    initRect();
    initVectors();

    ball = new Ball(BALL_RADIUS / 2);
    intersection.setPoint(2000, 2000);

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

    dstFace1.w = srcFace1.w = dstFace2.w = srcFace2.w = PLAYERS_FACE_W;
    dstFace1.h = srcFace1.h = dstFace2.h = srcFace2.h = PLAYERS_FACE_H;
    srcFace1.x = srcFace1.y = srcFace2.x = 0;
    dstFace1.y = dstFace2.y = Game::WINDOW_HEIGHT - PLAYERS_FACE_H;
    srcFace2.y              = PLAYERS_FACE_H;

    dstArrow.h = 20;
}

/**
 * @brief Initialize field limits, players and goals vector
 */
void Field::initVectors()
{
    // Limit Fields
    fieldLimits.push_back(new Point2D(Game::xPadding, Game::yPadding));
    fieldLimits.push_back(new Point2D(Game::WINDOW_WIDTH - Game::xPadding, Game::yPadding));
    fieldLimits.push_back(new Point2D(Game::WINDOW_WIDTH - Game::xPadding, Game::WINDOW_HEIGHT - Game::yPadding));
    fieldLimits.push_back(new Point2D(Game::xPadding, Game::WINDOW_HEIGHT - Game::yPadding));

    // Players
    for (int i = 0; i < 8; i++) {
        players.push_back(new Player(DST_PLAYERS_DIMENSIONS_H / 2, i / 4));
    }

    // Goals
    int                           goalGap = 100;
    std::pair<Point2D*, Point2D*> tempGoal;
    tempGoal.first  = new Point2D(Game::xPadding, (Game::WINDOW_HEIGHT / 2) - goalGap);
    tempGoal.second = new Point2D(Game::xPadding, (Game::WINDOW_HEIGHT / 2) + goalGap);
    goals.push_back(tempGoal);

    tempGoal.first  = new Point2D(Game::WINDOW_WIDTH - Game::xPadding, (Game::WINDOW_HEIGHT / 2) - goalGap);
    tempGoal.second = new Point2D(Game::WINDOW_WIDTH - Game::xPadding, (Game::WINDOW_HEIGHT / 2) + goalGap);
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

    goalText = new Text();
    goalText->create("GOAL !!!!!", WhiteColor, "Press");
    goalText->changeFont("Press", 40);
    goalText->changeDestRect(Game::WINDOW_WIDTH / 2 - goalText->getDestRect().w, Game::WINDOW_HEIGHT / 2 - goalText->getDestRect().h);
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
                    Game::xPadding + radius,
                    Game::WINDOW_WIDTH / 2 - 110),
                (Game::yPadding + radius + 20) + i * (Game::WINDOW_HEIGHT / 4)));
        }
        else {
            players[i]->setPosition(Point2D(
                randomUniformDistribution(
                    Game::xPadding + radius + Game::WINDOW_WIDTH / 2,
                    Game::WINDOW_WIDTH - Game::xPadding - radius),
                (Game::yPadding + radius + 20) + (i % 4) * (Game::WINDOW_HEIGHT / 4)));
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
    int gap    = 100;
    int center = (Game::WINDOW_WIDTH / 2 - PLAYERS_FACE_W / 2);
    SDL_SetRenderDrawColor(Game::renderer, 220, 195, 60, 255);
    SDL_RenderFillRect(Game::renderer, &overlayRect);

    dstFace1.x = center - gap;
    SDL_RenderCopy(Game::renderer, playersFaceTexture, &srcFace1, &dstFace1);

    dstFace2.x = center + gap;
    srcFace2.y = PLAYERS_FACE_H;
    SDL_RenderCopy(Game::renderer, playersFaceTexture, &srcFace2, &dstFace2);

    rightTeamScoreText->draw();
    leftTeamScoreText->draw();
}

/**
 * @brief Draw the directional arrow
 */
void Field::drawArrow()
{
    int     radius    = focusOn->getRadius();
    Point2D playerPos = focusOn->getPosition();

    SDL_RendererFlip arrowFlip = SDL_FLIP_NONE;
    SDL_Point        playerPoint;

    float distance = playerPos.getDistance(positionMouse);
    int   angle    = std::atan2(positionMouse.getY() - playerPos.getY(), positionMouse.getX() - playerPos.getX()) * (180 / M_PI);

    dstArrow.w = (distance > 150) ? 150 : distance;
    dstArrow.h = 20;
    dstArrow.x = playerPos.getX() - radius / 2 - dstArrow.w / 2;
    dstArrow.y = playerPos.getY() - dstArrow.h / 2;

    playerPoint.x = dstArrow.w / 2;
    playerPoint.y = dstArrow.h / 2;

    SDL_RenderCopyEx(Game::renderer, arrowTexture, nullptr, &dstArrow, angle, &playerPoint, arrowFlip);
}

/**
 * @brief Refresh the score
 */
void Field::updateTextOverlay()
{
    leftTeamScoreText->changeText(std::to_string(leftTeamScore));
    rightTeamScoreText->changeText(std::to_string(rightTeamScore));
}

/**
 * @brief Makes players react to the goal
 * @param playerWhoGoal
 */
void Field::playersReactionWhenGoal(int playerWhoGoal)
{
    if (playerWhoGoal == 1) {
        srcFace1.x = PLAYERS_FACE_W;
        srcFace2.x = PLAYERS_FACE_W * 2;
    }
    else {
        srcFace1.x = PLAYERS_FACE_W * 2;
        srcFace2.x = PLAYERS_FACE_W;
    }
}
