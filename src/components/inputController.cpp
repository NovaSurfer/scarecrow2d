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
    if(Game::input_manager->get_key_down("forward"))
    {
        transform->set_pos_y(-3);
    }
    if(Game::input_manager->get_key_down("backward"))
    {
        transform->set_pos_y(3);
    }
    if(Game::input_manager->get_key_up("forward"))
    {
        transform->set_pos_y(0);
    }
    if(Game::input_manager->get_key_up("backward"))
    {
        transform->set_pos_y(0);
    }
    if(Game::input_manager->get_key_down("rotateLeft"))
    {
        transform->rotate(-5);
    }
    if(Game::input_manager->get_key_down("rotateRight"))
    {
        transform->rotate(5);
    }

        /*    case SDLK_ESCAPE:
                SDL_Window *window = Game::get_window();
                int flags = SDL_GetWindowDisplayIndex(window);
                std::cout << SDL_WINDOW_FULLSCREEN << std::endl;
                std::cout << flags << std::endl;
                if (flags == SDL_WINDOW_FULLSCREEN)
                {
                    SDL_SetWindowFullscreen(window, 0);
                } else if (flags == 0)
                {
                    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
                } else
                {
                    std::cout << SDL_GetError();
                }
                break;*/
}

