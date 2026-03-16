/******************************************************************************/
/**
 * @file    nyFile.hpp
 * @author  Dalia Castellanos
 * @date    11/03/2026
 * @brief   Defines file utilities for reading and writing to system files.
 * 
 * A File class that defines several utility options for reading and writing,
 * both bytes and plain characters, onto or from system files.
 *
 * @bug	    No known bugs.
 */
 /******************************************************************************/
#pragma once

#include "macros/nyApi.hpp"
#include "memory/nyByteBuffer.hpp"

#include "types/nyContainers.h"
#include "types/nyResult.hpp"
#include "types/nyStringView.hpp"
#include "types/nyTypes.hpp"

#include <string>

namespace nyEngineSDK
{
  /**
   * @brief  File utilities for reading files and querying file state.
   * @bug    No known bugs
   */
  class File
  {
  public:
    /**
     * @brief  Returns whether a file system entry exists at the given path.
     * @bug    No known bugs
     */
    static Result<bool>
    exists(StringView path) noexcept;

    /**
     * @brief  Reads the entire file as binary data into a ByteBuffer.
     * @bug    No known bugs
     */
    static Result<ByteBuffer>
    readEntireFile(StringView path, Allocator& allocator) noexcept;

    /**
     * @brief  Reads the entire file as text into a String.
     * @bug    No known bugs
     */
    static Result<String>
    readEntireTextFile(StringView path) noexcept;

    /**
     * @brief  Returns the last write time in nanoseconds for the given path.
     * @bug    No known bugs
     */
    static Result<Duration>
    getLastWriteTime(StringView path) noexcept;

    /**
     * @brief  Writes binary data to a file.
     * @bug    No known bugs
     */
    static Result<void>
    writeEntireFile(StringView path, const void* data, usize sizeBytes) noexcept;
    
    /**
     * @brief  Writes a text file.
     * @bug    No known bugs
     */
    static Result<void>
    writeEntireTextFile(StringView path, StringView text) noexcept;
  };
} // namespace nyEngineSDK