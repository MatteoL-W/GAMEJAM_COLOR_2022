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
        float distance = field->getFocusedPlayer()->getPosition().getDistance(field->getPositionMouse());
        switch (event.type) {
        case SDL_MOUSEBUTTONDOWN:
            field->intersectBallOfPlayer(0, field->getPositionClick());
            field->getFocusedPlayer()->changeSpeed(((distance > 150) ? 150 : distance) / FORCE_FACTOR);
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

//    case SDL_MOUSEBUTTONUP:
//        field->setPositionClick(event.button.x, event.button.y);
//        field->intersectBallOfPlayer(0, field->getPositionClick());
//        break;

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

    // if is shooting, call shoot function
    // else, field->verifGoalAt(player), if goal == 0, pas de but, si goal == 1, but à gauche, sinon but à droite
    if (field->isPlayerShootingAt(0)) {
        field->shootOfPlayer(0, field->getPositionClick());
    }
    else {
        //        if (goal != 0) {
        //            if (goal == 1) {
        //                field->incrementLeftTeamScore();
        //            } else if (goal == 2) {
        //                field->incrementRightTeamScore();
        //            }
        //
        //            field->updateTextOverlay();
        //            field->playersReactionWhenGoal(goal);
        //            render();
        //
        //            SDL_Delay(3000);
        //
        //            field->resetPlayersReactions();
        //            field->resetBallPosition();
        //            field->loadPlayersPattern();
        //            goal = 0;
        //        }
        // std::cout << " goal : " << field->getGoalAt(field->getFocusedPlayer()) << std::endl;
        // std::cout << field->getFocusedPlayer();
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
    //    if (goal != 0) {
    //        field->drawGoalText();
    //    }

    SDL_RenderPresent(Game::renderer);
}
