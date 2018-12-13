//
// Created by Maksim Ruts on 06-Dec-18.
//

#ifndef INC_2D_GAME_LOGS_H
#define INC_2D_GAME_LOGS_H

#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <memory>
#include <mutex>
#include <map>
#include <experimental/source_location>

enum class LogLevel {
    INFO,
    WARN,
    ERR
};

enum class LogType {
    CONSOLE,
    FILE,
    CONSOLE_N_FILE
};

static const std::map<LogLevel, std::string> log_levels = {
    {LogLevel::INFO, "INFO"},
    {LogLevel::WARN, "WARN"},
    {LogLevel::ERR, "ERROR"}
};


class Log {
public:
    using SRC_LOC = std::experimental::source_location;
    // ¯\_(ツ)_/¯
    // https://stackoverflow.com/questions/52977593/stdexperimentalsource-location-at-compile-time
    template<typename... Args>
    void info(Args&& ... args) { log(LogLevel::INFO, SRC_LOC::current().file_name(), SRC_LOC::current().line(), args...); };
    template<typename... Args>
    void warn(Args&& ... args) { log(LogLevel::WARN, __FILE__, __LINE__, args...); };
    template<typename... Args>
    void error(Args&& ... args) { log(LogLevel::ERR, __FILE__, __LINE__, args...); };

protected:
    virtual void log(LogLevel log_level, const char* file, int line, const char* fmt, ...) = 0;
};

class LogConsole : public Log {
public:
    LogConsole() = default;
protected:
    void log(LogLevel log_level, const char* file, int line, const char* fmt, ...) override;
};

class LogFile : public Log {

};

class LogMixed : public Log {

};

#endif //INC_2D_GAME_LOGS_H
