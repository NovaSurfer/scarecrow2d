//
// Created by Maksim Ruts on 04-Dec-18.
//

#ifndef INC_2D_ENGINE_LOGGER_H
#define INC_2D_ENGINE_LOGGER_H

#include <memory>
#include "tinyFactory.h"
#include "logs.h"

using LogFactory = Factory<std::unique_ptr<Log>>;

LogFactory log_create(LogType log_type)
{
//ERROR: Lambda can only be converted to a function pointer if it doesn't capture
// https://stackoverflow.com/questions/28746744/passing-capturing-lambda-as-function-pointer
//    return [=]{
//      if (log_type==LogType::CONSOLE)
//          return std::unique_ptr<Log>(new LogConsole());
//    };

    if (log_type==LogType::CONSOLE)
        return [] {
          return std::unique_ptr<Log>(new LogConsole());
        };
}

#endif //INC_2D_ENGINE_LOGGER_H
