/******************************************************************************/
/**
 * @file    nyResult.hpp
 * @author  Dalia Castellanos
 * @date    18/02/2026
 * @brief   Defines a simple Result class for representing success or error results.
 * 
 * Defines a simple `Result` template class that represents the result of an
 * operation that can either succeed with a value of type T or fail with an
 * error status.
 *
 * @bug	    No known bugs.
 */
/******************************************************************************/
#pragma once

#include <new>
#include <type_traits>
#include <utility>

#include "u0/nyStatus.hpp"


namespace nyEngineSDK
{
  /**
   * @brief  Represents the result of an operation that can either succeed with
   *         a value of type T or fail with an error status.
   * @tparam T  The type of the value that represents a successful result. This
   *            can be any type, including void for operations that do not
   *            return a value.
   * @bug    No known bugs.
   */
  template <class T>
  class Result
  {
   public:
    /**
     * @brief  Constructs a Result object representing a successful result with
     *         the specified value.
     * @param  value  The value to store in the Result object, representing a
     *                successful result. This can be any type, including void
     *                for operations that do not return a value.
     * @bug    No known bugs.
     */
    Result(const T& value)
    noexcept(std::is_nothrow_copy_constructible<T>::value)
      : mHasValue(true)
    {
      new (&mStorage.value) T(value);
    }

    /**
     * @brief  Constructs a Result object representing a successful result with
     *         the specified value.
     * @param  value  The value to store in the Result object, representing a
     *                successful result. This can be any type, including void
     *                for operations that do not return a value.
     * @bug    No known bugs.
     */
    Result(T&& value)
    noexcept(std::is_nothrow_move_constructible<T>::value)
      : mHasValue(true)
    {
      new (&mStorage.value) T(std::move(value));
    }

    /**
     * @brief  Constructs a Result object representing an error result with the
     *         specified error status.
     * @param  error  The error status to store in the Result object,
     *                representing an error result. This should be a Status
     *                object that describes the error condition.
     * @bug    No known bugs.
     */
    Result(const Status& error) noexcept
      : mHasValue(false)
    {
      new (&mStorage.error) Status(error);
    }

    /**
     * @brief  Constructs a Result object representing an error result with the
     *         specified error status.
     * @param  error  The error status to store in the Result object,
     *                representing an error result. This should be a Status
     *                object that describes the error condition.
     * @bug    No known bugs.
     */
    Result(Status&& error) noexcept
      : mHasValue(false)
    {
      new (&mStorage.error) Status(std::move(error));
    }

    /**
     * @brief  Copy constructor for Result. Creates a new Result object by
     *         copying the value or error status from another Result object.
     * @param  other  The Result object to copy from. The new Result object will
     *                have the same value or error status as the other object.
     * @bug    No known bugs.
     */
    Result(const Result& other)
    noexcept(std::is_nothrow_copy_constructible<T>::value)
      : mHasValue(other.mHasValue)
    {
      if (mHasValue)
      {
        new (&mStorage.value) T(other.mStorage.value);
      }
      else
      {
        new (&mStorage.error) Status(other.mStorage.error);
      }
    }

    /**
     * @brief  Move constructor for Result. Creates a new Result object by
     *         moving the value or error status from another Result object.
     * @param  other  The Result object to move from. The new Result object will
     *                have the same value or error status as the other object,
     *                and the other object will be left in a valid but
     *                unspecified state.
     * @bug    No known bugs.
     */
    Result(Result&& other)
    noexcept(std::is_nothrow_move_constructible<T>::value)
      : mHasValue(other.mHasValue)
    {
      if (mHasValue)
      {
        new (&mStorage.value) T(std::move(other.mStorage.value));
      }
      else
      {
        new (&mStorage.error) Status(std::move(other.mStorage.error));
      }
    }

    /**
     * @brief  Copy assignment operator for Result. Assigns the value or error
     *         status from another Result object to this object. If this object
     *         already contains a value or error status, it will be destroyed
     *         before the new value or error status is assigned.
     * @param  other  The Result object to copy from. This object will have the
     *                same value or error status as the other object after the
     *                assignment.
     * @return A reference to this Result object after the assignment.
     * @bug    No known bugs.
     */
    Result&
    operator=(const Result& other)
    noexcept(std::is_nothrow_copy_constructible<T>::value)
    {
      if (this == &other)
      {
        return *this;
      }

      destroyActive();
      mHasValue = other.mHasValue;

      if (mHasValue)
      {
        new (&mStorage.value) T(other.mStorage.value);
      }
      else
      {
        new (&mStorage.error) Status(other.mStorage.error);
      }

      return *this;
    }

