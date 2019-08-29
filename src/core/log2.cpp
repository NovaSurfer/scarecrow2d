#include "log2.h"
#include "compiler.h"

namespace sc2d::logging
{

    void log(LogType log_type, LogLevel log_level, const char* file, int line, const char* fmt...)
    {
        static std::mutex mtx;
        std::lock_guard<std::mutex> lock(mtx);

        time_t t = time(nullptr);
        tm lt{};

#if COMPILER_CLANG || COMPILER_GCC
        localtime_r(&t, &lt);
#elif COMPILER_MVC || COMPILER_MINGW32 || COMPILER_MINGW64
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
}
