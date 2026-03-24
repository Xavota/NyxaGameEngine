/******************************************************************************/
/**
 * @file    nyCoreApi.hpp
 * @author  Dalia Castellanos
 * @date    16/03/2026
 * @brief   Defines the public API for the Core library.
 *
 * Defines API export/import macros and other public-facing declarations for the
 * Core library.
 *
 * @bug	    No known bugs.
 */
/******************************************************************************/
#pragma once

#include <macros/nyPlatform.hpp>
#include <macros/nyCompiler.hpp>

// Build system must define exactly one of these when compiling the library:
// - NY_CORE_SHARED : building/using Core as a shared library if not defined, defaults to static library
//
// And when compiling the Core library itself (not users), define:
// - NY_CORE_IMPLEMENTATION

// Symbol visibility
#if defined(NY_CORE_SHARED)
  #if NY_OS_WINDOWS
    #if NY_COMPILER_MSVC
      #if defined(NY_CORE_IMPLEMENTATION)
        #define NY_API __declspec(dllexport)
      #else
        #define NY_API __declspec(dllimport)
      #endif
    #else //Any other compiler
      #if defined(NY_CORE_IMPLEMENTATION)
        #define NY_API __attribute__ ((dllexport))
      #else
        #define NY_API __attribute__ ((dllimport))
      #endif
    #endif

    #define NY_LOCAL
  #else
    #define NY_API   __attribute__((visibility("default")))
    #define NY_LOCAL __attribute__((visibility("hidden")))
  #endif

#else
  // Static library: nothing to export/import
  #define NY_API
  #define NY_LOCAL
#endif