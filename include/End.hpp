#pragma once

#include <SDL2/SDL.h>
#include <iostream>

class End {
public:
    End();

    ~End() = default;

    void update(int winner);

    void draw();

private:
    SDL_Texture* endBackground;

    std::string fileName;
};
