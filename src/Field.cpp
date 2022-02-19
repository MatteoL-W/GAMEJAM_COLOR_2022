#include "../include/Field.hpp"
#include <SDL2/SDL_image.h>
#include <vector>
#include "../include/Game.hpp"
#include "../include/Player.hpp"
#include "../include/Random.hpp"

std::vector<Player*>  players;
std::vector<Point2D*> fieldLimits;

const int xPadding = 58;
const int yPadding = 42;

Field::Field()
{
    loadAndInitialize();
}

/**
 * @brief Load assets and objects
 */
void Field::loadAndInitialize()
{
    // Initializing assets
    fieldTexture          = IMG_LoadTexture(Game::renderer, "assets/images/field.png");
    teamOnePlayersTexture = IMG_LoadTexture(Game::renderer, "assets/images/1_player.png");
    teamTwoPlayersTexture = IMG_LoadTexture(Game::renderer, "assets/images/2_player.png");

    srcPlayers.w = srcPlayers.h = PLAYERS_DIMENSIONS;
    dstPlayers.w = dstPlayers.h = PLAYERS_DIMENSIONS;

    // Initializing vectors
    // set Limit Fields
    fieldLimits.push_back(new Point2D(xPadding, yPadding));
    fieldLimits.push_back(new Point2D(Game::WINDOW_WIDTH - xPadding, yPadding));
    fieldLimits.push_back(new Point2D(Game::WINDOW_WIDTH - xPadding, Game::WINDOW_HEIGHT - yPadding));
    fieldLimits.push_back(new Point2D(xPadding, Game::WINDOW_HEIGHT - yPadding));

    // set Players
    for (int i = 0; i < 8; i++) {
        players.push_back(new Player(PLAYERS_DIMENSIONS / 2, i / 4));
    }

    loadPlayersPattern();
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
    // Drawing the field
    SDL_RenderCopy(Game::renderer, fieldTexture, nullptr, nullptr);

    drawPlayers();
}

/**
 * @brief Draw the players
 */
void Field::drawPlayers()
{
    SDL_Texture* tempTexture = nullptr;
    for (auto& player : players) {
        dstPlayers.x = player->getPosition().getX();
        dstPlayers.y = player->getPosition().getY();
        tempTexture  = (player->getTeam() == 0) ? teamOnePlayersTexture : teamTwoPlayersTexture;
        player->draw(tempTexture, srcPlayers, dstPlayers);
    }
}

/**
 * @brief Place the players depending on pattern
 */
void Field::loadPlayersPattern()
{
    for (int i = 0; i < 8; i++) {
        int team = i / 4;

        players[i]->setPosition(Point2D(
            randomUniformDistribution(xPadding, Game::WINDOW_WIDTH / 2 - xPadding) + (Game::WINDOW_WIDTH / 2 - xPadding) * team,
            yPadding + (i % 4) * (Game::WINDOW_HEIGHT / 4) ));
    }
}