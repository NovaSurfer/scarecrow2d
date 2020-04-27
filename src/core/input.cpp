//
// Created by novasurfer on 4/19/20.
//

#include "input.h"
#include "game/game_main.h"
#include <GLFW/glfw3.h>

namespace sc2d
{
    void Input::read(GLFWwindow* window, int key, int scancode, int action, int mode)
    {
        Game* game = (Game*)glfwGetWindowUserPointer(window);
        game->read_input(key, action);
    }
}
