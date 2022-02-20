#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include "Interface.hpp"

class Game {
public:
    Game();

    ~Game();

    void clean();

    void refresh();

    static const int WINDOW_WIDTH = 1350;

    static const int WINDOW_HEIGHT = 750;

    static SDL_Renderer* renderer;

    void setInterfaceToField();

    void setRunning(bool newState) { isRunning = newState; }

    bool running() const { return isRunning; };

    Interface* getCurrentInterface() { return currentInterface; };

    SDL_Event getEvent() const { return event; };

    int getWinner() { return *winner; };

private:
    SDL_Window* window;

    bool isRunning = false;

    Interface* currentInterface;

    SDL_Event event;

    int* winner = nullptr;
};
