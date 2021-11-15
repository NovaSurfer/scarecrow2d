//
// Created by novasurfer on 11/8/21.
//
#include "render.h"
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

    // Explicit template instantiation
    template class Render<opengl_render>;
}
