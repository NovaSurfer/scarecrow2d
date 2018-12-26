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
    template<typename... Args, typename SOMES = SRC_LOC>
    void info(Args&& ... args, SOMES s = SRC_LOC::current()) { log(LogLevel::INFO, s.file_name(), s.line(), args...); };
    template<typename... Args>
    void warn(Args&& ... args) { log(LogLevel::WARN, SRC_LOC::current(), args...); };
    template<typename... Args>
    void error(Args&& ... args) { log(LogLevel::ERR, SRC_LOC::current(), args...); };

protected:
    virtual void log(LogLevel log_level, const char* file, int line, ...) = 0;
};

class LogConsole : public Log {
public:
    LogConsole() = default;
protected:
    void log(LogLevel log_level, const char* file, int line, ...) override;
};

class LogFile : public Log {

};

class LogMixed : public Log {

};

#endif //INC_2D_GAME_LOGS_H
