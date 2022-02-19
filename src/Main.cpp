#include "../include/Main.hpp"
#include <SDL2/SDL.h>
#include "../include/Game.hpp"
#include "../include/Geometry.hpp"

Game* game = nullptr;

int main(int argc, char* argv[])
{
    // game = new Game();

    // while (game->running()) {
    //     Uint32 frameStart = SDL_GetTicks();

    //     game->refresh();

    //     // FPS Handle (custom in Main.hpp)
    //     int frameTime = SDL_GetTicks() - frameStart;
    //     if (FRAME_DELAY > frameTime) {
    //         SDL_Delay(FRAME_DELAY - frameTime);
    //     }
    // }

    Point2D circleOrigin(0, 1);
    Point2D position(-1, 0);
    Point2D direction(1, 0);
    Point2D intersect;
    intersectCircle(circleOrigin, 1, position, direction, intersect);

    return 1;
}
