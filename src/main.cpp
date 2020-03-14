//
// Created by Maksim Ruts on 28-Aug-18.
//

#include "core/debug_utils.h"
#include "core/log2.h"
#include "core/result.h"
#include "core/sprite.h"
//#include "core/sprite_sheet_inst.h"
#include "core/tiled_map.h"
#include "core/window.h"
#include "filesystem/configLoader.h"
#include "filesystem/resourceHolder.h"
#include "math/transform.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "core/text_ft2.h"


std::unique_ptr<sc2d::Window> window;
std::unique_ptr<sc2d::Sprite> sprite;
//std::unique_ptr<sc2d::SpriteSheetInstanced> spritesheet;

sc2d::tiled::Map tiled_map;
sc2d::TextureAtlas tex_atlas;
sc2d::Texture2d logo_texture;
sc2d::Ft2Font fnt_04b_03;
sc2d::TextFt2 text_ft2;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

sc2d::ResultBool engine_init()
{
    if(!sc2d::Config<sc2d::ResourcesConfigLoad>::open("resources.json"))
        return sc2d::ResultBool::throw_err(sc2d::Err::RESOURCE_LOADING_FAIL);

    if(!sc2d::Config<sc2d::SceneConfigLoad>::open("data/scenes/zone.json"))
        return sc2d::ResultBool::throw_err(sc2d::Err::SCENE_LOADING_FAIL);

    return {true};
}

sc2d::ResultBool program_init()
{
    glfwInit();

    constexpr const sc2d::WindowData window_data {3,
                                                  3,
                                                  GLFW_OPENGL_CORE_PROFILE,
                                                  800,
                                                  600,
                                                  "scarecrow2d",
                                                  framebuffer_size_callback,
                                                  key_callback};
    window = std::make_unique<sc2d::Window>(window_data, true);

    // Glad loads OpenGL functions pointers
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return sc2d::ResultBool::throw_err(sc2d::Err::FAILED_TO_INIT_GLAD);
    }

    // Loading engine systems
    engine_init();

    glViewport(0, 0, window_data.screen_width, window_data.screen_height);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
//        glFrontFace(GL_CCW);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_SCISSOR_TEST);

    math::mat4 proj =
        math::ortho(0.0f, static_cast<GLfloat>(window_data.screen_width),
                    static_cast<GLfloat>(window_data.screen_height), 0.0f, -1.0f, 1.0f);

    // REGULAR SPRITE
        const sc2d::Shader& sprite_shader = sc2d::ResourceHolder::get_shader("sprite_default");
        logo_texture = sc2d::ResourceHolder::get_texture("logo");
        sprite_shader.run();
        sprite_shader.set_int("image", logo_texture.get_obj_id());
        sprite_shader.set_mat4("projection", proj);
        sprite = std::make_unique<sc2d::Sprite>(sprite_shader);

    // SPRITE_SHEEEEEEEEEEET
    const sc2d::Shader& sprite_sheet_shader = sc2d::ResourceHolder::get_shader("spritesheet");
    tex_atlas = sc2d::ResourceHolder::get_texture_atlas("tilemap");
    sprite_sheet_shader.run();
    sprite_sheet_shader.set_int("image_array", tex_atlas.get_obj_id());
    log_gl_error_cmd()
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
    text_ft2.set_pos({100.f,100.f}, 0.f);

    log_gl_error_cmd()

        return !glGetError()
        ? (true)
        : sc2d::ResultBool::throw_err(sc2d::Err::ENGINE_INIT_FAIL);
}

void poll_events()
{
    glfwPollEvents();
}

void draw()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    tiled_map.draw_map(tex_atlas.get_obj_id());
    sprite->draw(logo_texture.get_obj_id(), math::vec2(0, 0),
                         math::size2d(111, 148), 0);
    text_ft2.draw();
    //    spritesheet->draw(sc2d::ResourceHolder::get_texture_atlas("tilemap"), math::vec2(0, 0),
    //                     math::size2d(16, 16), 0);


    glfwSwapBuffers(window->get_window());
}

void update(double dt) {}

int main()
{
    program_init();

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
    text_ft2.destroy();
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
