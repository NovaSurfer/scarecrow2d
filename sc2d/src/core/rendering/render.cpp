//
// Created by novasurfer on 11/8/21.
//
#include "render.h"
#include "vulkan/vulkan.h"
#include <GLFW/glfw3.h>
#include "core/glfw_base/window.h"

namespace sc2d
{
    template <typename R>
    void Render<R>::create(const WindowSize* const window_size) const
    {
        this->init(window_size);
    }

    void opengl_render::init(const WindowSize* const window_size) const
    {
        glViewport(0, 0, window_size->width, window_size->height);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_SCISSOR_TEST);
    }

    void vulkan_render::init(const WindowSize* window_size) const
    {
       VkApplicationInfo app_info {};
       app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
       app_info.pApplicationName = "scarecrow2d";
       app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
       app_info.pEngineName = "sc2d";
       app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
       app_info.apiVersion = VK_API_VERSION_1_0;

       VkInstanceCreateInfo create_info {};
       create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
       create_info.pApplicationInfo = &app_info;
    }


    // Explicit template instantiation
    template class Render<opengl_render>;
    template class Render<vulkan_render>;
}
