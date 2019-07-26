//
// Created by maksim.ruts on 26.7.19.
//

#ifndef INC_2D_GAME_DEBUG_UTILS_H
#define INC_2D_GAME_DEBUG_UTILS_H

#include "log2.h"

#define log_gl_error_cmd() log_err_cmd("%s", sc2d::debug::check_gl_error());
#define log_gl_error_file() log_err_file("%s", sc2d::debug::check_gl_error());

namespace sc2d::debug
{
    const char* check_gl_error();
}

#endif //INC_2D_GAME_DEBUG_UTILS_H
