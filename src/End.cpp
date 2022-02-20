#include <SDL2/SDL_image.h>
#include "../include/End.hpp"
#include "../include/Game.hpp"

End::End()
{
    endBackground = IMG_LoadTexture(Game::renderer, fileName.c_str());
}

/**
 * @brief Update the end
 */
void End::update(int winner)
{
    fileName = "assets/images/end_player" + std::to_string(winner) + "_win.png";
}

/**
 * @brief Draw the ending
 */
void End::draw()
{
    SDL_RenderCopy(Game::renderer, endBackground, nullptr, nullptr);
}
