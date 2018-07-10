#include "game.h"

#undef main

int main()
{
    // TODO: fix main loop
    constexpr uint32_t FPS = 60;
    constexpr uint32_t frameDelay = 1000 / FPS;
    uint32_t frameStart = 0;
    int frameTime = 0;

    std::unique_ptr<Game> game = std::make_unique<Game>();
    game->init("2D Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

    while (game->running())
    {
        frameStart = SDL_GetTicks();

        game->handle_events();
        game->update();
        game->render();
        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);

        }
    }

    game->clean();
    return 0;
}