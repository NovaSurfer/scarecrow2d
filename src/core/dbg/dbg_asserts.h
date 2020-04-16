//
// Created by novasurfer on 4/16/20.
//

#ifndef SCARECROW2D_DBG_ASSERTS_H
#define SCARECROW2D_DBG_ASSERTS_H

#include "core/log2.h"

#ifdef NDEBUG
#    define DBG_FAIL_IF(expr, msg) static_cast<void>(0);
#    define DBG_WARN_IF(expr, msg) static_cast<void>(0);

#else
#    define DBG_FAIL_IF(expr, msg)                                                                 \
        {                                                                                          \
            if(static_cast<bool>(expr)) {                                                          \
                log_err_cmd("%s, %s.", #expr, msg);                                                \
                abort();                                                                           \
            }                                                                                      \
        }

#    define DBG_WARN_IF(expr, msg)                                                                 \
        {                                                                                          \
            if(static_cast<bool>(expr)) {                                                          \
                log_warn_cmd("%s, %s.", #expr, msg);                                               \
            }                                                                                      \
        }
#endif

#endif //SCARECROW2D_DBG_ASSERTS_H
