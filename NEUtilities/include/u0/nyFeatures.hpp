/*****************************************************************************/
/**
 * @file    nyFeatures.hpp
 * @author  Dalia Castellanos
 * @date    07/02/2026
 * @brief   Defines feature detection macros for the Utilities library.
 *
 * Defines macros to detect the presence of various compiler features, such as
 * built-in functions, attributes, and C++ attributes. These macros can be used
 * throughout the library to conditionally compile code based on the availability
 * of these features, allowing for better portability and optimization across
 * different compilers and platforms.
 *
 * @bug	    No known bugs.
 */
/*****************************************************************************/
#pragma once

// __has_builtin / __has_attribute / __has_cpp_attribute support
#ifndef NY_HAS_BUILTIN
  #if defined(__has_builtin)
    #define NY_HAS_BUILTIN(x) __has_builtin(x)
  #else
    #define NY_HAS_BUILTIN(x) 0
  #endif
#endif

#ifndef NY_HAS_ATTRIBUTE
  #if defined(__has_attribute)
    #define NY_HAS_ATTRIBUTE(x) __has_attribute(x)
  #else
    #define NY_HAS_ATTRIBUTE(x) 0
  #endif
#endif

#ifndef NY_HAS_CPP_ATTRIBUTE
  #if defined(__has_cpp_attribute)
    #define NY_HAS_CPP_ATTRIBUTE(x) __has_cpp_attribute(x)
  #else
    #define NY_HAS_CPP_ATTRIBUTE(x) 0
  #endif
#endif
