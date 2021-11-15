//
// Created by novasurfer on 11/8/21.
//

#include "glfwbase.h"
#include <GLFW/glfw3.h>

namespace sc2d
{
    void GlfwBase::init()
    {
        glfwInit();
    }

    namespace GlfwWindowUtils
    {
        void GL_frambuffer_resize(GLFWwindow* window, int width, int height)
        {
            // make sure the viewport matches the new window dimensions; note that width and
            // height will be significantly larger than specified on retina displays.
            glViewport(0, 0, width, height);
        }
    }
}
