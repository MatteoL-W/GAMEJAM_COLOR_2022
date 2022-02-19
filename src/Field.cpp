#include "../include/Field.hpp"
#include <SDL2/SDL_image.h>
#include <vector>
#include "../include/Game.hpp"
#include "../include/Player.hpp"

std::vector<Player*> players;

Field::Field()
{
    loadAndInitialize();
}

/**
 * @brief Load assets and objects
 */
void Field::loadAndInitialize()
{
    teamOnePlayersTexture = IMG_LoadTexture(Game::renderer, "assets/images/1_player.png");
    teamTwoPlayersTexture = IMG_LoadTexture(Game::renderer, "assets/images/2_player.png");

    srcPlayers.w = srcPlayers.h = PLAYERS_DIMENSIONS;
    dstPlayers.w = dstPlayers.h = PLAYERS_DIMENSIONS;

    for (int i = 0; i < 8; i++) {
        players.push_back(new Player(PLAYERS_DIMENSIONS / 2, i / 4));
    }
}

/**
 * @brief Update the menu
 */
void Field::update()
{
}

/**
 * @brief Draw the menu
 */
void Field::draw()
{
    drawPlayers();
}

/**
 * @brief Draw the players
 */
void Field::drawPlayers()
{
    SDL_Texture* tempTexture = nullptr;
    for (size_t i = 0; i < players.size(); i++) {
        dstPlayers.x = PLAYERS_DIMENSIONS * i;
        tempTexture = (players[i]->getTeam() == 0) ? teamOnePlayersTexture : teamTwoPlayersTexture;
        players[i]->draw(tempTexture, srcPlayers, dstPlayers);
    }
}