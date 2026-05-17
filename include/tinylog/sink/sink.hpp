#pragma once

#include <string>

#include "tinylog/level.hpp"
#include "tinylog/log_msg.hpp"

namespace sink {

using tinylog::LogMessage;
using tinylog::Level;

class Sink {
public:
    virtual ~Sink() = default;

    void log(const LogMessage& msg) {
        if(!should_sink(msg)){
            return;
        }
        sink_it_(msg);
    }

    void flush() {
        flush_();
    }

    void set_level(Level lvl){
        level_ = lvl;
    }
    void set_pattern(std::string pattern){

    }

    bool should_sink(const LogMessage& msg){
        return msg.level >= level_;
    }

protected:
    // virtual void sink_it_(const log_msg& msg) = 0;
    virtual void flush_() = 0;
    virtual void sink_it_(const LogMessage& msg) = 0;

private:
    Level level_{Level::DEBUG};
    // std::unique_ptr<formatter> formatter_;
};
}
