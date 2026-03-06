/*****************************************************************************/
/**
 * @file    nyWarnings.hpp
 * @author  Dalia Castellanos
 * @date    07/02/2026
 * @brief   Defines warning control macros for the Utilities library.
 *
 * Defines macros to push/pop warning state and disable specific warnings for
 * different compilers. These macros can be used to locally suppress warnings in
 * specific sections of code, such as when implementing platform-specific workarounds
 * or when dealing with third-party code that generates warnings.
 *
 * @bug	    No known bugs.
 */
/******************************************************************************/
#pragma once

#include "nyCompiler.hpp"

// Push/pop
#if NY_COMPILER_MSVC
  #define NY_WARNING_PUSH() __pragma(warning(push))
  #define NY_WARNING_POP()  __pragma(warning(pop))
  #define NY_WARNING_DISABLE_MSVC(id) __pragma(warning(disable: id))
#else
  #define NY_WARNING_PUSH()
  #define NY_WARNING_POP()
  #define NY_WARNING_DISABLE_MSVC(id)
#endif

#if (NY_COMPILER_CLANG || NY_COMPILER_GCC)
  #define NY_DO_PRAGMA(x) _Pragma(#x)
  #define NY_WARNING_DISABLE_GCC_CLANG(name) NY_DO_PRAGMA(GCC diagnostic ignored name)
#else
  #define NY_DO_PRAGMA(x)
  #define NY_WARNING_DISABLE_GCC_CLANG(name)
#endif

// Named common disables (add as you need)
#define NY_DISABLE_UNUSED_PARAMETER_WARNINGS() \
  do { \
    NY_WARNING_PUSH(); \
    /* MSVC */ \
    NY_WARNING_DISABLE_MSVC(4100); \
    /* GCC/Clang */ \
    NY_WARNING_DISABLE_GCC_CLANG("-Wunused-parameter"); \
  } while (0)

#define NY_RESTORE_WARNINGS() \
  do { \
    NY_WARNING_POP(); \
  } while (0)