#include "TimeTool.h"
#include "fib.hpp"
#include <cassert>
#include <iostream>

namespace {
void checkCorrectness(std::function<unsigned(unsigned)> fibFunc) {
    assert(fibFunc(0U) == 0);
    assert(fibFunc(1U) == 1);
    assert(fibFunc(2U) == 1);
    assert(fibFunc(3U) == 2);
    assert(fibFunc(4U) == 3);
    assert(fibFunc(5U) == 5);
    assert(fibFunc(6U) == 8);
    assert(fibFunc(7U) == 13);
    assert(fibFunc(8U) == 21);
    assert(fibFunc(9U) == 34);
    assert(fibFunc(10U) == 55);
}
} // namespace

int main() {
    TimeTool timeTool{500000};
    unsigned testNum{20U};

    checkCorrectness(std::bind(dsa::recursion::fib<unsigned>, std::placeholders::_1));
    checkCorrectness(std::bind(dsa::recursion::fibCached<unsigned>, std::placeholders::_1));
    checkCorrectness(std::bind(dsa::iteration::fib<unsigned>, std::placeholders::_1));
    checkCorrectness(std::bind(dsa::fib<unsigned>, std::placeholders::_1));

    // assert(dsa::recursion::fib(50UL) == 12586269025UL);
    // assert(dsa::recursion::fibCached(50UL) == 12586269025UL);
    // assert(dsa::iteration::fib(50UL) == 12586269025UL);

    std::cout << "start to test time cost: " << std::endl;
    std::cout << "dsa::recursion::fib(" << testNum << "U) cost: " << timeTool.test(std::bind(dsa::recursion::fib<unsigned>, testNum)) << " s." << std::endl;
    std::cout << "dsa::recursion::fibCached(" << testNum << "U) cost: " << timeTool.test(std::bind(dsa::recursion::fibCached<unsigned>, testNum)) << " s." << std::endl;
    std::cout << "dsa::iteration::fib(" << testNum << "U) cost: " << timeTool.test(std::bind(dsa::iteration::fib<unsigned>, testNum)) << " s." << std::endl;
    std::cout << "dsa::fib(" << testNum << "U) cost: " << timeTool.test(std::bind(dsa::fib<unsigned>, testNum)) << " s." << std::endl;

    return 0;
}