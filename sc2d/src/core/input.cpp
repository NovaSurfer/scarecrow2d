//
// Created by novasurfer on 4/19/20.
//
#include "input.h"
#include "glfw_base/window.h"

namespace sc2d
{

    Input::Input(const Window& window)
    {
        glfwSetWindowUserPointer(window.get_window(), reinterpret_cast<void*>(this));
    }

    void Input::read_kb_key(GLFWwindow* window, int key, int scancode, int action, int mode)
    {
        Input* input = reinterpret_cast<Input*>(glfwGetWindowUserPointer(window));

        if(input)
        {
            input->set_key_input(key, scancode, action, mode);
        }
    }

    void Input::read_cursor_pos(GLFWwindow* window, double xpos, double ypos)
    {
        Input* input = reinterpret_cast<Input*>(glfwGetWindowUserPointer(window));

        if(input)
        {
            input->set_cursor_pos(xpos, ypos);
        }
    }

    void Input::read_mouse_button(GLFWwindow* window, int button, int action, int mods)
    {
        Input* input = reinterpret_cast<Input*>(glfwGetWindowUserPointer(window));

        if(input)
        {
            input->set_mouse_button(button, action, mods);
        }
    }

    bool Input::get_key(Key::Code key) const
    {
        return keyboard_key.key == key;
    }

    bool Input::get_key_down(Key::Code key) const
    {
        return keyboard_key.key == key && keyboard_key.action == InputAction::PRESS;
    }

    bool Input::get_key_up(Key::Code key) const
    {
        return keyboard_key.key == key && keyboard_key.action == InputAction::RELEASE;
    }

    bool Input::mouse_btn(MouseBtn::Code button) const
    {
        return mouse_button.button == button;
    }

    bool Input::mouse_btn_down(MouseBtn::Code button) const
    {
        return mouse_button.button == button && mouse_button.action == InputAction::PRESS;
    }

    bool Input::mouse_btn_up(MouseBtn::Code button) const
    {
        return mouse_button.button == button && mouse_button.action == InputAction::RELEASE;
    }

    const CursorPos& Input::get_cursor_pos() const
    {
        return cursor_pos;
    }

    void Input::set_key_input(int key, int scancode, int action, int mode)
    {
        keyboard_key.key = key;
        keyboard_key.scancode = scancode;
        keyboard_key.action = action;
        keyboard_key.mode = mode;
    }

    void Input::set_cursor_pos(double xpos, double ypos)
    {
        cursor_pos.x_pos = xpos;
        cursor_pos.y_pos = ypos;
    }

    void Input::set_mouse_button(int button, int action, int mods)
    {
        mouse_button.button = button;
        mouse_button.action = action;
        mouse_button.mods = mods;
    }
}