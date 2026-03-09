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

#include "types/nyStringView.hpp"

namespace nyEngineSDK
{
  /**
   * @brief Utility helpers for path string inspection and normalization.
   * @bug No known bugs
   */
  class Path
  {
   public:
    /**
     * @brief Returns whether the given character is a path separator.
     * @bug No known bugs
     */
    static bool
    isSeparator(char c) noexcept
    {
      return (c == '/') || (c == '\\');
    }

    /**
     * @brief Returns whether the path is empty.
     * @bug No known bugs
     */
    static bool
    isEmpty(StringView path) noexcept
    {
      return path.empty();
    }

    /**
     * @brief Returns the file extension, excluding the dot.
     * @bug No known bugs
     */
    static StringView
    getExtension(StringView path) noexcept
    {
      usize dotPos = findLastDot(path);
      if (dotPos == kInvalidPos)
      {
        return StringView();
      }

      usize sepPos = findLastSeparator(path);
      if ((sepPos != kInvalidPos) && (dotPos < sepPos))
      {
        return StringView();
      }

      if (dotPos + 1 >= path.size())
      {
        return StringView();
      }

      return StringView(path.data() + dotPos + 1, path.size() - dotPos - 1);
    }

    /**
     * @brief Returns whether the path has a valid file extension.
     * @bug No known bugs
     */
    static bool
    hasExtension(StringView path) noexcept
    {
      return !getExtension(path).empty();
    }

    /**
     * @brief Returns the file name portion of the path.
     * @bug No known bugs
     */
    static StringView
    getFileName(StringView path) noexcept
    {
      usize sepPos = findLastSeparator(path);
      if (sepPos == kInvalidPos)
      {
        return path;
      }

      if (sepPos + 1 >= path.size())
      {
        return StringView();
      }

      return StringView(path.data() + sepPos + 1, path.size() - sepPos - 1);
    }

    /**
     * @brief Returns the file name without its extension.
     * @bug No known bugs
     */
    static StringView
    getFileStem(StringView path) noexcept
    {
      StringView fileName = getFileName(path);
      usize dotPos = findLastDot(fileName);
      if (dotPos == kInvalidPos)
      {
        return fileName;
      }

      return StringView(fileName.data(), dotPos);
    }

    /**
     * @brief Returns the parent path portion.
     * @bug No known bugs
     */
    static StringView
    getParentPath(StringView path) noexcept
    {
      usize sepPos = findLastSeparator(path);
      if (sepPos == kInvalidPos)
      {
        return StringView();
      }

      return StringView(path.data(), sepPos);
    }

    /**
     * @brief Returns a normalized path using forward slashes.
     * @bug No known bugs
     */
    static std::string
    normalize(StringView path)
    {
      std::string out;
      out.reserve(path.size());

      bool lastWasSeparator = false;

      for (usize i = 0; i < path.size(); ++i)
      {
        char c = path[i];
        if (isSeparator(c))
        {
          if (!lastWasSeparator)
          {
            out.push_back('/');
            lastWasSeparator = true;
          }
        }
        else
        {
          out.push_back(c);
          lastWasSeparator = false;
        }
      }

      return out;
    }

    /**
     * @brief Joins two path parts and normalizes separators.
     * @bug No known bugs
     */
    static std::string
    join(StringView a, StringView b)
    {
      if (a.empty())
      {
        return normalize(b);
      }

      if (b.empty())
      {
        return normalize(a);
      }

      std::string out = normalize(a);

      if (!out.empty() && !isSeparator(out.back()))
      {
        out.push_back('/');
      }

      usize start = 0;
      while ((start < b.size()) && isSeparator(b[start]))
      {
        ++start;
      }

      for (usize i = start; i < b.size(); ++i)
      {
        char c = b[i];
        if (isSeparator(c))
        {
          out.push_back('/');
        }
        else
        {
          out.push_back(c);
        }
      }

      return out;
    }

   private:
    static constexpr usize kInvalidPos = static_cast<usize>(-1);

    /**
     * @brief Returns the last separator position in the path.
     * @bug No known bugs
     */
    static usize
    findLastSeparator(StringView path) noexcept
    {
      for (usize i = path.size(); i > 0; --i)
      {
        if (isSeparator(path[i - 1]))
        {
          return i - 1;
        }
      }

      return kInvalidPos;
    }

    /**
     * @brief Returns the last dot position in the path.
     * @bug No known bugs
     */
    static usize
    findLastDot(StringView path) noexcept
    {
      for (usize i = path.size(); i > 0; --i)
      {
        if (path[i - 1] == '.')
        {
          return i - 1;
        }
      }

      return kInvalidPos;
    }
  };
} // namespace nyEngineSDK