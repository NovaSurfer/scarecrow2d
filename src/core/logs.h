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

enum class LogLevel {
    INFO,
    WARN,
    ERROR
};

enum class LogType {
    CONSOLE,
    FILE,
    CONSOLE_N_FILE
};

class Log {
public:
    template<typename... Args>
    void info(Args&& ... args) { log(LogLevel::INFO, __FILE__, __LINE__, args...); };
    template<typename... Args>
    void warn(Args&& ... args) { log(LogLevel::WARN, __FILE__, __LINE__, args...); };
    template<typename... Args>
    void error(Args&& ... args) { log(LogLevel::ERROR, __FILE__, __LINE__, args...); };

protected:
    static const std::map<LogLevel, std::string> log_levels;
    virtual void log(LogLevel log_level, const char* file, int line, const char* fmt, ...) = 0;
};

class LogConsole : public Log {
protected:
    void log(LogLevel log_level, const char* file, int line, const char* fmt, ...) override;
};

class LogFile : public Log {

};

class LogMixed : public Log {

};

#endif //INC_2D_GAME_LOGS_H
