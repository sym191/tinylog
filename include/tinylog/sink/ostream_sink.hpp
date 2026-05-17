#pragma once

#include "tinylog/formatter.hpp"
#include "tinylog/sink/sink.hpp"
#include <ostream>

namespace sink {

class OStreamSink : public Sink{
public:
    explicit OStreamSink(std::ostream& ostream): ostream_(ostream) {}

protected:
    void flush_() override{
        ostream_.flush();
    }
    void sink_it_(const LogMessage& msg) override{
        ostream_ << formatter_.format(msg) << '\n';
        
    }

private:
    std::ostream& ostream_;
    tinylog::DefaultFormatter formatter_;

};

} 
