#include "../include/Game.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "../include/interfaces/MenuInterface.hpp"
#include "../include/interfaces/FieldInterface.hpp"
#include "../include/interfaces/EndInterface.hpp"

SDL_Renderer* Game::renderer = nullptr;

MenuInterface* menuInterface = nullptr;
FieldInterface* fieldInterface = nullptr;
EndInterface* endInterface = nullptr;

/**
 * @brief Initialize the game (assign the window, renderer, define the game as running)
 */
Game::Game()
{
    /* Vérifications */
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "SDL_INIT HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
        exit(1);
    }

    if (!IMG_Init(IMG_INIT_PNG)) {
        std::cout << "IMG_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
        exit(1);
    }

    if (TTF_Init() < 0) {
        std::cout << "TTF_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
        exit(1);
    }

    /* Create SDL needs */
    window   = SDL_CreateWindow("Change the name", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                                WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);

    /* Define the interfaces */
    menuInterface = new MenuInterface(this);
    fieldInterface = new FieldInterface(this);
    endInterface = new EndInterface(this);

    /* Define the default interface*/
    currentInterface = menuInterface;

    isRunning = true;
}

Game::~Game() = default;

/**
 * @brief Quit the game properly
 */
void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

/**
 * @brief Refresh the game and chose the right interface
 */
void Game::refresh()
{
    currentInterface->handleEvents();
    currentInterface->update();
    currentInterface->render();
}

/**
 * @brief Set the interface to field
 */
void Game::setInterfaceToField()
{
    currentInterface = fieldInterface;
}

/**
 * @brief Set the interface to field
 */
void Game::endGame()
{
    currentInterface = endInterface;
}
