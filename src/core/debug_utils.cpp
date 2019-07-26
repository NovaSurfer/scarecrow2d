//
// Created by maksim.ruts on 26.7.19.
//

#include "debug_utils.h"
#include <glad/glad.h>

namespace sc2d::debug
{
    const char* check_gl_error()
    {
        GLenum err;
        const char* err_str = "GL_NO_ERROR";
        while((err = glGetError()) != GL_NO_ERROR) {
            switch(err) {
                case GL_INVALID_ENUM:
                    err_str = "GL_INVALID_ENUM";
                    break;
                case GL_INVALID_VALUE:
                    err_str = "GL_INVALID_VALUE";
                    break;
                case GL_INVALID_OPERATION:
                    err_str = "GL_INVALID_OPERATION";
                    break;
                case GL_STACK_OVERFLOW:
                    err_str = "GL_STACK_OVERFLOW";
                    break;
                case GL_STACK_UNDERFLOW:
                    err_str = "GL_STACK_UNDERFLOW";
                    break;
                case GL_OUT_OF_MEMORY:
                    err_str = "GL_OUT_OF_MEMORY";
                    break;
                case GL_INVALID_FRAMEBUFFER_OPERATION:
                    err_str = "GL_INVALID_FRAMEBUFFER_OPERATION";
                    break;
            }
        }
        return err_str;
    }
}
