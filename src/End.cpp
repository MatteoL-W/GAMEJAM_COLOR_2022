#include <SDL2/SDL_image.h>
#include "../include/End.hpp"
#include "../include/Game.hpp"

End::End()
{
    endBackground1 = IMG_LoadTexture(Game::renderer,"assets/images/end_player1_win.png");
    endBackground2 = IMG_LoadTexture(Game::renderer,"assets/images/end_player2_win.png");
    ends[0] = endBackground1;
    ends[1] = endBackground2;
}

/**
 * @brief Update the end
 */
void End::update()
{
}

/**
 * @brief Draw the ending
 */
void End::draw(int winnerNb)
{
    SDL_RenderCopy(Game::renderer, ends[winnerNb - 1], nullptr, nullptr);
}
