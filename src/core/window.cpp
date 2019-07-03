//
// Created by Maksim Ruts on 28-Oct-18.
//

#include "window.h"

Window::Window(const WindowData& window_data, bool isCurrentContext)
    : window_data(window_data)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, window_data.context_version_max);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, window_data.context_version_min);
    glfwWindowHint(GLFW_OPENGL_PROFILE, window_data.opengl_profile);
    window = glfwCreateWindow(window_data.screen_width, window_data.screen_height,
                              window_data.window_name.c_str(), nullptr, nullptr);
    glfwSetFramebufferSizeCallback(window, window_data.frame_buffer_size_callback);
    glfwSetKeyCallback(window, window_data.key_callback);
    if(isCurrentContext)
        glfwMakeContextCurrent(window);
}
