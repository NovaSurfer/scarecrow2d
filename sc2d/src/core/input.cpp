//
// Created by novasurfer on 4/19/20.
//
#include "input.h"
#include "glfw_base/window.h"
#include <GLFW/glfw3.h>

namespace sc2d
{

    Input::Input(const Window& window)
    {
        glfwSetWindowUserPointer(window.get_window(), reinterpret_cast<void*>(this));
    }

    void Input::read(GLFWwindow* window, int key, int scancode, int action, int mode)
    {
        Input* input = reinterpret_cast<Input*>(glfwGetWindowUserPointer(window));

        if(input)
        {
            input->set_key_input(key, scancode, action, mode);
        }
    }

    void Input::set_key_input(int key, int scancode, int action, int mode)
    {
        this->key = key;
        this->scancode = scancode;
        this->action = action;
        this->mode = mode;
    }

    bool Input::get_key(int key)
    {
        return this->key == key;
    }

    bool Input::get_key_down(int key)
    {
        return this->key == key && action == GLFW_PRESS;
    }

    bool Input::get_key_up(int key)
    {
        return this->key == key && action == GLFW_RELEASE;
    }
}