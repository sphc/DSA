/*
 * @Author       : sphc
 * @Date         : 2023-11-07 12:02:27
 * @LastEditors  : sphc
 * @LastEditTime : 2023-11-07 12:43:08
 * @FilePath     : /include/sort.hpp
 * @Description  :
 */
#ifndef __SORT_H__
#define __SORT_H__

#include "heap_operation.hpp"
#include "utility.hpp"
#include <utility>
#include <vector>

namespace dsa {

template <typename ElementType>
void buildHeap(std::vector<ElementType> &elements) {
    decltype(elements.size()) end{elements.size() / 2};
    while (0 < end) {
        reshapeDown(elements, --end, elements.size() - 1);
    }
}

/**
 * @description: 堆排序，要求 ElementType 能够进行关系运算和赋值
 * @return      {void}
 */
template <typename ElementType>
void heapsort(std::vector<ElementType> &elements) {
    buildHeap(elements);
    decltype(elements.size()) end{elements.size()};
    while (1 < end) {
        swap(std::move(elements[0]), std::move(elements[--end]));
        reshapeDown(elements, 0, end - 1);
    }
}

} // namespace dsa

#endif