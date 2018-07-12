#include <SDL_video.h>
#include "game.h"

SDL_Renderer *Game::renderer = nullptr;
SDL_Window *Game::window = nullptr;
std::unique_ptr<InputManager> Game::input_manager = nullptr;
SDL_Event Game::event;

Manager manager;

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    const unsigned short int flags = fullscreen ? SDL_WINDOW_FULLSCREEN | SDL_WINDOW_RESIZABLE : 0;

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << ":: SUBSYSTEMS INITIALIZED ::\n";
        SDL_SetHint (SDL_HINT_RENDER_SCALE_QUALITY, nullptr);
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window)
        {
            std::cout << ":: WINDOW CREATED ::\n";
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer)
        {
//            SDL_RenderSetLogicalSize(renderer, 640, 480);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            std::cout << ":: RENDERER CREATED ::\n";
        }


        isRunning = true;
    } else
    {
        isRunning = false;
    }

    input_manager = std::make_unique<InputManager>();
    levelMap = std::make_shared<LevelMap>();
    auto &player(manager.add_entity());
    player.add_component<Transform>();
    player.get_component<Transform>().set_pos_y(300);
    player.get_component<Transform>().set_pos_x(300);
    player.add_component<InputController>();
    player.add_component<Sprite>("data/sprites/ScareCrow.png");
}

void Game::handle_events()
{
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT)
    {
        isRunning = false;
    }
}

void Game::update()
{
    manager.refresh();
    manager.update();
}

void Game::render()
{
    SDL_RenderClear(renderer);

    levelMap->draw_map();
    manager.draw();

    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    IMG_Quit();
    SDL_Quit();
    std::cout << ":: GAME CLEANED ::\n";
}