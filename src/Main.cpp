#include "../include/Main.hpp"
#include <SDL2/SDL.h>
#include "../include/Game.hpp"
#include "../include/Random.hpp"

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

    int   n     = 10;
    float p     = 0.9;
    int   count = 0;
    for (int i = 0; i < n; i++) {
        std::cout << "random number uniform: " << randomUniformDistribution(0, 50) << std::endl;
    }

    return 1;
}
