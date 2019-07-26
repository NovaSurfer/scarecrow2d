#include "log2.h"

namespace sc2d::logging
{

    void log(LogType log_type, LogLevel log_level, const char* file, int line, const char* fmt...)
    {
        static std::mutex mtx;
        std::lock_guard<std::mutex> lock(mtx);

        time_t t = time(nullptr);
        tm lt{};

#if defined(__unix__)
        localtime_r(&t, &lt);
#elif defined(_MSC_VER) || (__MINGW32__)
        localtime_s(&lt, &t);
#endif

        va_list args;
        char buf[16];
        buf[strftime(buf, sizeof(buf), "%H:%M:%S", &lt)] = '\0';

        FILE* log_stream = nullptr;
        std::string log_format{};

        if(log_type == CONSOLE) {
            log_stream = stderr;
            log_format = "%s %s%-5s\x1b[0m \x1b[90m%s:%d:\x1b[0m ";
            fprintf(log_stream, log_format.c_str(), buf, lvl_colors[log_level],
                    lvl_names[log_level], file, line);
        } else {
            log_stream = fopen("sc2d.log", "a");
            log_format = "%s %-5s %s:%d: ";
            if(log_stream != nullptr)
                fprintf(log_stream, log_format.c_str(), buf, lvl_names[log_level], file, line);
        }
        va_start(args, fmt);
        vfprintf(log_stream, fmt, args);
        va_end(args);
        fprintf(log_stream, "\n");
        fflush(log_stream);
    }

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