    /**
     * @brief  Move assignment operator for Result. Moves the value or error
     *         status from another Result object to this object. If this object
     *         already contains a value or error status, it will be destroyed
     *         before the new value or error status is assigned.
     * @param  other  The Result object to move from. This object will have the
     *                same value or error status as the other object after the
     *                assignment, and the other object will be left in a valid
     *                but unspecified state.
     * @return A reference to this Result object after the assignment.
     * @bug    No known bugs.
     */
    Result&
    operator=(Result&& other)
    noexcept(std::is_nothrow_move_constructible<T>::value)
    {
      if (this == &other)
      {
        return *this;
      }

      destroyActive();
      mHasValue = other.mHasValue;

      if (mHasValue)
      {
        new (&mStorage.value) T(std::move(other.mStorage.value));
      }
      else
      {
        new (&mStorage.error) Status(std::move(other.mStorage.error));
      }

      return *this;
    }

    /**
     * @brief  Destructor for Result. Destroys the active value or error status
     *         contained in the Result object. If the Result object contains a
     *         value, it will be destroyed. If it contains an error status, the
     *         error status will be destroyed.
     * @bug    No known bugs.
     */
    ~Result() noexcept
    {
      destroyActive();
    }


    /**
     * @brief  Returns true if the Result object contains a value
     *         (i.e., represents a successful result), or false if it contains
     *         an error status (i.e., represents an error result).
     * @return True if the Result object contains a value, false if it contains
     *         an error status.
     * @bug    No known bugs.
     */
    bool
    hasValue() const noexcept
    {
      return mHasValue;
    }

    /**
     * @brief  Explicit conversion operator to bool. Allows a Result object to
     *         be used in boolean contexts (e.g., if statements) to check if it
     *         contains a value (i.e., represents a successful result) or an
     *         error status (i.e., represents an error result).
     * @return True if the Result object contains a value, false if it contains
     *         an error status.
     * @bug    No known bugs.
     */
    explicit
    operator bool() const noexcept
    {
      return mHasValue;
    }

    /**
     * @brief  Returns a reference to the value contained in the Result object.
     * @return A reference to the value contained in the Result object.
     * @bug    No known bugs.
     */
    T&
    value() noexcept
    {
      NY_ASSERT(mHasValue);
      return mStorage.value;
    }

    /**
     * @brief  Returns a const reference to the value contained in the Result
     *         object.
     * @return A const reference to the value contained in the Result object.
     * @bug    No known bugs.
     */
    const T&
    value() const noexcept
    {
      NY_ASSERT(mHasValue);
      return mStorage.value;
    }

    /**
     * @brief  Returns a reference to the error status contained in the Result
     *         object.
     * @return A reference to the error status contained in the Result object.
     * @bug    No known bugs.
     */
    Status&
    error() noexcept
    {
      NY_ASSERT(!mHasValue);
      return mStorage.error;
    }

    /**
     * @brief  Returns a const reference to the error status contained in the
     *         Result object.
     * @return A const reference to the error status contained in the Result
     *         object.
     * @bug    No known bugs.
     */
    const Status&
    error() const noexcept
    {
      NY_ASSERT(!mHasValue);
      return mStorage.error;
    }

    /**
     * @brief  Returns a reference to the error status contained in the Result
     *         object. If the Result object currently contains a value, the
     *         value will be destroyed and replaced with a default-constructed
     *         error status before returning the reference to the error status.
     * @return A reference to the error status contained in the Result object.
     * @bug    No known bugs.
     */
    T
    takeValue() noexcept(std::is_nothrow_move_constructible<T>::value)
    {
      NY_ASSERT(mHasValue);
      T out = std::move(mStorage.value);
      destroyActive();
      mHasValue = false;
      new (&mStorage.error) Status(Status::ok());
      return out;
    }

