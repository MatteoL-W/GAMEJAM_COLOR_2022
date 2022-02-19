#include "../../include/interfaces/FieldInterface.hpp"
#include <SDL2/SDL.h>

Point2D intersection;

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
        field->getPlayerAt(0)->intersectBall(field->getPositionClick(), *(field->getBall()), field->getPlayers(),
                                             field->getFieldLimits(), intersection);
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
