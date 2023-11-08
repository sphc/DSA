#ifndef __PQ_TYPE_H__
#define __PQ_TYPE_H__

#include "QueueException.hpp"
#include "heap_operation.hpp"
#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

namespace dsa {
/*
 * @Author       : sphc
 * @Date         : 2023-11-07 09:56:22
 * @LastEditors  : sphc
 * @LastEditTime : 2023-11-07 12:01:00
 * @FilePath     : /include/PQType.hpp
 * @Description  : 优先队列，要求 ElementType 支持关系运算和赋值
 */
template <typename ElementType>
class PQType {
public:
    using size_type = std::size_t;
    PQType() = default;
    PQType(const PQType &) = default;
    PQType &operator=(const PQType &) = default;

    /**
     * @description: 将队列置空
     * @return      {void}
     */
    void makeEmpty() noexcept;
    /**
     * @description: 检查队列是否为空
     * @return      {bool} 若为空返回 true，否则返回 false
     */
    [[nodiscard]] bool isEmpty() const noexcept;
    /**
     * @description: 元素入队
     * @param       {ElementType} e 要插入的元素
     * @return      {void}
     */
    void enqueue(const ElementType &e);
    /**
     * @description: 优先级最高的元素出队
     * @return      {ElementType} 队列中优先级最高的元素
     */
    ElementType dequeue();

private:
    using ElementContainer = std::vector<ElementType>;
    ElementContainer __elements;
};

/**
 * @description: 将队列置空
 * @return      {void}
 */
template <typename ElementType>
void PQType<ElementType>::makeEmpty() noexcept {
    __elements.clear();
}

/**
 * @description: 检查队列是否为空
 * @return      {bool} 若为空返回 true，否则返回 false
 */
template <typename ElementType>
[[nodiscard]] bool PQType<ElementType>::isEmpty() const noexcept {
    return __elements.empty();
}

/**
 * @description: 元素入队
 * @param       {ElementType} e 要插入的元素
 * @return      {void}
 */
template <typename ElementType>
void PQType<ElementType>::enqueue(const ElementType &e) {
    try {
        __elements.push_back(e);
    } catch (const std::bad_alloc &e) {
        throw QueueException("queue full!");
    }
    reshapeUp(__elements, 0, __elements.size() - 1);
}

/**
 * @description: 优先级最高的元素出队
 * @return      {ElementType} 队列中优先级最高的元素
 */
template <typename ElementType>
ElementType PQType<ElementType>::dequeue() {
    if (isEmpty()) {
        throw QueueException("queue empty!");
    }
    ElementType e{std::move(__elements.front())};
    __elements.front() = std::move(__elements.back());
    __elements.pop_back();
    if (!isEmpty()) {
        reshapeDown(__elements, 0, __elements.size() - 1);
    }
    return e;
}

} // namespace dsa

#endif