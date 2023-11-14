#include "sort.hpp"
#include <cassert>
#include <iostream>
#include <vector>

template <typename RandomAccessIterator>
bool isSorted(RandomAccessIterator begin, RandomAccessIterator end) {
    while (begin != end && begin + 1 != end) {
        if (*begin > *(begin + 1)) {
            return false;
        }
        ++begin;
    }
    return true;
}

template <typename Container, typename SortFunction>
void testSort(Container &container, SortFunction sortFunc) {
    assert(!isSorted(std::begin(container), std::end(container)));
    sortFunc(std::begin(container), std::end(container));
    // std::for_each(std::begin(container), std::end(container), [](const auto &e) {
    //     std::cout << e << " ";
    // });
    assert(isSorted(std::begin(container), std::end(container)));
}

int main() {
    {
        std::vector<int> v{9, 8, 7, 6, 5, 10, 21, 22, 15, 14};
        assert(!isSorted(std::begin(v), std::end(v)));
        dsa::heapSort(v);
        assert(isSorted(std::begin(v), std::end(v)));
        v.clear();
        dsa::heapSort(v);
        v.push_back(3);
        dsa::heapSort(v);
    }
    {
        std::vector<int> v{9, 8, 7, 6, 5, 10, 21, 22, 15, 14};
        assert(!isSorted(std::begin(v), std::end(v)));
        dsa::bubbleSort(std::begin(v), std::end(v));
        assert(isSorted(std::begin(v), std::end(v)));
        v.clear();
        dsa::bubbleSort(std::begin(v), std::end(v));
        v.push_back(3);
        dsa::bubbleSort(std::begin(v), std::end(v));
    }
    {
        std::vector<int> v{9, 8, 7, 6, 5, 10, 21, 22, 15, 14};
        assert(!isSorted(std::begin(v), std::end(v)));
        dsa::selectionSort(std::begin(v), std::end(v));
        assert(isSorted(std::begin(v), std::end(v)));
        v.clear();
        dsa::selectionSort(std::begin(v), std::end(v));
        v.push_back(3);
        dsa::selectionSort(std::begin(v), std::end(v));
    }
    {
        std::vector<int> v{9, 8, 7, 6, 5, 10, 21, 22, 15, 14};
        assert(!isSorted(std::begin(v), std::end(v)));
        dsa::insertionSort(std::begin(v), std::end(v));
        assert(isSorted(std::begin(v), std::end(v)));
        v.clear();
        dsa::insertionSort(std::begin(v), std::end(v));
        v.push_back(3);
        dsa::insertionSort(std::begin(v), std::end(v));
    }
}