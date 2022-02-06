//
// Created by novasurfer on 11/8/21.
//

#include "glfwbase.h"
#include <filesystem/resourceHolder.h>
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
            // TODO: update projection for the camera inside game
            // TODO: left the position of an object on the same place
            sc2d::ResourceHolder::update_shaders_proj(math::ortho(0.0, width, height, 0.0, DEFAULT_Z_NEAR, DEFAULT_Z_FAR));
        }
    }
}
