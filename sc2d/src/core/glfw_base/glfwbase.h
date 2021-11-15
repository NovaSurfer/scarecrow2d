//
// Created by novasurfer on 11/8/21.
//

#ifndef SCARECROW2D_GLFWBASE_H
#define SCARECROW2D_GLFWBASE_H

struct GLFWwindow;
namespace sc2d
{
    enum class GlProfile : int
    {
        ANY = 0,
        CORE = 0x00032001,
        COMPAT = 0x00032002
    };

    class GlfwBase
    {
    public:
        static void init();
    };

    namespace GlfwWindowUtils
    {
        void GL_frambuffer_resize(GLFWwindow* window, int width, int height);
    }
}

#endif //SCARECROW2D_GLFWBASE_H
