#ifndef __QUEUE_EXCEPTION_H__
#define __QUEUE_EXCEPTION_H__

#include <stdexcept>
#include <string>

namespace dsa {
/*
 * @Author       : sphc
 * @Date         : 2023-11-07 10:44:24
 * @LastEditors  : sphc
 * @LastEditTime : 2023-11-07 11:12:18
 * @FilePath     : /include/QueueException.hpp
 * @Description  : 队列异常类
 */
class QueueException : public std::exception {
public:
    QueueException(const std::string &message) :
        __message{message} {
    }

    const char *what() const noexcept override {
        return __message.c_str();
    }

private:
    std::string __message;
};
} // namespace dsa

#endif