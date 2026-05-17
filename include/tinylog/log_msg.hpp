#pragma once

#include "tinylog/level.hpp"
#include <chrono>
#include <source_location>
#include <string>
#include <string_view>
#include <thread>

namespace tinylog {

struct LogMessage{
    std::string_view log_name;
    Level level;
    std::chrono::system_clock::time_point time;
    std::thread::id thread_id;
    std::string payload;
    std::source_location source;
};

}
