#include "file/nyPath.h"

#include <filesystem>

namespace nyEngineSDK
{
  namespace
  {
    /**
     * @brief  Converts backslashes to forward slashes.
     * @bug    No known bugs
     */
    String
    normalizeSeparators(const String& path)
    {
      String out;
      out.reserve(path.size());

      bool lastWasSeparator = false;

      for (usize i = 0; i < path.size(); ++i)
      {
        char c = path[i];
        if (Path::isSeparator(c))
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
  } // namespace

  StringView
  Path::getExtension(StringView path) noexcept
  {
    usize dotPos = findLastDot(path);
    if (dotPos == kInvalidPos || dotPos + 1 >= path.size())
    {
      return StringView();
    }

    usize sepPos = findLastSeparator(path);
    if ((sepPos != kInvalidPos) && (dotPos < sepPos))
    {
      return StringView();
    }

    return StringView(path.data() + dotPos + 1, path.size() - dotPos - 1);
  }

  StringView
  Path::getFileName(StringView path) noexcept
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

  StringView
  Path::getFileStem(StringView path) noexcept
  {
    StringView fileName = getFileName(path);
    usize dotPos = findLastDot(fileName);
    if (dotPos == kInvalidPos)
    {
      return fileName;
    }

    return StringView(fileName.data(), dotPos);
  }

  StringView
  Path::getParentPath(StringView path) noexcept
  {
    usize sepPos = findLastSeparator(path);
    if (sepPos == kInvalidPos)
    {
      return StringView();
    }

    return StringView(path.data(), sepPos);
  }

  String
  Path::normalize(StringView path) noexcept
  {
    String result(path.data(), path.size());
    return normalizeSeparators(result);
  }

  bool
  Path::isAbsolute(StringView path) noexcept
  {
    std::filesystem::path p(String(path.data(), path.size()));
    return p.is_absolute();
  }

  String
  Path::makeAbsolute(StringView path) noexcept
  {
    std::filesystem::path p(std::string(path.data(), path.size()));
    std::filesystem::path abs = std::filesystem::absolute(p);

    return normalizeSeparators(abs.string());
  }

  String
  Path::normalizeAbsolute(StringView path) noexcept
  {
    std::filesystem::path p(std::string(path.data(), path.size()));
    std::filesystem::path abs = std::filesystem::absolute(p);

    abs = abs.lexically_normal();

    return normalizeSeparators(abs.string());
  }

  String
  Path::join(StringView a, StringView b) noexcept
  {
    if (a.empty())
    {
      return normalize(b);
    }

    if (b.empty())
    {
      return normalize(a);
    }

    String out = normalize(a);

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

  usize
  Path::findLastSeparator(StringView path) noexcept
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

  usize
  Path::findLastDot(StringView path) noexcept
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
}