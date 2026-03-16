#include "file/nyFile.h"

#include <chrono>
#include <filesystem>
#include <fstream>
#include <string>

#include "nyLog.hpp"

#include "macros/nyModuleName.h"
#include "macros/nyResultMacros.hpp"

#include "file/nyPath.h"

#include "types/nyContainers.h"

namespace nyEngineSDK
{
  namespace
  {
    /**
     * @brief  Converts a StringView path into a normalized String.
     * @bug    No known bugs
     */
    String
    toFsPath(StringView path)
    {
      return Path::normalize(path);
    }
  } // namespace

  Result<bool>
  File::exists(StringView path) noexcept
  {
    try
    {
      const String fsPath = toFsPath(path);
      return std::filesystem::exists(fsPath);
    }
    catch (const std::exception& e)
    {
      return NY_ERRF(
        LogLevel::Error,
        kModule,
        "Failed to check existence of '{}': {}",
        path,
        e.what()
      );
    }
    catch (...)
    {
      return NY_ERRF(
        LogLevel::Error,
        kModule,
        "Failed to check existence of '{}': unknown error",
        path
      );
    }
  }

  Result<ByteBuffer>
  File::readEntireFile(StringView path, Allocator& allocator) noexcept
  {
    try
    {
      const String fsPath = toFsPath(path);

      std::ifstream file(fsPath, std::ios::binary | std::ios::ate);
      if (!file.is_open())
      {
        return NY_ERRF(
          LogLevel::Error,
          kModule,
          "Failed to open file '{}'",
          path
        );
      }

      const std::ifstream::pos_type endPos = file.tellg();
      if (endPos < 0)
      {
        return NY_ERRF(
          LogLevel::Error,
          kModule,
          "Failed to determine size of file '{}'",
          path
        );
      }

      const usize fileSize = static_cast<usize>(endPos);

      ByteBuffer buffer(allocator);
      if (!buffer.resize(fileSize))
      {
        return NY_ERRF(
          LogLevel::Error,
          kModule,
          "Failed to allocate {} bytes for file '{}'",
          static_cast<u64>(fileSize),
          path
        );
      }

      file.seekg(0, std::ios::beg);

      if (fileSize > 0)
      {
        file.read(reinterpret_cast<char*>(buffer.data()), endPos);
        if (!file)
        {
          return NY_ERRF(
            LogLevel::Error,
            kModule,
            "Failed to read {} bytes from file '{}'",
            static_cast<u64>(fileSize),
            path
          );
        }
      }

      return buffer;
    }
    catch (const std::exception& e)
    {
      return NY_ERRF(
        LogLevel::Error,
        kModule,
        "Failed to read file '{}': {}",
        path,
        e.what()
      );
    }
    catch (...)
    {
      return NY_ERRF(
        LogLevel::Error,
        kModule,
        "Failed to read file '{}': unknown error",
        path
      );
    }
  }

  Result<String>
  File::readEntireTextFile(StringView path) noexcept
  {
    try
    {
      const String fsPath = toFsPath(path);

      std::ifstream file(fsPath, std::ios::binary | std::ios::ate);
      if (!file.is_open())
      {
        return NY_ERRF(
          LogLevel::Error,
          kModule,
          "Failed to open text file '{}'",
          path
        );
      }

      const std::ifstream::pos_type endPos = file.tellg();
      if (endPos < 0)
      {
        return NY_ERRF(
          LogLevel::Error,
          kModule,
          "Failed to determine size of text file '{}'",
          path
        );
      }

      const usize fileSize = static_cast<usize>(endPos);

      String text;
      text.resize(fileSize);

      file.seekg(0, std::ios::beg);

      if (fileSize > 0)
      {
        file.read(&text[0], endPos);
        if (!file)
        {
          return NY_ERRF(
            LogLevel::Error,
            kModule,
            "Failed to read {} bytes from text file '{}'",
            static_cast<u64>(fileSize),
            path
          );
        }
      }

      return text;
    }
    catch (const std::exception& e)
    {
      return NY_ERRF(
        LogLevel::Error,
        kModule,
        "Failed to read text file '{}': {}",
        path,
        e.what()
      );
    }
    catch (...)
    {
      return NY_ERRF(
        LogLevel::Error,
        kModule,
        "Failed to read text file '{}': unknown error",
        path
      );
    }
  }

  Result<Duration>
  File::getLastWriteTime(StringView path) noexcept
  {
    try
    {
      const String fsPath = toFsPath(path);

      const auto time = std::filesystem::last_write_time(fsPath);
      const auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
        time.time_since_epoch()
      ).count();

      return Duration(0, 0, 0, 0, 0, 0, static_cast<u64>(ns));
    }
    catch (const std::exception& e)
    {
      return NY_ERRF(
        LogLevel::Error,
        kModule,
        "Failed to get last write time of '{}': {}",
        path,
        e.what()
      );
    }
    catch (...)
    {
      return NY_ERRF(
        LogLevel::Error,
        kModule,
        "Failed to get last write time of '{}': unknown error",
        path
      );
    }
  }
  Result<void> File::writeEntireFile(StringView path, const void* data, usize sizeBytes) noexcept
  {
    try
    {
      const String fsPath = toFsPath(path);

      std::ofstream file(fsPath, std::ios::binary | std::ios::trunc);
      if (!file.is_open())
      {
        return NY_ERRF(
          LogLevel::Error,
          kModule,
          "Failed to open file '{}' for writing",
          path
        );
      }

      if (sizeBytes > 0)
      {
        file.write(reinterpret_cast<const char*>(data), sizeBytes);
        if (!file)
        {
          return NY_ERRF(
            LogLevel::Error,
            kModule,
            "Failed to write {} bytes to '{}'",
            static_cast<u64>(sizeBytes),
            path
          );
        }
      }

      return Status::ok();
    }
    catch (const std::exception& e)
    {
      return NY_ERRF(
        LogLevel::Error,
        kModule,
        "Failed writing '{}': {}",
        path,
        e.what()
      );
    }
    catch (...)
    {
      return NY_ERRF(
        LogLevel::Error,
        kModule,
        "Failed writing '{}': unknown error",
        path
      );
    }
  }

  Result<void> File::writeEntireTextFile(StringView path, StringView text) noexcept
  {
    return writeEntireFile(
      path,
      text.data(),
      text.size()
    );
  }
} // namespace nyEngineSDK