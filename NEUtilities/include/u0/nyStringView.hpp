/*****************************************************************************/
/**
 * @file    nyStringView.hpp
 * @author  Dalia Castellanos
 * @date    07/02/2026
 * @brief   Defines a simple string view type for the Utilities library.
 *
 * Defines a simple `StringView` class that represents a non-owning view of a
 * contiguous sequence of characters. The `StringView` class provides basic
 * functionality for accessing the underlying data, such as size, emptiness, and
 * character access. The `StringView` class can be used to safely pass around views
 * of strings without copying or taking ownership of the data.
 *
 * @bug	    No known bugs.
 */
 /*****************************************************************************/
#pragma once

#include "u0/nyTypes.hpp"

namespace nyEngineSDK
{
  /*
   * @brief  Represents a non-owning view of a contiguous sequence of characters.
   * @bug    No known bugs.
   */
  class StringView
  {
   public:
   /*
    * @brief  Constructs an empty string view.
    * @bug    No known bugs.
    */
    constexpr StringView() noexcept : m_data(nullptr), m_size(0) {}
    /*
     * @brief  Constructs a string view from a pointer and size.
     * @bug    No known bugs.
     */
    constexpr StringView(const char* s, usize n) noexcept : m_data(s), m_size(n) {}
    /*
     * @brief  Constructs a string view from a null-terminated C-string. If the
     *         pointer is null, the string view will be empty.
     * @param  zstr  Pointer to a null-terminated C-string. If null, the string view will be empty.
     * @bug    No known bugs.
     */
    constexpr StringView(const char* zstr) noexcept : m_data(zstr), m_size(calc_len(zstr)) {}

    /*
     * @brief  Returns a pointer to the first character of the string view.
     * @return Pointer to the first character of the string view. If the view
     *         is empty, this may be null or point to a null terminator.
     * @bug    No known bugs.
     */
    constexpr const char* data() const noexcept { return m_data; }

    /*
     * @brief  Returns the number of characters in the string view.
     * @return Number of characters in the string view. This does not include
     *         any null terminator.
     * @bug    No known bugs.
     */
    constexpr usize size() const noexcept { return m_size; }
    /*
     * @brief  Returns whether the string view is empty (i.e. has zero size).
     * @return True if the string view is empty, false otherwise.
     * @bug    No known bugs.
     */
    constexpr bool empty() const noexcept { return m_size == 0; }

    /*
     * @brief  Returns a reference to the character at the specified index in
     *         the string view.
     *         string view.
     * @param  i  The index of the character to access. Must be less than the
     *            size of the string view.
     * @return A reference to the character at the specified index in the string view.
     * @bug    No known bugs.
     */
    constexpr const char& operator[](usize i) const noexcept {
      NY_ASSERT(i < m_size);
      return m_data[i];
    }

   private:
     /*
      * @brief  Helper function to calculate the length of a null-terminated C-string
      *         at compile time.
      * @param  s  Pointer to a null-terminated C-string. If null, returns 0.
      * @return The length of the C-string (number of characters before the null
      * @bug    No known bugs.
      */
    static constexpr usize calc_len(const char* s) noexcept {
      if (!s) return 0;
      usize n = 0;
      while (s[n] != '\0') ++n;
      return n;
    }


    /*
     * @brief  Pointer to the first character of the string view. This may be null
     */
    const char* m_data;
    /*
     * @brief  Number of characters in the string view. This does not include any
     */
    usize m_size;
  };
} // namespace nyEngineSDK