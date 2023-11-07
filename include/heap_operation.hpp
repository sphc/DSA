#ifndef __HEAD_OPERATION_H__
#define __HEAD_OPERATION_H__

#include "utility.hpp"
#include <cassert>
#include <vector>

/*
 * @Author       : sphc
 * @Date         : 2023-11-07 12:06:11
 * @LastEditors  : sphc
 * @LastEditTime : 2023-11-07 12:12:08
 * @FilePath     : /include/heap_operation.hpp
 * @Description  :
 */
namespace dsa {

template <typename ElementType>
void reshapeDown(std::vector<ElementType> &elements, decltype(elements.size()) root, decltype(elements.size()) bottom) {
    assert(root < elements.size());
    assert(bottom < elements.size());
    assert(root <= bottom);

    decltype(elements.size()) leftChild = root * 2 + 1;
    if (leftChild > bottom) {
        return;
    }
    decltype(elements.size()) rightChild = leftChild + 1;
    decltype(elements.size()) maxChild;
    if (bottom < rightChild) {
        maxChild = leftChild;
    } else {
        maxChild = elements[leftChild] < elements[rightChild] ? rightChild : leftChild;
    }
    if (elements[root] < elements[maxChild]) {
        swap(std::move(elements[root]), std::move(elements[maxChild]));
        reshapeDown(elements, maxChild, bottom);
    }
}

template <typename ElementType>
void reshapeUp(std::vector<ElementType> &elements, decltype(elements.size()) root, decltype(elements.size()) bottom) {
    assert(root < elements.size());
    assert(bottom < elements.size());
    assert(root <= bottom);

    if (bottom == root) {
        return;
    }
    decltype(elements.size()) parent = (bottom - 1) / 2;
    if (elements[parent] < elements[bottom]) {
        swap(std::move(elements[parent]), std::move(elements[bottom]));
        reshapeUp(elements, root, parent);
    }
}
} // namespace dsa

#endif