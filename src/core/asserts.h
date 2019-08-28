//
// Created by Maksim Ruts on 27/08/2019.
//

#ifndef INC_2D_GAME_ASSERTS_H
#define INC_2D_GAME_ASSERTS_H

#include "compiler.h"
#include "log2.h"
#include "stacktrace.h"

#define CRASH_INST "int3"

// TODO: Memory barrier
inline void compilerFenceForCrash()
{
    //#if COMPILER_OS_WINDOWS && !COMPILER_GCC || !COMPILER_CLANG || !COMPILER_MINGW32 ||                \
//    !COMPILER_MINGW64
    //    _ReadWriteBarrier();
    //#else
    asm volatile("" ::: "memory");
    //#endif
}

#ifndef CRASH_WITH_INFO
#    if COMPILER_CLANG || COMPILER_MVC
#        define CRASH_WITH_INFO(...)                                                               \
            {                                                                                      \
                compilerFenceForCrash();                                                           \
                asm(CRASH_INST);                                                                   \
                __builtin_unreachable();                                                           \
            }

#    endif
#endif // CRASH_WITH_NO_INFO

#define RELEASE_ASSERT_NOT_REACHED(...) CRASH_WITH_INFO(__VA_ARGS__);
[[noreturn]] inline void TERMINATE() {RELEASE_ASSERT_NOT_REACHED()};
#define THROW_ERR(...) TERMINATE()

#endif //INC_2D_GAME_ASSERTS_H
