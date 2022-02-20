#include "../../include/interfaces/FieldInterface.hpp"
#include <SDL2/SDL.h>

Point2D direction(0, 0);

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
        field->intersectBallOfPlayer(0, field->getPositionClick());
        Point2D click = field->getPositionClick();
        direction     = field->getPlayerAt(0).getPosition().getDirection(click);
        break;
    }

    if (field->isPlayerShootingAt(0)) {
        field->shootOfPlayer(0, direction, field->getPositionClick());
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
