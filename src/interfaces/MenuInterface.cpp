#include "../../include/interfaces/MenuInterface.hpp"
#include <SDL2/SDL.h>

/**
 * @brief Handle SDL Events in the menu
 */
void MenuInterface::handleEvents()
{
    SDL_Event event = game->getEvent();
    SDL_PollEvent(&event);

    switch (event.type) {
    case SDL_QUIT:
        game->setRunning(false);
        break;

    case SDL_KEYDOWN:
        if (inHome) {
            inHome = false;
        } else {
            game->setInterfaceToField();
        }
        break;
    }


}

/**
 * @brief Update the menu
 */
void MenuInterface::update()
{
    menu->update();
}

/**
 * @brief Render the menu
 */
void MenuInterface::render()
{
    SDL_RenderClear(Game::renderer);

    if (inHome) {
        menu->drawHome();
    } else {
        menu->drawRules();
    }


    SDL_RenderPresent(Game::renderer);
}
