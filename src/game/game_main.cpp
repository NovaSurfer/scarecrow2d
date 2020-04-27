//
// Created by novasurfer on 4/23/20.
//

#include "game_main.h"
#include "core/input_types.h"
#include "core/log2.h"
#include "filesystem/resourceHolder.h"
#include "menu.h"

GameMode Game::mode;

sc2d::ResultBool Game::init(GameMode start_mode, const math::mat4& proj)
{
    mode = start_mode;

    ///------------- INIT TEST SCENE / LEVEL

    // REGULAR SPRITE
    const sc2d::Shader& sprite_shader = sc2d::ResourceHolder::get_shader("sprite_default");
    logo_texture = sc2d::ResourceHolder::get_texture("logo");
    sprite_shader.run();
    sprite_shader.set_int("image", logo_texture);
    sprite_shader.set_mat4("projection", proj);
    sprite.init(sprite_shader);

    // SPRITE_SHEEEEEEEEEEET
    const sc2d::Shader& sprite_sheet_shader = sc2d::ResourceHolder::get_shader("spritesheet");
    tex_atlas = sc2d::ResourceHolder::get_texture_atlas("tilemap");
    sprite_sheet_shader.run();
    sprite_sheet_shader.set_int("image_array", tex_atlas);
    sprite_sheet_shader.set_mat4("projection", proj);
    tiled_map = sc2d::ResourceHolder::get_tiled_map("wasd");
    tiled_map.init(sprite_sheet_shader);

    const sc2d::Shader& font_shader = sc2d::ResourceHolder::get_shader("text_ft2");
    font_shader.run();
    font_shader.set_mat4("projection", proj);
    font_shader.set_vec3("spriteColor", math::vec3(1.f, 0.0f, 1.0f));
    fnt_04b_03.init("data/fonts/04B_03__.TTF", 48, sc2d::ASCII_TABLE_SIZE);
    text_ft2.init(font_shader, fnt_04b_03);
    text_ft2.set_text("hello. I'm Max.");
    text_ft2.set_pos({100.f, 100.f}, 0.f);

    log_gl_error_cmd();

    return !glGetError() ? (true) : sc2d::ResultBool::throw_err(sc2d::Err::ENGINE_INIT_FAIL);
}

void Game::draw()
{
    if(mode == GameMode::MENU) {
        menu.draw();
    } else {
        tiled_map.draw_map(tex_atlas.get_obj_id());
        sprite.draw(logo_texture.get_obj_id(), math::vec2(0, 0), math::size2d(111, 148), 0);
        text_ft2.draw();
        //    spritesheet->draw(sc2d::ResourceHolder::get_texture_atlas("tilemap"), math::vec2(0, 0),
        //                     math::size2d(16, 16), 0);
    }
}
void Game::destroy()
{
    text_ft2.destroy();
}
void Game::read_input(int key, int action)
{
    if(key == Key::ESCAPE && action == KeyAction::PRESS) {
        menu.toggle();
    }
}
