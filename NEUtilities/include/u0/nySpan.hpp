/******************************************************************************/
/**
 * @file    nySpan.hpp
 * @author  Dalia Castellanos
 * @date    07/02/2026
 * @brief   Defines a simple span type for the Utilities library.
 *
 * Defines a simple `Span` template class that represents a non-owning view of a
 * contiguous sequence of elements. The `Span` class provides basic functionality
 * for accessing the underlying data, such as size, emptiness, and element
 * access. The `Span` class can be used to safely pass around views of arrays,
 * vectors, or other contiguous data structures without copying or taking
 * ownership of the data.
 *
 * @bug	    No known bugs.
 */
/******************************************************************************/
#pragma once

#include <type_traits>

#include "u0/nyTypes.hpp"

namespace nyEngineSDK
{
  /**
   * @brief  Represents a non-owning view of a contiguous sequence of elements.
   * @bug    No known bugs.
   */
  template <class T>
  class Span {
  public:
    using element_type = T;
    using value_type = typename std::remove_cv<T>::type;
    using pointer = T*;
    using reference = T&;

    /**
     * @brief  Constructs an empty span.
     * @bug    No known bugs.
     */
    constexpr Span() noexcept : mData(nullptr), mSize(0) {}
    /**
     * @brief  Constructs a span from a pointer and size.
     * @param  data  Pointer to the first element of the span.
     * @param  size  Number of elements in the span.
     * @bug    No known bugs.
     */
    constexpr Span(T* data, usize size) noexcept : mData(data), mSize(size) {}

    /**
     * @brief  Constructs a span from a C-style array.
     * @param  arr  C-style array to create the span from.
     * @bug    No known bugs.
     */
    template <usize N>
    constexpr Span(T(&arr)[N]) noexcept : mData(arr), mSize(N) {}

    /**
     * @brief  Returns a pointer to the first element of the span.
     * @return A pointer to the first element of the span.
     * @bug    No known bugs.
     */
    constexpr T* data() const noexcept { return mData; }
    /**
     * @brief  Returns the number of elements in the span.
     * @return The number of elements in the span.
     * @bug    No known bugs.
     */
    constexpr usize size() const noexcept { return mSize; }
    /**
     * @brief  Returns true if the span is empty (i.e., has zero elements).
     * @return True if the span is empty, false otherwise.
     * @bug    No known bugs.
     */
    constexpr bool empty() const noexcept { return mSize == 0; }

    /**
     * @brief  Returns a reference to the element at the specified index in the span.
     * @param  i  The index of the element to access. Must be less than the size of the span.
     * @return A reference to the element at the specified index in the span.
     * @bug    No known bugs.
     */
    constexpr T& operator[](usize i) const noexcept {
      NY_ASSERT(i < mSize);
      return mData[i];
    }

    /**
     * @brief  Returns an iterator to the first element of the span.
     * @return An iterator to the first element of the span.
     * @bug    No known bugs.
     */
    constexpr T* begin() const noexcept { return mData; }
    /**
     * @brief  Returns an iterator to one past the last element of the span.
     * @return An iterator to one past the last element of the span.
     * @bug    No known bugs.
     */
    constexpr T* end() const noexcept { return mData + mSize; }

  private:
    /**
     * @brief  Pointer to the first element of the span.
     */
    T* mData;
    /**
     * @brief  Number of elements in the span.
     */
    usize mSize;
  };

} // namespace nyEngineSDK