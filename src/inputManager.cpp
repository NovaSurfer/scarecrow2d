//
// Created by maksim on 6/10/18.
//

#include "inputManager.h"

InputManager::InputManager() try
{
    IniIO config("config.ini");
    key_values = config.get_kvps("binds");

    for(const auto& kv : key_values)
    {
        key_names[kv.first] = kv.second;
    }

} catch (const std::exception& e)
{
    std::cerr << e.what() << "\n";
    //TODO: window with error message (config.ini cannot be open)
}

bool InputManager::get_key_down(const std::string &key)
{
    if(Game::event.type == SDL_KEYDOWN)
    {
        return is_same_key(key);
    }
}


bool InputManager::get_key_up(const std::string &key)
{
    if(Game::event.type == SDL_KEYUP)
    {
        return is_same_key(key);
    }
}

bool InputManager::is_same_key(const std::string &key)
{
    std::string current_key_name = SDL_GetKeyName(Game::event.key.keysym.sym);
    return current_key_name == key_names[key];
}