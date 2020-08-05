//
// Created by novasurfer on 4/23/20.
//

#ifndef SCARECROW2D_GAME_MAIN_H
#define SCARECROW2D_GAME_MAIN_H

#include "core/text_ft2.h"
#include "core/tiled_map.h"
#include "menu.h"
#include <core/sprite.h>
#include <core/spritebatch.h>

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
};

#endif //SCARECROW2D_GAME_MAIN_H
