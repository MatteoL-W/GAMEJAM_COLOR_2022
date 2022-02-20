#include "../../include/interfaces/EndInterface.hpp"
#include <SDL2/SDL.h>

/**
 * @brief Handle SDL Events in the menu
 */
void EndInterface::handleEvents()
{
    SDL_Event event = game->getEvent();
    SDL_PollEvent(&event);

    switch (event.type) {
    case SDL_QUIT:
    case SDL_KEYDOWN:
    case SDL_MOUSEBUTTONDOWN:
        game->setRunning(false);
        break;
    }
}

/**
 * @brief Update the menu
 */
void EndInterface::update()
{
    end->update();
}

/**
 * @brief Render the menu
 */
void EndInterface::render()
{
    SDL_RenderClear(Game::renderer);

    end->draw(game->getWinner());

    SDL_RenderPresent(Game::renderer);
}
