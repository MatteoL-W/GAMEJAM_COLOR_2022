#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include "Ball.hpp"
#include "Player.hpp"

const int PLAYERS_DIMENSIONS = 64;
const int BALL_RADIUS        = 32;

class Field {
public:
    Field();

    ~Field() = default;

    void loadAndInitialize();

    void loadPlayersPattern();

    void resetBallPosition();

    void update();

    void draw();

    void drawPlayers();

    void drawBall();

    void setPositionClick(float x, float y) { positionClick.setPoint(x, y); };

    std::vector<Player*>  getPlayers() const { return players; };
    std::vector<Point2D*> getFieldLimits() const { return fieldLimits; };
    Ball*                 getBall() const { return ball; };

private:
    SDL_Texture *teamOnePlayersTexture, *teamTwoPlayersTexture, *fieldTexture, *ballTexture;

    SDL_Rect dstPlayers, srcPlayers, dstBall;

    Point2D positionClick;

    std::vector<Player*>  players;
    std::vector<Point2D*> fieldLimits;
    Ball*                 ball;
};
