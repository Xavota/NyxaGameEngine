#pragma once

#include "macros/nyMacros.hpp"

using namespace nyEngineSDK;

namespace assertTestUtility
{
  // Stores information about the most recent assertion.
  struct AssertCapture
  {
    bool triggered = false;
    const char* expression = nullptr;
    const char* file = nullptr;
    const char* message = nullptr;
    int line = 0;
  };

  static AssertCapture gAssertCapture;


  // This function temporarily replaces Nyxa's normal assertion handler
  // during tests.
  //
  // Instead of breaking into the debugger or aborting the program,
  // it records the assertion information and returns.
  static void testAssertHandler(
    const char* expr,
    const char* file,
    int line,
    const char* msg) noexcept
  {
    gAssertCapture.triggered = true;
    gAssertCapture.expression = expr;
    gAssertCapture.file = file;
    gAssertCapture.line = line;
    gAssertCapture.message = msg;
  }


  // Clears information from a previous assertion.
  static void resetAssertCapture() noexcept
  {
    gAssertCapture = {};
  }


  // Temporarily installs an assertion handler.
  //
  // When this object goes out of scope, the previous Nyxa assertion
  // handler is automatically restored.
  class AssertHandlerGuard
  {
  public:
    explicit AssertHandlerGuard(AssertHandlerFn handler) noexcept
      : mPreviousHandler(getAssertHandler())
    {
      setAssertHandler(handler);
    }

    ~AssertHandlerGuard()
    {
      setAssertHandler(mPreviousHandler);
    }

    AssertHandlerGuard(const AssertHandlerGuard&) = delete;
    AssertHandlerGuard&
      operator=(const AssertHandlerGuard&) = delete;

  private:
    AssertHandlerFn mPreviousHandler;
  };
}