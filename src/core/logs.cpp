//
// Created by Maksim Ruts on 06-Dec-18.
//

#include "logs.h"

void LogConsole::log(LogLevel log_level, const char* file, int line, ...)
{
    time_t t = time(nullptr);
    struct tm* lt = localtime(&t);
    const std::string& log_lvl = log_levels.at(log_level);
    va_list args;
    char buf[16];
    buf[strftime(buf, sizeof(buf), "%H:%M:%S", lt)] = '\0';
    fprintf(stderr, "%s %-5s %s:%d: ", buf, log_lvl.c_str(), file, line);
    va_start(args, line);
    vfprintf(stderr, "%s", args);
    va_end(args);
    fprintf(stderr, "\n");
    fflush(stderr);
}
