#include "sort.hpp"
#include <cassert>
#include <iostream>
#include <vector>

template <typename ElementType>
bool isSorted(std::vector<ElementType> &elements) {
    auto begin{elements.cbegin()};
    auto end{elements.cend()};
    while (begin != end && begin + 1 != end) {
        if (*begin > *(begin + 1)) {
            return false;
        }
        ++begin;
    }
    return true;
}

int main() {
    std::vector<int> v{9, 8, 7, 6, 5, 10, 21, 22, 15, 14};
    assert(!isSorted(v));
    dsa::heapsort(v);
    assert(isSorted(v));
}