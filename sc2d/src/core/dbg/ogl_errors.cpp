//
// Created by maksim.ruts on 26.7.19.
//

#include "ogl_errors.h"
#include "aglet/aglet.h"

namespace sc2d::debug
{
    const char* check_gl_error()
    {
        GLenum err;
        const char* err_str = nullptr;
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
