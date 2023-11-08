#ifndef __HEAD_OPERATION_H__
#define __HEAD_OPERATION_H__

#include <cassert>
#include <vector>

/*
 * @Author       : sphc
 * @Date         : 2023-11-07 12:06:11
 * @LastEditors  : sphc
 * @LastEditTime : 2023-11-08 22:07:04
 * @FilePath     : /include/heap_operation.hpp
 * @Description  :
 */
namespace dsa {

void __checkHeapOperationParam(std::size_t heapSize, std::size_t root, std::size_t bottom);

namespace recursion {

template <typename ElementType>
void reshapeDown(std::vector<ElementType> &elements, decltype(elements.size()) root, decltype(elements.size()) bottom) {
    __checkHeapOperationParam(elements.size(), root, bottom);

    decltype(elements.size()) leftChild = root * 2 + 1;
    if (bottom < leftChild) {
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
        std::swap(elements[root], elements[maxChild]);
        reshapeDown(elements, maxChild, bottom);
    }
}

template <typename ElementType>
void reshapeUp(std::vector<ElementType> &elements, decltype(elements.size()) root, decltype(elements.size()) bottom) {
    __checkHeapOperationParam(elements.size(), root, bottom);

    if (bottom == root) {
        return;
    }
    decltype(elements.size()) parent = (bottom - 1) / 2;
    if (elements[parent] < elements[bottom]) {
        std::swap(elements[parent], elements[bottom]);
        reshapeUp(elements, root, parent);
    }
}

} // namespace recursion

inline namespace iteration {

template <typename ElementType>
void reshapeDown(std::vector<ElementType> &elements, decltype(elements.size()) root, decltype(elements.size()) bottom) {
    __checkHeapOperationParam(elements.size(), root, bottom);

    while (true) {
        decltype(elements.size()) leftChild = root * 2 + 1;
        if (bottom < leftChild) {
            break;
        }
        decltype(elements.size()) rightChild = leftChild + 1;
        decltype(elements.size()) maxChild;
        if (bottom < rightChild) {
            maxChild = leftChild;
        } else {
            maxChild = elements[leftChild] < elements[rightChild] ? rightChild : leftChild;
        }

        if (elements[root] < elements[maxChild]) {
            std::swap(elements[root], elements[maxChild]);
            root = maxChild;
        } else {
            break;
        }
    }
}

template <typename ElementType>
void reshapeUp(std::vector<ElementType> &elements, decltype(elements.size()) root, decltype(elements.size()) bottom) {
    __checkHeapOperationParam(elements.size(), root, bottom);

    while (bottom != root) {
        decltype(elements.size()) parent = (bottom - 1) / 2;
        if (elements[parent] < elements[bottom]) {
            std::swap(elements[parent], elements[bottom]);
            bottom = parent;
        } else {
            break;
        }
    }
}

} // namespace iteration

} // namespace dsa

#endif