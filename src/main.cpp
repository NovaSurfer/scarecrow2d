//
// Created by Maksim Ruts on 28-Aug-18.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "core/window.h"
#include "filesystem/configLoader.h"
#include "core/log2.h"

std::unique_ptr<Window> window;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

bool engine_init()
{
    return Config<ResourcesConfigLoad>::open("resources.json");
}

int init()
{
    glfwInit();
    log_info_cmd("Hello %s", "world");
    log_info_file("Hello %s", "world");

    const WindowData window_data{3, 3, GLFW_OPENGL_CORE_PROFILE, 800, 600, "scarecrow2d", framebuffer_size_callback, key_callback};
    window = std::make_unique<Window>(window_data, true);

    // Glad loads OpenGL functions pointers
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Loading engine systems
    if (!engine_init()) return -2;

    return glGetError();
}

void poll_events()
{
    glfwPollEvents();
}

void draw()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window->get_window());
}

void update(double dt)
{

}

int main()
{
    if(init() != 0)
        return -1;

    // TODO: Make class for time management
    double begin_ticks = glfwGetTime();
    double end_ticks = 0;
    double delta_time = 1.0 / 60.0;

    // Game loop
    while (!glfwWindowShouldClose(window->get_window()))
    {   
        update(delta_time);
        poll_events();
        draw();
        
        end_ticks = glfwGetTime();
        delta_time = (begin_ticks - end_ticks) / glfwGetTime();

    #ifndef NDEBUG
        // If delta_time is too large, we must have resumed from a 
        // breakpoint -- frame-lock to the target rate this frame.
        if(delta_time > 1.0)
        {
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
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}