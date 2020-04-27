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

#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <mutex>

#define log_info_cmd(...)                                                                          \
    sc2d::logging::log(sc2d::logging::CONSOLE, sc2d::logging::INFO, __FILE__, __LINE__, __VA_ARGS__)
#define log_info_file(...)                                                                         \
    sc2d::logging::log(sc2d::logging::FILE_S, sc2d::logging::INFO, __FILE__, __LINE__, __VA_ARGS__)
#define log_warn_cmd(...)                                                                          \
    sc2d::logging::log(sc2d::logging::CONSOLE, sc2d::logging::WARN, __FILE__, __LINE__, __VA_ARGS__)
#define log_warn_file(...)                                                                         \
    sc2d::logging::log(sc2d::logging::FILE_S, sc2d::logging::WARN, __FILE__, __LINE__, __VA_ARGS__)
#define log_err_cmd(...)                                                                           \
    sc2d::logging::log(sc2d::logging::CONSOLE, sc2d::logging::ERR, __FILE__, __LINE__, __VA_ARGS__)
#define log_err_file(...)                                                                          \
    sc2d::logging::log(sc2d::logging::FILE_S, sc2d::logging::ERR, __FILE__, __LINE__, __VA_ARGS__)

namespace sc2d::logging
{
    enum LogLevel
    {
        INFO,
        WARN,
        ERR
    };

    enum LogType
    {
        CONSOLE,
        FILE_S
    };

    static constexpr const char* lvl_names[] {"INFO", "WARNING", "ERROR"};
    static constexpr const char* lvl_colors[] {
        "\x1b[32m", // INFO - green
        "\x1b[33m", // WARNING - yellow
        "\x1b[31m" // ERROR - red
    };

    void log(LogType log_type, LogLevel log_level, const char* file, int line, const char* fmt...);
}
#endif //INC_2D_GAME_LOG2_H
