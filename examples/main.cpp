#include "tinylog/level.hpp"
#include "tinylog/logger.hpp"
#include "tinylog/sink/ostream_sink.hpp"

#include <iostream>
#include <memory>

int main(){
    auto sink_ptr = std::make_shared<sink::OStreamSink>(std::cout);
    tinylog::Logger logger{"test", sink_ptr};
    logger.info("hello {}", "tinylog");
    logger.log(tinylog::Level::ERR, "err ocur {}", "stackoverflow");
}