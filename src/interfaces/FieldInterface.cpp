#include "../../include/interfaces/FieldInterface.hpp"
#include <SDL2/SDL.h>

const float FORCE_FACTOR = 4.5;

/**
 * @brief Handle SDL Events in the menu
 */
void FieldInterface::handleEvents()
{
    SDL_Event event = game->getEvent();
    SDL_PollEvent(&event);

    if (field->getFocusedPlayer() != nullptr) {
        if (field->getFocusedPlayer()->isPlayerShooting()) {
            field->shootOfPlayer(field->getFocusedPlayer(), field->getPositionClick());
        }

        float distance = field->getFocusedPlayer()->getPosition().getDistance(field->getPositionMouse());
        switch (event.type) {
        case SDL_MOUSEBUTTONDOWN:
            field->setPositionClick(event.button.x, event.button.y);
            field->intersectBallOfPlayer(field->getFocusedPlayer(), field->getPositionClick());
            field->getFocusedPlayer()->changeSpeed(((distance > 150) ? 150 : distance) / FORCE_FACTOR);
            field->getFocusedPlayer()->getPosition().print();
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
            float mouseX = event.button.x;
            float mouseY = event.button.y;

            for (auto& player : field->getPlayers()) {
                float   radius    = player->getRadius();
                Point2D playerPos = player->getPosition();
                if ((mouseX > playerPos.getX() - radius && mouseX < playerPos.getX() + radius) && (mouseY > playerPos.getY() - radius && mouseY < playerPos.getY() + radius)) {
                    field->setFocusedPlayer(player);
                    field->getFocusedPlayer()->changeSpeed(0.1);
                }
            }
        }

        break;
    }

    if (field->getFocusedPlayer() != nullptr && field->getFocusedPlayer()->getSpeed() == 0) {
        std::cout << "test !!! " << std::endl;
        if (field->getFocusedPlayer()->getGoal() != 0) {
            if (field->getFocusedPlayer()->getGoal() == 1) {
                field->incrementLeftTeamScore();
            }
            else if (field->getFocusedPlayer()->getGoal() == 2) {
                field->incrementRightTeamScore();
            }

            if (field->hasAWinner() != 0) {
                game->setWinner(field->hasAWinner());
                game->endGame();
            }

            field->updateTextOverlay();
            field->playersReactionWhenGoal(field->getFocusedPlayer()->getGoal());
            render();

            SDL_Delay(3000);

            field->resetPlayersReactions();
            field->resetBallPosition();
            field->loadPlayersPattern();
            field->getFocusedPlayer()->setGoal(0);
        }
        field->touchesBallNot();
        field->setFocusedPlayer(nullptr);
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
    if (field->getFocusedPlayer() != nullptr && field->getFocusedPlayer()->getGoal() != 0) {
        field->drawGoalText();
    }

    SDL_RenderPresent(Game::renderer);
}
