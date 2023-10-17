#ifndef __TIME_TOOL_H__
#define __TIME_TOOL_H__

#include <functional>
#include <memory>

class TimeTool {
public:
    TimeTool(uint32_t repeatTimes = 1);
    TimeTool(const TimeTool &) = delete;
    TimeTool(TimeTool &&) = delete;
    TimeTool &operator=(const TimeTool &) = delete;
    TimeTool &operator=(const TimeTool &&) = delete;
    ~TimeTool();
    long test(std::function<void(void)> func);

private:
    struct Impl;
    std::unique_ptr<Impl> __pimpl;
};

#endif