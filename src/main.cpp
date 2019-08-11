//
// Created by Maksim Ruts on 28-Aug-18.
//

#include "core/log2.h"
#include "core/sprite.h"
#include "core/sprite_sheet.h"
#include "core/window.h"
#include "filesystem/configLoader.h"
#include "filesystem/resourceHolder.h"
#include "math/transform.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

std::unique_ptr<Window> window;
std::unique_ptr<sc2d::Sprite> sprite;
std::unique_ptr<sc2d::SpriteSheet> spritesheet;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

bool engine_init()
{
    return sc2d::Config<sc2d::ResourcesConfigLoad>::open("resources.json") &&
           sc2d::Config<sc2d::SceneConfigLoad>::open("data/scenes/zone.json");
}

int init()
{
    glfwInit();

    const WindowData window_data {3,
                                  3,
                                  GLFW_OPENGL_CORE_PROFILE,
                                  800,
                                  600,
                                  "scarecrow2d",
                                  framebuffer_size_callback,
                                  key_callback};
    window = std::make_unique<Window>(window_data, true);

    // Glad loads OpenGL functions pointers
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Loading engine systems
    if(!engine_init())
        return -2;

    glViewport(0, 0, window_data.screen_width, window_data.screen_height);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    //    glFrontFace(GL_CCW);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_SCISSOR_TEST);

    math::mat4 proj =
        math::ortho(0.0f, static_cast<GLfloat>(window_data.screen_width),
                    static_cast<GLfloat>(window_data.screen_height), 0.0f, -1.0f, 1.0f);

    //    sc2d::ResourceHolder::get_shader("sprite-default")
    //        .set_int("image", sc2d::ResourceHolder::get_texture("engineer").get_obj_id());
    //    sc2d::ResourceHolder::get_shader("sprite-default").run().set_mat4("projection", proj);
    //    log_err_cmd("0x%x", glGetError());
    //    sprite = std::make_unique<sc2d::Sprite>(sc2d::ResourceHolder::get_shader("sprite-default"));
    log_err_cmd("0x%x", glGetError());

    const sc2d::Shader& sprite_sheet_shader = sc2d::ResourceHolder::get_shader("spritesheet");
    sprite_sheet_shader.set_int("image_array",
                                sc2d::ResourceHolder::get_texture_atlas("tilemap").get_obj_id());
    log_err_cmd("0x%x", glGetError());
    sprite_sheet_shader.run().set_mat4("projection", proj);
    sprite_sheet_shader.set_int("tile_index", 2);
    spritesheet = std::make_unique<sc2d::SpriteSheet>(sprite_sheet_shader);

    return glGetError();
}

void poll_events()
{
    glfwPollEvents();
}

void draw()
{
    glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    //    sprite->draw(sc2d::ResourceHolder::get_texture("logo"), math::vec2(0, 0),
    //                 math::size2d(111, 148), 0);
    spritesheet->draw(sc2d::ResourceHolder::get_texture_atlas("tilemap"), math::vec2(0, 0),
                      math::size2d(16, 16), 0);
    glfwSwapBuffers(window->get_window());
}

void update(double dt) {}

int main()
{
    if(init() != 0)
        return -1;

    // TODO: Make class for time management
    double begin_ticks = glfwGetTime();
    double end_ticks = 0;
    double delta_time = 1.0 / 60.0;

    // Game loop
    while(!glfwWindowShouldClose(window->get_window())) {
        update(delta_time);
        poll_events();
        draw();

        end_ticks = glfwGetTime();
        delta_time = (begin_ticks - end_ticks) / glfwGetTime();

#ifndef NDEBUG
        // If delta_time is too large, we must have resumed from a
        // breakpoint -- frame-lock to the target rate this frame.
        if(delta_time > 1.0) {
            delta_time = 1.0 / 60.0;
        }
#endif

        begin_ticks = end_ticks;
    }

    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // When a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}