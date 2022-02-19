#pragma once

#include <SDL2/SDL.h>

const int PLAYERS_DIMENSIONS = 64;

class Field {
public:
    Field();

    ~Field() = default;

    void loadAndInitialize();

    void update();

    void draw();

    void drawPlayers();

    void loadPlayersPattern();

private:
    SDL_Texture* teamOnePlayersTexture, *teamTwoPlayersTexture, *fieldTexture;

    SDL_Rect dstPlayers, srcPlayers;
};
