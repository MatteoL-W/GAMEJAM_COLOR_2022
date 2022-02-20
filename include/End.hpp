#pragma once

#include <SDL2/SDL.h>
#include <iostream>

class End {
public:
    End();

    ~End() = default;

    void update();

    void draw(int winnerNb);

private:
    SDL_Texture* endBackground1, *endBackground2, *ends[2];

    std::string fileName;
};
