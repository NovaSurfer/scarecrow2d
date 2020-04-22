//
// Created by Maksim Ruts on 27/08/2019.
//

#ifndef INC_2D_GAME_COMPILER_H
#define INC_2D_GAME_COMPILER_H

#if defined(__linux__)
#    define COMPILER_OS_LINUX 1
#endif

#if defined(__APPLE__)
#    define COMPILER_OS_APPLE 1
#endif

#if defined(_WIN32)
#    define COMPILER_OS_WIN32 1
#endif

#if defined(_WIN64)
#    define COMPILER_OS_WIN64_32 1
#endif

#if defined(__GNUC__)
#    define COMPILER_GCC 1
#endif

#if defined(__clang__)
#    define COMPILER_CLANG 1
#endif

#if defined(_MSC_VER)
#    define COMPILER_MVC 1
#endif

#if defined(__MINGW32__)
#    define COMPILER_MINGW32 1
#endif

#if defined(__MINGW64__)
#    define COMPILER_MINGW64 1
#endif

#if defined(__i386__)
#    define COMPILER_ARCH_x32 1
#endif

#if defined(__x86_64__)
#    define COMPILER_ARCH_x64_32 1
#endif

#ifdef COMPILER_MVC
#    define forceinline __forceinline
#elif defined(COMPILER_GCC)
#    define forceinline inline __attribute__((__always_inline__))
#elif defined(COMPILER_CLANG)
#    if __has_attribute(__always_inline__)
#        define forceinline inline __attribute__((__always_inline__))
#    else
#        define forceinline inline
#    endif
#else
#    define forceinline inline
#endif

#endif //INC_2D_GAME_COMPILER_H
