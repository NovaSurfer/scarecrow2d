//
// Created by Maksim Ruts on 28-Oct-18.
//

#ifndef INC_2D_GAME_WINDOW_H
#define INC_2D_GAME_WINDOW_H

#include <GLFW/glfw3.h>
#include <memory>
#include <string>

struct GLFWwindow;

struct WindowData
{
    int context_version_min;
    int context_version_max;
    int opengl_profile;
    int screen_width;
    int screen_height;
    std::string window_name;
    GLFWframebuffersizefun frame_buffer_size_callback;
    GLFWkeyfun key_callback;
};

class Window
{
public:
    Window(const WindowData& window_data, bool isCurrentContext);
    GLFWwindow* get_window() const
    {
        return window;
    }

private:
    WindowData window_data;
    GLFWwindow* window;
};

#endif //INC_2D_GAME_WINDOW_H
