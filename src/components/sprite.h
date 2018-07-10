//
// Created by Maksim Ruts on 25-Apr-18.
//

#ifndef INC_2D_ENGINE_SPRITECOMPONENT_H
#define INC_2D_ENGINE_SPRITECOMPONENT_H

#include "../textureManager.h"
#include "components.h"
#include "SDL.h"

class Transform;

class Sprite : public Component {
private:
    Transform *transform;
    SDL_Texture *texture;
    SDL_Surface *surface;
    SDL_Rect srcrect;
    SDL_Rect destrect;
    SDL_Point center;

    void resize_surface();

public:
    Sprite() = default;
    Sprite(const char *path, bool resizable = false);

    void set_texture(const char *path);

    void init() override;
    void update() override;
    void draw() override;

};


#endif //INC_2D_ENGINE_SPRITECOMPONENT_H
