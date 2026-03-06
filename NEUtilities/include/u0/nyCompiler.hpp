/******************************************************************************/
/**
 * @file    nyCompiler.hpp
 * @author  Dalia Castellanos
 * @date    07/02/2026
 * @brief   Defines compiler detection macros for the Utilities library.
 *
 * Defines macros to detect the compiler being used to build the Utilities
 * library, as well as macros for the compiler version and supported C++
 * standard. These macros can be used throughout the library to conditionally
 * compile code based on the compiler and its features.
 *
 * @bug	    No known bugs.
 */
/******************************************************************************/
#pragma once

#if defined(_MSC_VER) && !defined(__clang__)
  #define NY_COMPILER_MSVC 1
#else
  #define NY_COMPILER_MSVC 0
#endif

#if defined(__clang__)
  #define NY_COMPILER_CLANG 1
#else
  #define NY_COMPILER_CLANG 0
#endif

#if defined(__GNUC__) && !defined(__clang__)
  #define NY_COMPILER_GCC 1
#else
  #define NY_COMPILER_GCC 0
#endif

#if NY_COMPILER_MSVC
  #define NY_COMPILER_VERSION_MAJOR (_MSC_VER / 100)
  #define NY_COMPILER_VERSION_MINOR (_MSC_VER % 100)
#elif NY_COMPILER_CLANG
  #define NY_COMPILER_VERSION_MAJOR __clang_major__
  #define NY_COMPILER_VERSION_MINOR __clang_minor__
#elif NY_COMPILER_GCC
  #define NY_COMPILER_VERSION_MAJOR __GNUC__
  #define NY_COMPILER_VERSION_MINOR __GNUC_MINOR__
#else
  #define NY_COMPILER_VERSION_MAJOR 0
  #define NY_COMPILER_VERSION_MINOR 0
#endif

#if defined(_MSVC_LANG)
  #define NY_CPP_VERSION _MSVC_LANG
#else
  #define NY_CPP_VERSION __cplusplus
#endif

#define NY_CPP17 (NY_CPP_VERSION >= 201703L)
#define NY_CPP20 (NY_CPP_VERSION >= 202002L)
#define NY_CPP23 (NY_CPP_VERSION >= 202302L)

#if !NY_CPP17
  #error "Utilities requires at least C++17."
#endif
