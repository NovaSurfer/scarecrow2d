//
// Created by Maksim Ruts on 25-Apr-18.
//

#ifndef INC_2D_ENGINE_SPRITECOMPONENT_H
#define INC_2D_ENGINE_SPRITECOMPONENT_H

#include "../textureManager.h"
#include "SDL.h"
#include "components.h"

class Transform;

class Sprite : public Component
{
private:
    Transform* transform = nullptr;
    SDL_Texture* texture = nullptr;
    SDL_Rect srcrect;
    SDL_Rect destrect;
    SDL_Point pivot;

public:
    explicit Sprite(std::string_view path);
    void set_texture(std::string_view path);

    SDL_Surface* scaled_copy(SDL_Surface* src, SDL_Rect* dstSize);

    void resize(const SDL_Point dest_size);
    void init() override;
    void update() override;
    void draw() override;

    void calc_pivot();
};

#endif //INC_2D_ENGINE_SPRITECOMPONENT_H
