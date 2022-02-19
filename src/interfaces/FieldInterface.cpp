#include "../../include/interfaces/FieldInterface.hpp"
#include <SDL2/SDL.h>

/**
 * @brief Handle SDL Events in the menu
 */
void FieldInterface::handleEvents()
{
    SDL_Event event = game->getEvent();
    SDL_PollEvent(&event);

    switch (event.type) {
    case SDL_QUIT:
        game->setRunning(false);
        break;

    case SDL_MOUSEBUTTONUP:
        field->setPositionClick(event.button.x, event.button.y);
        field->getPlayerAt(5)->intersectBall(field->getPositionClick(), *(field->getBall()), field->getPlayers(),
                                             field->getFieldLimits(), field->intersection);
        break;
    }
}

/**
 * @brief Update the menu
 */
void FieldInterface::update()
{
    field->update();
}

/**
 * @brief Render the menu
 */
void FieldInterface::render()
{
    SDL_RenderClear(Game::renderer);

    field->draw();

    SDL_RenderPresent(Game::renderer);
}
