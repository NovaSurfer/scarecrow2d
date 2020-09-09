//
// Created by novasurfer on 4/23/20.
//

#ifndef SCARECROW2D_GAME_MAIN_H
#define SCARECROW2D_GAME_MAIN_H

#include "core/rendering/scene/text_ft2.h"
#include "core/rendering/scene/tiled_map.h"
#include "menu.h"
#include <core/rendering/renderqueue.h>
#include <core/rendering/scene/sprite.h>
#include <core/rendering/scene/spritebatch.h>

enum class GameMode
{
    MENU,
    SCENE
};

namespace sc2d
{
    class WindowSize;
}

struct Game
{
    void init(GameMode start_mode, const sc2d::WindowSize& size);
    void draw();
    void destroy();
    void read_input(int key, int action);

    static GameMode mode;

private:
    Menu menu;
    sc2d::Sprite sprite;
    sc2d::SpriteBatch sprite_batch;
    sc2d::tiled::Map tiled_map;
    sc2d::TextFt2 text_ft2;
    sc2d::RenderQueue render_queue;
};

#endif //SCARECROW2D_GAME_MAIN_H
