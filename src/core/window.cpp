//
// Created by Maksim Ruts on 28-Oct-18.
//

#include "window.h"
#include "compiler.h"
#include <GLFW/glfw3.h>

namespace sc2d
{

    Window::Window(const WindowData& window_data, bool isCurrentContext)
        : window_data(window_data)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, window_data.context_version_maj);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, window_data.context_version_min);
        glfwWindowHint(GLFW_OPENGL_PROFILE, window_data.opengl_profile);
#if COMPILER_OS_APPLE
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
#endif
        window = glfwCreateWindow(window_data.size.width, window_data.size.height,
                                  window_data.window_name, nullptr, nullptr);
        glfwSetFramebufferSizeCallback(window, window_data.frame_buffer_size_callback);
        glfwSetKeyCallback(window, window_data.key_callback);
        if(isCurrentContext)
            glfwMakeContextCurrent(window);
    }
}
