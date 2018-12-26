//
// Created by Maksim Ruts on 06-Dec-18.
//

#include "logs.h"

void LogConsole::log(LogLevel log_level, Log::SRC_LOC src_loc, const char* fmt, ...)
{
    time_t t = time(nullptr);
    struct tm* lt = localtime(&t);
    const std::string& log_lvl = log_levels.at(log_level);
    va_list args;
    char buf[16];
    buf[strftime(buf, sizeof(buf), "%H:%M:%S", lt)] = '\0';
    fprintf(stderr, "%s %-5s %s:%d: ", buf, log_lvl.c_str(), src_loc.file_name(), src_loc.line());
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");
    fflush(stderr);
}
