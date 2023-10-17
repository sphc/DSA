#include "TimeTool.h"
#include "fib.hpp"
#include <cassert>
#include <iostream>

int main() {
    TimeTool timeTool{500000};
    unsigned testNum{20U};

    assert(dsa::recursion::fib(0U) == 0);
    assert(dsa::recursion::fib(1U) == 1);
    assert(dsa::recursion::fib(2U) == 1);
    assert(dsa::recursion::fib(3U) == 2);
    assert(dsa::recursion::fib(4U) == 3);
    assert(dsa::recursion::fib(5U) == 5);
    assert(dsa::recursion::fib(6U) == 8);
    assert(dsa::recursion::fib(7U) == 13);
    assert(dsa::recursion::fib(8U) == 21);
    assert(dsa::recursion::fib(9U) == 34);
    assert(dsa::recursion::fib(10U) == 55);
    // assert(dsa::recursion::fib(50UL) == 12586269025UL);

    assert(dsa::recursion::fibCached(0U) == 0);
    assert(dsa::recursion::fibCached(1U) == 1);
    assert(dsa::recursion::fibCached(2U) == 1);
    assert(dsa::recursion::fibCached(3U) == 2);
    assert(dsa::recursion::fibCached(4U) == 3);
    assert(dsa::recursion::fibCached(5U) == 5);
    assert(dsa::recursion::fibCached(6U) == 8);
    assert(dsa::recursion::fibCached(7U) == 13);
    assert(dsa::recursion::fibCached(8U) == 21);
    assert(dsa::recursion::fibCached(9U) == 34);
    assert(dsa::recursion::fibCached(10U) == 55);
    assert(dsa::recursion::fibCached(50UL) == 12586269025UL);

    assert(dsa::iteration::fib(0U) == 0);
    assert(dsa::iteration::fib(1U) == 1);
    assert(dsa::iteration::fib(2U) == 1);
    assert(dsa::iteration::fib(3U) == 2);
    assert(dsa::iteration::fib(4U) == 3);
    assert(dsa::iteration::fib(5U) == 5);
    assert(dsa::iteration::fib(6U) == 8);
    assert(dsa::iteration::fib(7U) == 13);
    assert(dsa::iteration::fib(8U) == 21);
    assert(dsa::iteration::fib(9U) == 34);
    assert(dsa::iteration::fib(10U) == 55);
    assert(dsa::iteration::fib(50UL) == 12586269025UL);

    std::cout << "start to test time cost: " << std::endl;
    std::cout << "dsa::recursion::fib(" << testNum << "U) cost: " << timeTool.test(std::bind(dsa::recursion::fib<unsigned>, testNum)) << " s." << std::endl;
    std::cout << "dsa::recursion::fibCached(" << testNum << "U) cost: " << timeTool.test(std::bind(dsa::recursion::fibCached<unsigned>, testNum)) << " s." << std::endl;
    std::cout << "dsa::iteration::fib(" << testNum << "U) cost: " << timeTool.test(std::bind(dsa::iteration::fib<unsigned>, testNum)) << " s." << std::endl;

    return 0;
}