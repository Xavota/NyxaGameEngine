#include "nyLog.hpp"

#include <atomic>
#include <cstdlib>

#include "macros/nyMacros.hpp"

namespace nyEngineSDK
{
  namespace
  {
    void
    default_sink(LogLevel lvl, StringView, StringView, StringView) noexcept {
      if (lvl == LogLevel::Fatal) {
#if NY_BUILD_DEBUG
        NY_DEBUG_BREAK();
#else
        std::abort();
#endif
      }
    }

    std::atomic<LogSinkFn> g_sink{ &default_sink };
    std::atomic<LogLevel>  g_level{ LogLevel::Info };
  }

  void
  set_log_sink(LogSinkFn fn) noexcept {
    g_sink.store(fn ? fn : &default_sink, std::memory_order_relaxed);
  }

  LogSinkFn get_log_sink() noexcept {
    return g_sink.load(std::memory_order_relaxed);
  }

  void set_log_level(LogLevel lvl) noexcept {
    g_level.store(lvl, std::memory_order_relaxed);
  }

  LogLevel get_log_level() noexcept {
    return g_level.load(std::memory_order_relaxed);
  }

  bool log_enabled(LogLevel lvl) noexcept {
    auto cur = g_level.load(std::memory_order_relaxed);
    return static_cast<u8>(lvl) >= static_cast<u8>(cur);
  }

  void log_text(LogLevel lvl, StringView engine, StringView module, StringView text) noexcept {
    if (!log_enabled(lvl)) return;
    auto sink = g_sink.load(std::memory_order_relaxed);
    sink(lvl, engine, module, text);
    if (lvl == LogLevel::Fatal) {
      NY_PANIC("Fatal log");
    }
  }
}