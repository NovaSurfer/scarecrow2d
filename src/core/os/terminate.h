//
// Created by Maksim Ruts on 27/08/2019.
//

#ifndef INC_2D_GAME_TERMINATE_H
#define INC_2D_GAME_TERMINATE_H

#include "stacktrace.h"
#include "core/log2.h"
#include "error_types.h"

namespace sc2d
{

    [[noreturn]] inline void terminate(Err e)
    {
        log_err_cmd("Code :: %s", ERR_STR[static_cast<int>(e)]);
        const char* trace_str = Backtrace(0);
        FILE* trace_file = nullptr;
        trace_file = fopen("sc2d_stacktrace.log", "a");
        fprintf(trace_file, "%s", trace_str);
        fflush(trace_file);

        abort();
    }
}
#endif //INC_2D_GAME_TERMINATE_H
