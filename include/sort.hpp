/*
 * @Author       : sphc
 * @Date         : 2023-11-07 12:02:27
 * @LastEditors  : sphc
 * @LastEditTime : 2023-11-14 12:02:49
 * @FilePath     : /include/sort.hpp
 * @Description  :
 */
#ifndef __SORT_H__
#define __SORT_H__

#include "heap_operation.hpp"
#include <algorithm>
#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>

namespace dsa {

namespace __detail {

template <typename ElementType>
void __buildHeap(std::vector<ElementType> &elements) {
    decltype(elements.size()) end{elements.size() / 2};
    while (0 < end) {
        reshapeDown(elements, --end, elements.size() - 1);
    }
}

/**
 * @description: 一次冒泡，将最大的元素冒泡到序列的末端，若序列中的元素已经有序，则返回 false
 * @return      {bool} 存在元素交换则返回 true，否则返回 false
 */
template <typename RandomAccessIterator>
bool __bubbleUp(RandomAccessIterator begin, RandomAccessIterator end) {
    if (begin == end) {
        return false;
    }
    bool swapHappened{false};
    for (; begin + 1 != end; ++begin) {
        if (*begin > *(begin + 1)) {
            std::swap(*begin, *(begin + 1));
            swapHappened = true;
        }
    }
    return swapHappened;
}
/**
 * @description: 从序列中选出最大的元素，将他放置到序列的末尾
 * @return      {void}
 */
template <typename RandomAccessIterator>
void __selectMaxToEnd(RandomAccessIterator begin, RandomAccessIterator end) {
    if (begin == end) {
        return;
    }
    RandomAccessIterator max{begin++};
    while (begin != end) {
        if (*begin > *max) {
            max = begin;
        }
        ++begin;
    }
    if (max != --end) {
        std::swap(*max, *end);
    }
}

} // namespace __detail

/**
 * @description: 堆排序，要求 ElementType 能够支持关系运算和赋值运算
 * @return      {void}
 */
// TODO: 改为迭代器形式
template <typename ElementType>
void heapSort(std::vector<ElementType> &elements) {
    __detail::__buildHeap(elements);
    decltype(elements.size()) end{elements.size()};
    while (1 < end) {
        std::swap(elements[0], elements[--end]);
        reshapeDown(elements, 0, end - 1);
    }
}

/**
 * @description: 冒泡排序，要求 ElementType 支持关系运算和赋值运算
 * @return      {void}
 */
template <typename RandomAccessIterator>
void bubbleSort(RandomAccessIterator begin, RandomAccessIterator end) {
    while (end - begin > 1 && __detail::__bubbleUp(begin, end)) {
        --end;
    }
}

/**
 * @description: 选择排序，要求 ElementType 支持关系运算和赋值运算
 * @return      {void}
 */
template <typename RandomAccessIterator>
void selectionSort(RandomAccessIterator begin, RandomAccessIterator end) {
    while (end - begin > 1) {
        __detail::__selectMaxToEnd(begin, end--);
    }
}

template <typename RandomAccessIterator>
void insertionSort(RandomAccessIterator begin, RandomAccessIterator end) {
    if (begin == end) {
        return;
    }
    auto cur{begin + 1};
    while (cur != end) {
        auto tmp{cur - 1};
        std::remove_reference_t<decltype(*cur)> e{std::move(*cur)};
        while (tmp != begin && e < *tmp) {
            *(tmp + 1) = std::move(*tmp);
            --tmp;
        }
        if (tmp == begin && e < *tmp) {
            *(tmp + 1) = std::move(*tmp);
            *tmp = std::move(e);
        } else {
            *(tmp + 1) = std::move(e);
        }
        ++cur;
    }
}

} // namespace dsa

#endif