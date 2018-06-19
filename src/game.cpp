#include "game.h"

SDL_Renderer *Game::renderer = nullptr;
SDL_Window *Game::window = nullptr;
InputManager *Game::input_manager = nullptr;
SDL_Event Game::event;

Manager manager;

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    const unsigned short int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << ":: SUBSYSTEMS INITIALIZED ::" << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window)
        {
            std::cout << ":: WINDOW CREATED ::" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            std::cout << ":: RENDERER CREATED ::" << std::endl;
        }

        input_manager = new InputManager();

        isRunning = true;
    } else
    {
        isRunning = false;
    }

    levelMap = std::make_shared<LevelMap>();
    auto &player(manager.add_entity());
    player.add_component<Transform>();
    player.add_component<InputController>();
    player.add_component<Sprite>("data/sprites/character/engineer-idle.png");
}

void Game::handle_events()
{
    SDL_PollEvent(&event);

    if(event.type == SDL_QUIT)
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
    std::cout << ":: GAME CLEANED ::" << std::endl;
}