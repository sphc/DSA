#include "TimeTool.h"
#include <ctime>
#include <memory>

struct TimeTool::Impl {
    std::time_t time;
    uint32_t repeatTimes;

    void start() {
        time = std::time(NULL);
    }

    long duration() {
        return (std::time(NULL) - time);
    }
};

TimeTool::TimeTool(uint32_t repeatTimes) :
    __pimpl{std::make_unique<Impl>(Impl{0, repeatTimes})} {
}
TimeTool::~TimeTool() = default;

long TimeTool::test(std::function<void(void)> func) {
    __pimpl->start();
    for (uint32_t i = 0; i < __pimpl->repeatTimes; ++i) {
        func();
    }
    return __pimpl->duration();
}
