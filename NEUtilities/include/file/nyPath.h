/******************************************************************************/
/**
 * @file    nyPath.hpp
 * @author  Dalia Castellanos
 * @date    06/03/2026
 * @brief   Defines the Path class for path string manipulation.
 * 
 * Defines a simple `Path` class that provides static utility functions for
 * manipulating and inspecting file path strings. The class is designed
 * to work with both Windows and Unix-style paths, handling both forward and
 * backward slashes as separators.
 *
 * @bug	    No known bugs.
 */
/******************************************************************************/
#pragma once

#include <string>

#include "macros/nyApi.hpp"
#include "macros/nyMacros.hpp"

#include "types/nyContainers.h"
#include "types/nyStringView.hpp"

namespace nyEngineSDK
{
  /**
   * @brief  Utility helpers for path string inspection and normalization.
   * @bug   No known bugs
   */
  class NY_API Path
  {
   public:
    /**
     * @brief  Returns whether the given character is a path separator.
     * @bug    No known bugs
     */
    static NY_FORCE_INLINE bool
    isSeparator(char c) noexcept
    {
      return (c == '/') || (c == '\\');
    }

    /**
     * @brief  Returns whether the path is empty.
     * @bug    No known bugs
     */
    static NY_FORCE_INLINE bool
    isEmpty(StringView path) noexcept
    {
      return path.empty();
    }

    /**
     * @brief  Returns the file extension, excluding the dot.
     * @bug    No known bugs
     */
    static StringView
    getExtension(StringView path) noexcept;

    /**
     * @brief  Returns whether the path has a valid file extension.
     * @bug    No known bugs
     */
    static NY_FORCE_INLINE bool
    hasExtension(StringView path) noexcept
    {
      return !getExtension(path).empty();
    }

    /**
     * @brief  Returns the file name portion of the path.
     * @bug    No known bugs
     */
    static StringView
    getFileName(StringView path) noexcept;

    /**
     * @brief  Returns the file name without its extension.
     * @bug    No known bugs
     */
    static StringView
    getFileStem(StringView path) noexcept;

    /**
     * @brief  Returns the parent path portion.
     * @bug    No known bugs
     */
    static StringView
    getParentPath(StringView path) noexcept;

    /**
     * @brief  Returns a normalized path using forward slashes.
     * @bug    No known bugs
     */
    static String
    normalize(StringView path) noexcept;

    /**
     * @brief  Returns true if the path is absolute.
     * @bug    No known bugs
     */
    static bool
    isAbsolute(StringView path) noexcept;

    /**
     * @brief  Converts a path to absolute form.
     * @bug    No known bugs
     */
    static String
    makeAbsolute(StringView path) noexcept;

    /**
     * @brief  Returns a normalized absolute path.
     * @bug    No known bugs
     */
    static String
    normalizeAbsolute(StringView path) noexcept;

    /**
     * @brief  Joins two path parts and normalizes separators.
     * @bug    No known bugs
     */
    static String
    join(StringView a, StringView b) noexcept;

   private:
    static constexpr usize kInvalidPos = static_cast<usize>(-1);

    /**
     * @brief  Returns the last separator position in the path.
     * @bug    No known bugs
     */
    static usize
    findLastSeparator(StringView path) noexcept;

    /**
     * @brief  Returns the last dot position in the path.
     * @bug    No known bugs
     */
    static usize
    findLastDot(StringView path) noexcept;
  };
} // namespace nyEngineSDK