// Aleth: Ethereum C++ client, tools and libraries.
// Copyright 2014-2019 Aleth Authors.
// Licensed under the GNU General Public License, Version 3.

#pragma once

#include "CommonIO.h"
#include "FixedHash.h"
#include "Terminal.h"
#include <string>
#include <vector>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include <map>
#include <optional>

namespace dev
{

/// For better formatting it is recommended to limit thread name to max 4 characters.
void setThreadName(std::string const& _n);

/// Set the current thread's log name.
std::string getThreadName();

#define LOG(logger) logger.CreateStream()

enum Verbosity
{
    VerbositySilent = -1,
    VerbosityError = 0,
    VerbosityWarning = 1,
    VerbosityInfo = 2,
    VerbosityDebug = 3,
    VerbosityTrace = 4,
};

class SpdlogStreamInput {
  public:
    SpdlogStreamInput(std::optional<spdlog::level::level_enum> level)
      : level_{level} {}

    ~SpdlogStreamInput() {
        if (level_) {
          spdlog::log(*level_, "aleth: {}", fmt::to_string(mb_));
        }
    }

    template<typename T>
    SpdlogStreamInput& operator<<(const T& value) {
        if (level_) {
         fmt::format_to(mb_, "{}", value);
        }
      return *this;
    }

  private:
    std::optional<spdlog::level::level_enum> level_;
    fmt::memory_buffer mb_;
};

class SpdlogWrapper {
  public:
    SpdlogWrapper(Verbosity verbosity) {
        switch (verbosity) {
            case VerbosityError: level_ = spdlog::level::err; break;
            case VerbosityWarning: level_ = spdlog::level::warn; break;
            case VerbosityInfo: level_ = spdlog::level::info; break;
            case VerbosityDebug: level_ = spdlog::level::debug; break;
            case VerbosityTrace: level_ = spdlog::level::trace; break;
            case VerbositySilent: break;
            default: throw std::runtime_error("invalid verbosity");
        }
    }

    SpdlogStreamInput CreateStream() {
        return SpdlogStreamInput(level_);
    }

  private:
    std::optional<spdlog::level::level_enum> level_;
};

// Simple cout-like stream objects for accessing common log channels.
// Thread-safe
inline SpdlogWrapper g_errorLogger{VerbosityError};
inline SpdlogWrapper g_warningLogger{VerbosityWarning};
inline SpdlogWrapper g_infoLogger{VerbosityInfo};
inline SpdlogWrapper g_debugLogger{VerbosityDebug};
inline SpdlogWrapper g_traceLogger{VerbosityTrace};

#define cerror LOG(dev::g_errorLogger)
#define cwarn LOG(dev::g_warningLogger)
#define cnote LOG(dev::g_infoLogger)
#define cdebug LOG(dev::g_debugLogger)
#define ctrace LOG(dev::g_traceLogger)

// Simple macro to log to any channel a message without creating a logger object
// e.g. clog(VerbosityInfo, "channel") << "message";
// Thread-safe
#define clog(SEVERITY, CHANNEL)  \
    LOG(SpdlogWrapper(SEVERITY))

struct LoggingOptions
{
    int verbosity = VerbosityInfo;
    strings includeChannels;
    strings excludeChannels;
    bool vmTrace = false;
};

// Should be called in every executable
void setupLogging(LoggingOptions const& _options);

bool isVmTraceEnabled();

// Simple non-thread-safe logger with fixed severity and channel for each message
// For better formatting it is recommended to limit channel name to max 6 characters.
using Logger = SpdlogWrapper;
inline Logger createLogger(int _severity, std::string const& _channel)
{
    return Logger(static_cast<Verbosity>(_severity));
}

}  // namespace dev

namespace fmt {

template <typename T, typename U>
struct formatter<std::pair<T, U>> : fmt::formatter<std::string> {
  template <typename FormatContext>
  auto format(const std::pair<T, U>& p, FormatContext& ctx) {
    return format_to(ctx.out(), "({}, {})", p.first, p.second);
  }
};

template <typename T, typename U>
struct formatter<std::map<T, U>> : fmt::formatter<std::string> {
  template <typename FormatContext>
  auto format(const std::map<T, U>& m, FormatContext& ctx) {
    auto out = ctx.out();

    out = format_to(out, "[");

    bool first = true;
    for (const auto& [key, value] : m) {
      if (first) {
        out = format_to(out, "({}, {})", key, value);
        first = false;
      }
      else {
        out = format_to(out, ", ({}, {})", key, value);
      }
    }

    out = format_to(out, "]");

    return out;
  }
};

}  // namespace fmt
