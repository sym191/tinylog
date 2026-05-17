#pragma once

#include <array>
#include <chrono>
#include <ctime>
#include <format>
#include <string>
#include <string_view>

#include "tinylog/log_msg.hpp"

namespace tinylog {

class Formatter {
public:
    virtual ~Formatter() = default;

    virtual std::string_view format(const LogMessage& msg) = 0;
};

class DefaultFormatter final : public Formatter {
public:
    std::string_view format(const LogMessage& msg) override {
        const auto seconds = std::chrono::floor<std::chrono::seconds>(msg.time);
        const auto milliseconds =
            std::chrono::duration_cast<std::chrono::milliseconds>(msg.time - seconds);
        const auto time = std::chrono::system_clock::to_time_t(seconds);
        const auto local_time = to_local_time(time);

        std::array<char, 20> timestamp{};
        std::strftime(timestamp.data(), timestamp.size(), "%Y-%m-%d %H:%M:%S", &local_time);

        buffer_ = std::format("[{}.{:03}] [{}] [{}] {}",
                              timestamp.data(),
                              milliseconds.count(),
                              msg.log_name,
                              level_name(msg.level),
                              msg.payload);
        return buffer_;
    }

private:
    static std::string_view level_name(Level level) {
        switch (level) {
            case Level::DEBUG:
                return "debug";
            case Level::INFO:
                return "info";
            case Level::ERR:
                return "error";
        }
        return "unknown";
    }

    static std::tm to_local_time(std::time_t time) {
        std::tm local_time{};
#if defined(_WIN32)
        localtime_s(&local_time, &time);
#else
        localtime_r(&time, &local_time);
#endif
        return local_time;
    }

    std::string buffer_;
};

} // namespace tinylog
