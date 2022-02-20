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
const int PLAYERS_FACE_W           = 60;
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

    void drawArrow();

    void drawGoalText() { goalText->draw(); };

    void setPositionClick(float x, float y) { positionClick.setPoint(x, y); };

    Point2D getPositionClick() const { return positionClick; };

    std::vector<Player*> getPlayers() const { return players; };

    void setPositionMouse(float x, float y) { positionMouse.setPoint(x, y); };

    Point2D getPositionMouse() { return positionMouse; };

    std::vector<Point2D*> getFieldLimits() const { return fieldLimits; };

    Ball* getBall() const { return ball; };

    Player* getFocusedPlayer() { return focusOn; };

    void setFocusedPlayer(Player* player) { focusOn = player; };

    void incrementLeftTeamScore() { leftTeamScore++; };

    void incrementRightTeamScore() { rightTeamScore++; };

    void updateTextOverlay();

    void playersReactionWhenGoal(int playerWhoGoal);

    void resetPlayersReactions() { srcFace2.x = srcFace1.x = 0; };

    Player getPlayerAt(Player* player) const { return *(player); };

    void intersectBallOfPlayer(Player* player, const Point2D& positionClick)
    {
        if (player->intersectBall(positionClick, *ball, players, fieldLimits, intersection)) {
            touchesBall = true;
        }
    };

    void touchesBallNot() {touchesBall = false;};

    void shootOfPlayer(Player* player, const Point2D& positionClick) { player->shoot(positionClick, *ball, touchesBall, players, fieldLimits, intersection); };

    bool isPlayerShootingAt(Player* player) { player->isPlayerShooting(); };

    int getGoalAt(Player* player) { player->getGoal(); };

    // bouh cracra mais tmp
    Point2D intersection;

private:
    SDL_Texture *playersTexture, *fieldTexture, *ballTexture, *blueCone, *yellowCone, *playersFaceTexture, *arrowTexture;

    SDL_Rect dstPlayers, srcPlayers, dstBall, dstGoal, overlayRect, srcFace1, dstFace1, srcFace2, dstFace2, dstArrow;

    Point2D positionClick, positionMouse;

    std::vector<Player*> players;

    std::vector<Point2D*> fieldLimits;

    Ball* ball;

    std::vector<std::pair<Point2D*, Point2D*>> goals;

    int leftTeamScore = 0, rightTeamScore = 0;

    Text *leftTeamScoreText, *rightTeamScoreText, *goalText;

    Player* focusOn = nullptr;

    bool touchesBall;
};
