/*
 * @Author       : sphc
 * @Date         : 2023-11-08 21:11:25
 * @LastEditors  : sphc
 * @LastEditTime : 2023-11-08 21:34:53
 * @FilePath     : /src/heap_operation.cpp
 * @Description  :
 */
#include "heap_operation.hpp"

namespace dsa {

void __checkHeapOperationParam(std::size_t heapSize, std::size_t root, std::size_t bottom) {
    assert(root < heapSize);
    assert(bottom < heapSize);
    assert(root <= bottom);
}

} // namespace dsa