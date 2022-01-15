//
// Created by novasurfer on 4/22/21.
//
#include "core/glfw_base/glfwbase.h"
#include "core/glfw_base/sctime.h"
#include "core/glfw_base/window.h"
#include "game_main.h"
#include <core/input.h>
#include <core/resources.h>
#include <core/result.h>
#include "core/rendering/render.h"
#include <memory>

std::unique_ptr<sc2d::Window> window;
constexpr const sc2d::WindowData window_data {3,
                                              3,
                                              static_cast<int>(sc2d::GlProfile::CORE),
                                              {800,
                                               600},
                                              "scarecrow2d",
                                              sc2d::GlfwWindowUtils::GL_frambuffer_resize,
                                              sc2d::Input::read};

// Glad loads OpenGL functions pointers
//    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//        exit(-1);
//    }

int main()
{
    const sc2d::Render<sc2d::opengl_render> opengl_render;
    sc2d::GlfwBase::init();
    window = std::make_unique<sc2d::Window>(window_data, true);
    opengl_render.create(&window_data.size);
    sc2d::Resources::load_all();
    Game* game = new Game();
    GameMode game_mode = GameMode::SCENE;
    game->init(game_mode, window_data.size);

    // TODO:
    //glfwSetWindowUserPointer(window->get_window(), &game);


    // TODO: Make class for time management
    double begin_ticks = sc2d::Time::get_time();
    double end_ticks = 0;
    double delta_time = 1.0 / 60.0;

    // Game loop
    while(!window->should_close()) {
        window->poll_events();
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        game->draw();
        window->swap_buffers();
        end_ticks = sc2d::Time::get_time();
        delta_time = (begin_ticks - end_ticks) / sc2d::Time::get_time();

#ifndef NDEBUG
        // If delta_time is too large, we must have resumed from a
        // breakpoint -- frame-lock to the target rate this frame.
        if(delta_time > 1.0) {
            delta_time = 1.0 / 60.0;
        }
#endif
        begin_ticks = end_ticks;
    }
    //game->read_input();
    game->destroy();
    delete game;
    return 0;
}