#pragma once

#include <atomic>
#include <chrono>
#include <format>
#include <memory>
#include <source_location>
#include <string>
#include <thread>
#include <type_traits>
#include <utility>
#include <vector>

#include "tinylog/level.hpp"
#include "tinylog/log_msg.hpp"
#include "tinylog/sink/sink.hpp"

namespace tinylog {

using sink::Sink;

template <typename... Args>
struct FormatStringWithLocation {
    template <typename T>
    consteval FormatStringWithLocation(
        const T& fmt,
        std::source_location source = std::source_location::current())
        : fmt(fmt), source(source) {}

    std::format_string<Args...> fmt;
    std::source_location source;
};

class Logger{
public:

    Logger(std::string name):name_(std::move(name)), sinks_{}, level_{} {}

    Logger(std::string name, std::shared_ptr<Sink> sink): name_(std::move(name)), sinks_{sink}, level_{} {}

    template<typename It>
    Logger(std::string name, It begin, It end): name_(std::move(name)), sinks_(begin, end), level_{} {}

    template<typename... Args>
    void log(Level lv,
             FormatStringWithLocation<std::type_identity_t<Args>...> fmt,
             Args&&... args){
            log_(fmt.source,
                 std::chrono::system_clock::now(),
                 lv,
                 fmt.fmt,
                 std::forward<Args>(args)...);
    }

    template<typename... Args>
    void info(FormatStringWithLocation<std::type_identity_t<Args>...> fmt, Args&&... args){
        log(Level::INFO, fmt, std::forward<Args>(args)...);
    }

    void set_level(Level lv){
        level_.store(lv);
    }

    void set_pattern(std::string pattern){

    }

    void flush(){

    }

    bool should_log(Level lv){
        return lv >= level_.load(std::memory_order_relaxed);
    }

private:
    template <typename... Args>
    void log_(const std::source_location source, std::chrono::system_clock::time_point time, Level lv, std::format_string<Args...> fmt, Args&&... args){
        if(!should_log(lv)){
            return;
        }
        LogMessage msg{
            .log_name = name_,
            .level = lv,
            .time = time,
            .thread_id = std::this_thread::get_id(),
            .payload = std::format(fmt, std::forward<Args>(args)...),
            .source = source
        };
        for(auto& sink : sinks_){
            sink->log(msg);
        }
    }

    std::string name_;
    std::vector<std::shared_ptr<Sink>> sinks_;
    std::atomic<Level> level_;
};

}// namespace tinylog
