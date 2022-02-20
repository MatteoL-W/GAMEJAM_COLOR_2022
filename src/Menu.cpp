#include <SDL2/SDL_image.h>
#include "../include/Menu.hpp"
#include "../include/Game.hpp"

Menu::Menu()
{
    homeBackground = IMG_LoadTexture(Game::renderer, "assets/images/home.png");
    rulesBackground = IMG_LoadTexture(Game::renderer, "assets/images/rules.png");
}

/**
 * @brief Update the menu
 */
void Menu::update()
{
}

/**
 * @brief Draw the home
 */
void Menu::drawHome()
{
    SDL_RenderCopy(Game::renderer, homeBackground, nullptr, nullptr);
}

/**
 * @brief Draw the rules
 */
void Menu::drawRules()
{
    SDL_RenderCopy(Game::renderer, rulesBackground, nullptr, nullptr);
}