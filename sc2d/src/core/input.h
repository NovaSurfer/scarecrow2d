//
// Created by novasurfer on 4/19/20.
//

#ifndef SCARECROW2D_INPUT_H
#define SCARECROW2D_INPUT_H

#include "input_types.h"
class GLFWwindow;
namespace sc2d
{
    class Window;

    struct KeyboardKey
    {
        int key;
        int scancode;
        int action;
        int mode;
    };

    struct CursorPos
    {
        double x_pos;
        double y_pos;
    };

    struct MouseButton
    {
        int button;
        int action;
        int mods;
    };

    class Input
    {
    public:
        Input() = default;
        Input(const Window& window);

        static void read_kb_key(GLFWwindow* window, int key, int scancode, int action, int mode);
        static void read_cursor_pos(GLFWwindow* window, double xpos, double ypos);
        static void read_mouse_button(GLFWwindow* window, int button, int action, int mods);

        bool get_key(Key::Code key) const;
        bool get_key_down(Key::Code key) const;
        bool get_key_up(Key::Code key) const;

        bool mouse_btn(MouseBtn::Code button) const;
        bool mouse_btn_down(MouseBtn::Code button) const;
        bool mouse_btn_up(MouseBtn::Code button) const;

        const CursorPos& get_cursor_pos() const;

    private:
        CursorPos cursor_pos;
        MouseButton mouse_button;
        KeyboardKey keyboard_key;

        void set_key_input(int key, int scancode, int action, int mode);
        void set_cursor_pos(double xpos, double ypos);
        void set_mouse_button(int button, int action, int mods);
    };
}

#endif //SCARECROW2D_INPUT_H
