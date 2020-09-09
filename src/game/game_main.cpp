//
// Created by novasurfer on 4/23/20.
//

#include "game_main.h"
#include "core/camera.h"
#include "core/input_types.h"
#include "core/log2.h"
#include "core/rendering/texture.h"
#include "core/window.h"
#include "filesystem/resourceHolder.h"
#include "menu.h"
#include <core/dbg/dbg_asserts.h>
#include "core/rendering/renderqueue.h"

GameMode Game::mode;

void Game::init(GameMode start_mode, const sc2d::WindowSize& window_size)
{
    mode = start_mode;

    ///------------- INIT TEST SCENE / LEVEL
    sc2d::Camera camera;
    camera.make_orthographic(window_size.width, window_size.height, sc2d::DEFAULT_Z_NEAR,
                             sc2d::DEFAULT_Z_FAR);

    // REGULAR SPRITE
    const sc2d::Shader& sprite_shader = sc2d::ResourceHolder::get_shader("sprite_default");
    const sc2d::Texture2d& logo_texture = sc2d::ResourceHolder::get_texture("logo");
    sprite.init(sprite_shader);
    sprite.set_color(sc2d::Color::WHITE);
    sprite.set_texture(logo_texture);
    sprite.set_transfdata(math::vec2(0, 0), math::vec2(111, 148), 0, camera.get_proj());

    // SPRITE_SHEEEEEEEEEEET
    const sc2d::Shader& sprite_sheet_shader = sc2d::ResourceHolder::get_shader("spritesheet");
    const sc2d::TextureAtlas tex_atlas = sc2d::ResourceHolder::get_texture_atlas("tilemap");
    tiled_map = sc2d::ResourceHolder::get_tiled_map("wasd");
    tiled_map.init(sprite_sheet_shader, camera.get_proj());
    tiled_map.set_sheet_texture(tex_atlas);

    const sc2d::Shader& font_shader = sc2d::ResourceHolder::get_shader("text_ft2");
    font_shader.run();
    font_shader.set_mat4("projection", camera.get_proj());
    sc2d::Ft2Font fnt_04b_03;
    fnt_04b_03.init("data/fonts/04B_03__.TTF", 48, sc2d::ASCII_TABLE_SIZE);
    text_ft2.init(font_shader, fnt_04b_03);
    text_ft2.set_text("hello. I'm Max.");
    text_ft2.set_pos({100.f, 100.f}, 0);
    text_ft2.set_color(sc2d::Color::CYAN);

    const sc2d::Shader& batched_shader = sc2d::ResourceHolder::get_shader("sprite_batched");
    sprite_batch.init(batched_shader, camera.get_proj());


    render_queue.push(sprite);
    render_queue.push(text_ft2);

    DBG_WARN_ON_RENDER_ERR
}

void Game::draw()
{
    if(mode == GameMode::MENU) {
        menu.draw();
    } else {
        tiled_map.draw_map();
        render_queue.draw();
//        sprite.draw();
//        text_ft2.draw();

        sprite_batch.draw({5,5}, {100, 10}, {1.0, .0f, .0f, 1.0f});
        sprite_batch.draw({100,100}, {100, 100}, {1.0, .0f, 1.0f, 1.0f});
        sprite_batch.draw({50,65}, {10, 10}, {1.0, 1.0f, .0f, 1.0f});
        sprite_batch.draw({500,256}, {50, 50}, {0.0, 0.0f, .0f, 1.0f});
        sprite_batch.flush();
        //    spritesheet->draw(sc2d::ResourceHolder::get_texture_atlas("tilemap"), math::vec2(0, 0),
        //                     math::size2d(16, 16), 0);
    }
}
void Game::destroy()
{
//    text_ft2.destroy();
}
void Game::read_input(int key, int action)
{
    if(key == Key::ESCAPE && action == KeyAction::PRESS) {
        menu.toggle();
    }
}
