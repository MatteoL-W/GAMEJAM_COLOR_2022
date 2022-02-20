#include "../../include/interfaces/FieldInterface.hpp"
#include <SDL2/SDL.h>

/**
 * @brief Handle SDL Events in the menu
 */
void FieldInterface::handleEvents()
{
    SDL_Event event = game->getEvent();
    SDL_PollEvent(&event);

    if (field->getFocusedPlayer() != nullptr) {
        float distance = field->getFocusedPlayer()->getPosition().getDistance(field->getPositionMouse());
        switch (event.type) {
        case SDL_MOUSEBUTTONDOWN:
            field->getFocusedPlayer()->changeSpeed(((distance > 150) ? 150 : distance) / 4.5);
            field->setFocusedPlayer(nullptr);
            break;

        case SDL_MOUSEMOTION:
            field->setPositionMouse(event.button.x, event.button.y);
            break;
        }
    }

    switch (event.type) {
    case SDL_QUIT:
        game->setRunning(false);
        break;

    case SDL_MOUSEBUTTONDOWN:
        if (field->getFocusedPlayer() == nullptr) {
            std::vector<Player*> players = field->getPlayers();
            float                mouseX  = event.button.x;
            float                mouseY  = event.button.y;

            for (auto& player : players) {
                float   radius    = player->getRadius();
                Point2D playerPos = player->getPosition();
                if ((mouseX > playerPos.getX() - radius && mouseX < playerPos.getX() + radius) && (mouseY > playerPos.getY() - radius && mouseY < playerPos.getY() + radius)) {
                    field->setFocusedPlayer(player);
                }
            }
        }

        field->setPositionClick(event.button.x, event.button.y);
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
