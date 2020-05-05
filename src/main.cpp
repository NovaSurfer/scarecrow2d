//
// Created by Maksim Ruts on 28-Aug-18.
//

#include "core/dbg/ogl_errors.h"
#include "core/input.h"
#include "core/log2.h"
#include "core/resources.h"
#include "core/result.h"
#include "core/window.h"
#include "editor/editor_main.h"
#include "game/game_main.h"
#include "math/transform.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <memory>

enum class MainMode
{
    GAME,
    EDITOR
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

std::unique_ptr<sc2d::Window> window;
constexpr const sc2d::WindowData window_data {3,
                                              3,
                                              GLFW_OPENGL_CORE_PROFILE,
                                              {800,
                                              600},
                                              "scarecrow2d",
                                              framebuffer_size_callback,
                                              sc2d::Input::read};

sc2d::ResultBool renderer_init()
{

    glfwInit();
    window = std::make_unique<sc2d::Window>(window_data, true);

    // Glad loads OpenGL functions pointers
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return sc2d::ResultBool::throw_err(sc2d::Err::FAILED_TO_INIT_GLAD);
    }

    glViewport(0, 0, window_data.size.width, window_data.size.height);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_SCISSOR_TEST);
    log_gl_error_cmd();

    return !glGetError() ? (true) : sc2d::ResultBool::throw_err(sc2d::Err::ENGINE_INIT_FAIL);
}

void poll_events()
{
    glfwPollEvents();
}

void update(double dt) { }

int main(int argc, char* argv[])
{
    MainMode main_mode = MainMode::GAME;
    renderer_init();
    sc2d::Resources::load_all();

    Game game;
    game.init(GameMode::SCENE, window_data.size);
    glfwSetWindowUserPointer(window->get_window(), &game);


    // TODO: Make class for time management
    double begin_ticks = glfwGetTime();
    double end_ticks = 0;
    double delta_time = 1.0 / 60.0;

    // Game loop
    while(!glfwWindowShouldClose(window->get_window())) {
        update(delta_time);
        poll_events();
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        if(main_mode == MainMode::GAME) {
            game.draw();
        } else {
            Editor::draw();
        }
        glfwSwapBuffers(window->get_window());
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

    game.destroy();
    sc2d::Resources::clean_all();
    glfwTerminate();
    return 0;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
