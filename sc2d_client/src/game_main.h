//
// Created by novasurfer on 4/23/20.
//

#ifndef SCARECROW2D_GAME_MAIN_H
#define SCARECROW2D_GAME_MAIN_H

#include "core/rendering/scene/text_ft2.h"
#include "core/rendering/scene/tiled_map.h"
#include <core/glfw_base/window.h>
#include <core/input.h>
#include <core/rendering/renderqueue.h>
#include <core/rendering/scene/sprite.h>
#include <core/rendering/scene/spritebatch.h>

namespace sc2d
{
    struct WindowSize;
}

struct Game
{
    void init(const sc2d::Window& window, const sc2d::WindowSize& size);
    void draw();
    void update(double dt);
    void destroy();

private:
    sc2d::Sprite sprite;
    sc2d::SpriteBatch sprite_batch;
    sc2d::tiled::Map tiled_map;
    sc2d::TextFt2 text_ft2;
    sc2d::RenderQueue render_queue;
    sc2d::Input* input;
};

#endif //SCARECROW2D_GAME_MAIN_H
