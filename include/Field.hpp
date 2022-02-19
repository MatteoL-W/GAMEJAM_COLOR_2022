#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include "Ball.hpp"
#include "Player.hpp"
#include "Text.hpp"

const int SRC_PLAYERS_DIMENSIONS_W = 32;
const int SRC_PLAYERS_DIMENSIONS_H = 44;
const int DST_PLAYERS_DIMENSIONS_W = 46;
const int DST_PLAYERS_DIMENSIONS_H = 64;
const int PLAYERS_FACE_W           = 64;
const int PLAYERS_FACE_H           = 85;
const int BALL_RADIUS              = 32;
const int CONE_RADIUS              = 40;

class Field {
public:
    Field();

    ~Field() = default;

    void loadAssets();

    void initRect();

    void initVectors();

    void loadOverlay();

    void loadPlayersPattern();

    void resetBallPosition();

    void update();

    void draw();

    void drawPlayers();

    void drawBall();

    void drawGoals();

    void drawOverlay();

    void setPositionClick(float x, float y) { positionClick.setPoint(x, y); };

    Point2D getPositionClick() const { return positionClick; };

    std::vector<Player*> getPlayers() const { return players; };

    std::vector<Point2D*> getFieldLimits() const { return fieldLimits; };

    Ball* getBall() const { return ball; };

    Player* getPlayerAt(int i) const { return players[i]; };

    //bouh cracra mais tmp
    Point2D intersection;

private:
    SDL_Texture *playersTexture, *fieldTexture, *ballTexture, *blueCone, *yellowCone, *playersFaceTexture;

    SDL_Rect dstPlayers, srcPlayers, dstBall, dstGoal, overlayRect, srcFace, dstFace;

    Point2D positionClick;

    std::vector<Player*> players;

    std::vector<Point2D*> fieldLimits;

    Ball* ball;

    std::vector<std::pair<Point2D*, Point2D*>> goals;

    int leftTeamScore = 0, rightTeamScore = 0;

    Text *leftTeamScoreText, *rightTeamScoreText;
};