   private:
    /**
     * @brief  Destroys the active value or error status contained in the Result
     *         object. If the Result object contains a value, it will be
     *         destroyed. If it contains an error status, the error status will
     *         be destroyed. This function is called by the destructor and
     *         assignment operators to clean up the active member before
     *         assigning a new value or error status.
     * @bug    No known bugs.
     */
    void
    destroyActive() noexcept
    {
      if (mHasValue)
      {
        mStorage.value.~T();
      }
      else
      {
        mStorage.error.~Status();
      }
    }

   private:
    union Storage
    {
      Storage() {}
      ~Storage() {}

      /**
       * @brief  The value contained in the Result object when it represents a
       *         successful result. This member is active when mHasValue is true.
       */
      T value;
      /**
       * @brief  The error status contained in the Result object when it represents
       *         an error result. This member is active when mHasValue is false.
       */
      Status error;
    };

    /**
     * @brief  Indicates whether the Result object currently contains a value or
     *         an error status. If mHasValue is true, the value member of the
     *         Storage union is active and contains the value of the successful
     *         result. If mHasValue is false, the error member of the Storage
     *         union is active and contains the error status of the error result.
     */
    Storage mStorage;
    /**
     * @brief  Indicates whether the Result object currently contains a value
     *         (true) or an error status (false).
     */
    bool mHasValue;
  };

  /**
   * @brief  Specialization of the Result class template for void. This
   *         specialization represents the result of an operation that can
   *         either succeed with no value (i.e., void) or fail with an error
   *         status.
   */
  template <>
  class Result<void>
  {
   public:
    /**
     * @brief  Constructs a Result object representing a successful result with
     *         no value. The Result object will contain a successful status with
     *         no message.
     * @bug    No known bugs.
     */
    Result() noexcept
      : mStatus(Status::ok())
    {
    }

    /**
     * @brief  Constructs a Result object representing an error result with the
     *         specified error status.
     * @param  error  The error status to store in the Result object,
     *                representing an error result. This should be a Status
     *                object that describes the error condition.
     * @bug    No known bugs.
     */
    Result(const Status& s) noexcept
      : mStatus(s)
    {
    }

    /**
     * @brief  Constructs a Result object representing an error result with the
     *         specified error status.
     * @param  error  The error status to store in the Result object,
     *                representing an error result. This should be a Status
     *                object that describes the error condition.
     * @bug    No known bugs.
     */
    Result(Status&& s) noexcept
      : mStatus(std::move(s))
    {
    }

    /**
     * @brief  Returns true if the Result object contains a value
     *         (i.e., represents a successful result), or false if it contains
     *         an error status (i.e., represents an error result).
     * @return True if the Result object contains a value, false if it contains
     *         an error status.
     * @bug    No known bugs.
     */
    bool
    hasValue() const noexcept
    {
      return mStatus.isOk();
    }

    /**
     * @brief  Explicit conversion operator to bool. Allows a Result object to
     *         be used in boolean contexts (e.g., if statements) to check if it
     *         contains a value (i.e., represents a successful result) or an
     *         error status (i.e., represents an error result).
     * @return True if the Result object contains a value, false if it contains
     *         an error status.
     * @bug    No known bugs.
     */
    explicit
    operator bool() const noexcept
    {
      return mStatus.isOk();
    }

    /**
     * @brief  Returns a const reference to the error status contained in the
     *         Result object.
     * @return A const reference to the error status contained in the Result
     *         object.
     * @bug    No known bugs.
     */
    Status&
    error() noexcept
    {
      NY_ASSERT(mStatus.isError());
      return mStatus;
    }

    /**
     * @brief  Returns a reference to the error status contained in the Result
     *         object.
     * @return A reference to the error status contained in the Result object.
     * @bug    No known bugs.
     */
    const Status&
      error() const noexcept
    {
      NY_ASSERT(mStatus.isError());
      return mStatus;
    }

    /**
     * @brief  Returns a reference to the status contained in the Result object.
     * @return A reference to the status contained in the Result object.
     * @bug    No known bugs.
     */
    const Status&
    status() const noexcept
    {
      return mStatus;
    }

   private:
    /**
     * @brief  The error status contained in the Result object when it represents
     *         an error result. This member is active when mHasValue is false.
     */
    Status mStatus;
  };
} // namespace nyEngineSDK