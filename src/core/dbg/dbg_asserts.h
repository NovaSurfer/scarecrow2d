//
// Created by novasurfer on 4/16/20.
//

#ifndef SCARECROW2D_DBG_ASSERTS_H
#define SCARECROW2D_DBG_ASSERTS_H

#include "core/compiler.h"
#include "core/log2.h"
#include "ogl_errors.h"

namespace sc2d::debug
{

#ifdef NDEBUG
#    define DBG_FAIL_IF(expr, msg) static_cast<void>(0);
#    define DBG_CONSTEXPR_FAIL_IF(expr, msg) static_cast<void>(0);
#    define DBG_WARN_IF(expr, msg) static_cast<void>(0);
#    define DBG_RETURN_IF(expr, msg) static_cast<void>(0);
#    define DBG_FAIL_ON_RENDER_ERR() static_cast<void>(0);
#    define DBG_RETURN_ON_RENDER_ERR static_cast<void>(0);
#    define DBG_WARN_ON_RENDER_ERR static_cast<void>(0);

#else // DEBUG ON
#    define DBG_FAIL_IF(expr, msg)                                                                 \
        {                                                                                          \
            if(static_cast<bool>(expr)) {                                                          \
                log_err_cmd("%s, %s.", #expr, msg);                                                \
                abort();                                                                           \
            }                                                                                      \
        }

#    define DBG_CONSTEXPR_FAIL_IF(expr, msg)                                                       \
        {                                                                                          \
            if constexpr(static_cast<bool>(expr)) {                                                \
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

#    define DBG_RETURN_IF(expr, msg)                                                               \
        {                                                                                          \
            if(static_cast<bool>(expr)) {                                                          \
                log_warn_cmd("%s, %s.", #expr, msg);                                               \
                return;                                                                            \
            }                                                                                      \
        }

#    define DBG_FAIL_ON_RENDER_ERR                                                                 \
        {                                                                                          \
            const char* err_str = sc2d::debug::check_gl_error();                                   \
            if(err_str) {                                                                          \
                log_err_cmd("OPENGL: %s", err_str);                                                \
                abort();                                                                           \
            }                                                                                      \
        }

#    define DBG_RETURN_ON_RENDER_ERR                                                               \
        {                                                                                          \
            const char* err_str = sc2d::debug::check_gl_error();                                   \
            if(err_str) {                                                                          \
                log_err_cmd("OPENGL: %s", err_str);                                                \
                return;                                                                            \
            }                                                                                      \
        }

#    define DBG_WARN_ON_RENDER_ERR                                                                 \
        {                                                                                          \
            const char* err_str = sc2d::debug::check_gl_error();                                   \
            if(err_str) {                                                                          \
                log_warn_cmd("OPENGL: %s", err_str);                                               \
            }                                                                                      \
        }
}
#endif //NDEBUG

#endif //SCARECROW2D_DBG_ASSERTS_H
