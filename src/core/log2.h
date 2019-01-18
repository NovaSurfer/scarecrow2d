/**
 * I know that this is bad C++ code, but unfortunately I can't use
 * __FILE__ / __LINE__ predefined macroses outside of another macros context.
 * I've tried to use std::experimental::source_location, but it's very hard to mix
 * variadic arguments with default value for source_location.
 * Details_01: https://stackoverflow.com/questions/52977593/stdexperimentalsource-location-at-compile-time
 * Details_02: https://stackoverflow.com/questions/4196431/passing-the-caller-file-line-to-a-function-without-using-macro/28742116
 * Modified https://github.com/rxi/log.c
 */

#ifndef INC_2D_GAME_LOG2_H
#define INC_2D_GAME_LOG2_H

#include <ctime>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <mutex>

#define log_info_cmd(...)       sc2d::logging::log(sc2d::logging::CONSOLE, sc2d::logging::INFO, __FILE__, __LINE__, __VA_ARGS__)
#define log_info_file(...)      sc2d::logging::log(sc2d::logging::FILE_S, sc2d::logging::INFO, __FILE__, __LINE__, __VA_ARGS__)
#define log_warn_cmd(...)       sc2d::logging::log(sc2d::logging::CONSOLE, sc2d::logging::WARN, __FILE__, __LINE__, __VA_ARGS__)
#define log_warn_file(...)      sc2d::logging::log(sc2d::logging::FILE_S, sc2d::logging::WARN, __FILE__, __LINE__, __VA_ARGS__)
#define log_err_cmd(...)        sc2d::logging::log(sc2d::logging::CONSOLE, sc2d::logging::ERR, __FILE__, __LINE__, __VA_ARGS__)
#define log_err_file(...)       sc2d::logging::log(sc2d::logging::FILE_S, sc2d::logging::ERR, __FILE__, __LINE__, __VA_ARGS__)

namespace sc2d::logging{

    enum LogLevel {
        INFO,
        WARN,
        ERR
    };

    enum LogType {
        CONSOLE,
        FILE_S
    };

    static constexpr const char* lvl_names[] {
        "INFO", "WARNING", "ERROR"
    };

    static constexpr const char* lvl_colors[] {
        "\x1b[32m", // INFO - green
        "\x1b[33m", // WARNING - yellow
        "\x1b[31m"  // ERROR - red
    };

    static void log(LogType log_type, LogLevel log_level, const char* file, int line, const char* fmt ...)
    {
        static std::mutex mtx;
        std::lock_guard<std::mutex> lock(mtx);

        time_t t = time(nullptr);
        tm lt {};
        // TODO: localtime_s for MVC++
        localtime_r(&t, &lt);

        va_list args;
        char buf[16];
        buf[strftime(buf, sizeof(buf), "%H:%M:%S", &lt)] = '\0';

        FILE* log_stream = nullptr;
        std::string log_format{};

        if (log_type == CONSOLE) {
            log_stream = stderr;
            log_format = "%s %s%-5s\x1b[0m \x1b[90m%s:%d:\x1b[0m ";
            fprintf(log_stream, log_format.c_str(), buf, lvl_colors[log_level], lvl_names[log_level], file, line);
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

#endif //INC_2D_GAME_LOG2_H

