//
// Created by Maksim Ruts on 17-Apr-18.
//

#ifndef INC_2D_ENGINE_GAMEOBJECT_H
#define INC_2D_ENGINE_GAMEOBJECT_H

#include "textureManager.h"

class GameObject {
public:
    GameObject(const char* textureSheet, int x, int y);
    ~GameObject() = default;

    void update();
    void render();

private:
    int xpos;
    int ypos;

    SDL_Texture* objTexture;
    SDL_Rect srcRect;
    SDL_Rect destRect;
};


#endif //INC_2D_ENGINE_GAMEOBJECT_H
