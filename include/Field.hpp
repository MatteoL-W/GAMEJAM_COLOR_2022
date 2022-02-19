#pragma once

#include <SDL2/SDL.h>

const int PLAYERS_DIMENSIONS = 64;
const int BALL_RADIUS = 32;

class Field {
public:
    Field();

    ~Field() = default;

    void loadAndInitialize();

    static void loadPlayersPattern();

    static void resetBallPosition();

    void update();

    void draw();

    void drawPlayers();

    void drawBall();

private:
    SDL_Texture* teamOnePlayersTexture, *teamTwoPlayersTexture, *fieldTexture, *ballTexture;

    SDL_Rect dstPlayers, srcPlayers, dstBall;
};
