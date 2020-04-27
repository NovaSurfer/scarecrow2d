//
// Created by novasurfer on 4/23/20.
//

#ifndef SCARECROW2D_GAME_MAIN_H
#define SCARECROW2D_GAME_MAIN_H

#include "core/text_ft2.h"
#include "core/texture.h"
#include "core/tiled_map.h"
#include <core/sprite.h>
#include "core/result.h"
#include "menu.h"

enum class GameMode
{
    MENU,
    SCENE
};

struct Game
{
    sc2d::ResultBool init(GameMode start_mode, const math::mat4& proj);
    void draw();
    void destroy();
    void read_input(int key, int action);

    static GameMode mode;

private:
    Menu menu;
    sc2d::Sprite sprite;
    sc2d::tiled::Map tiled_map;
    sc2d::TextureAtlas tex_atlas;
    sc2d::Texture2d logo_texture;
    sc2d::Ft2Font fnt_04b_03;
    sc2d::TextFt2 text_ft2;
};

#endif //SCARECROW2D_GAME_MAIN_H
