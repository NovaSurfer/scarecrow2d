//
// Created by Maksim Ruts on 28-Oct-18.
//

#ifndef INC_2D_GAME_WINDOW_H
#define INC_2D_GAME_WINDOW_H

struct GLFWwindow;

namespace sc2d
{

    using Window_resize_callback = void (*)(GLFWwindow*, int, int);
    using Kbkey_callback = void (*)(GLFWwindow*, int, int, int, int);
    using CursorPos_callback = void (*)(GLFWwindow*, double, double);
    using MouseButton_callback = void (*)(GLFWwindow*, int, int, int);

    struct WindowSize
    {
        int width;
        int height;
    };

    struct WindowData
    {
        const char* window_name;
        Window_resize_callback frame_buffer_size_callback;
        Kbkey_callback key_callback;
        CursorPos_callback cursor_pos_callback;
        MouseButton_callback mouse_button_callback;
        WindowSize size;
        int context_version_maj;
        int context_version_min;
        int opengl_profile;
    };

    class Window
    {
    public:
        Window(const WindowData& window_data, bool isCurrentContext);
        bool should_close();
        void poll_events();
        void swap_buffers();
        inline GLFWwindow* get_window() const
        {
            return window;
        }

    private:
        GLFWwindow* window;
    };
}

#endif //INC_2D_GAME_WINDOW_H
