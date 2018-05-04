//
// Created by maksim on 4/29/18.
//

#include "inputController.h"

void InputController::init()
{
    transform = &entity->get_component<Transform>();
}

void InputController::update()
{
    if (Game::event.type == SDL_KEYDOWN)
    {
        switch (Game::event.key.keysym.sym)
        {
            case SDLK_w:
                transform->velocity.y = -1;
                break;
            case SDLK_s:
                transform->velocity.y = 1;
                break;
            case SDLK_a:
                transform->velocity.x = -1;
                break;
            case SDLK_d:
                transform->velocity.x = 1;
                break;
            default:
                break;
        }
    }
    if (Game::event.type == SDL_KEYUP)
    {
        switch (Game::event.key.keysym.sym)
        {
            case SDLK_w:
                transform->velocity.y = 0;
                break;
            case SDLK_s:
                transform->velocity.y = 0;
                break;
            case SDLK_a:
                transform->velocity.x = 0;
                break;
            case SDLK_d:
                transform->velocity.x = 0;
                break;
            case SDLK_ESCAPE:
                SDL_Window *window = Game::get_window();
                uint32_t flags = SDL_GetWindowFlags(window);

                std::cout << flags << std::endl;
                if (flags == SDL_WINDOW_FULLSCREEN)
                {
                    SDL_SetWindowFullscreen(window, 0);
                } else if (flags == 0)
                {
                    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
                }
                break;
        }
    }
}

