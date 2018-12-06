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
    return [=] {
      if (log_type==LogType::CONSOLE)
          return std::unique_ptr<Log>(new LogConsole());
    };
}

#endif //INC_2D_ENGINE_LOGGER_H
