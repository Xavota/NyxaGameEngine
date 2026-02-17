/*****************************************************************************/
/**
 * @file    nyApi.hpp
 * @author  Dalia Castellanos
 * @date    07/02/2026
 * @brief   Defines the public API for the Utilities library.
 *
 * Defines API export/import macros and other public-facing declarations for the
 * Utilities library.
 *
 * @bug	    No known bugs.
 */
 /*****************************************************************************/
#pragma once

#include "u0/nyPlatform.hpp"
#include "u0/nyCompiler.hpp"

// Build system must define exactly one of these when compiling the library:
// - NY_UTILITIES_SHARED : building/using Utilities as a shared library if not defined, defaults to static library
//
// And when compiling the Utilities library itself (not users), define:
// - NY_UTILITIES_IMPLEMENTATION

// Symbol visibility
#if defined(NY_UTILITIES_SHARED)
  #if NY_OS_WINDOWS
    #if defined(NY_UTILITIES_IMPLEMENTATION)
      #define NY_API __declspec(dllexport)
    #else
      #define NY_API __declspec(dllimport)
    #endif

    #define NY_LOCAL
  #else
  // GCC/Clang on ELF/Mach-O
    #if (NY_COMPILER_GCC || NY_COMPILER_CLANG)
      #define NY_API   __attribute__((visibility("default")))
      #define NY_LOCAL __attribute__((visibility("hidden")))
    #else
      #define NY_API
      #define NY_LOCAL
    #endif
  #endif

#else
  // Static library: nothing to export/import
  #define NY_API
  #define NY_LOCAL
#endif