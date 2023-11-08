/*
 * @Author       : sphc
 * @Date         : 2023-11-07 11:20:35
 * @LastEditors  : sphc
 * @LastEditTime : 2023-11-08 21:04:29
 * @FilePath     : /src/testPQType.cpp
 * @Description  :
 */
#include "PQType.hpp"
#include <iostream>

int main() {
    dsa::PQType<int> queue{};
    assert(queue.isEmpty());

    queue.enqueue(1);
    queue.enqueue(3);
    queue.enqueue(5);
    queue.enqueue(7);
    queue.enqueue(9);
    queue.enqueue(20);
    queue.enqueue(18);
    queue.enqueue(16);
    queue.enqueue(14);
    queue.enqueue(12);

    dsa::PQType<int> queue2{queue};
    dsa::PQType<int> queue3;
    queue3 = queue;

    assert(queue.dequeue() == 20);
    assert(queue.dequeue() == 18);
    assert(queue.dequeue() == 16);
    queue.enqueue(2);
    queue.enqueue(27);
    queue.enqueue(25);
    assert(queue.dequeue() == 27);
    assert(queue.dequeue() == 25);
    assert(queue.dequeue() == 14);
    while (!queue.isEmpty()) {
        queue.dequeue();
    }
    assert(queue.isEmpty());

    assert(queue2.dequeue() == 20);
    assert(queue2.dequeue() == 18);
    assert(queue2.dequeue() == 16);
    queue2.enqueue(2);
    queue2.enqueue(27);
    queue2.enqueue(25);
    assert(queue2.dequeue() == 27);
    assert(queue2.dequeue() == 25);
    assert(queue2.dequeue() == 14);
    while (!queue2.isEmpty()) {
        queue2.dequeue();
    }
    assert(queue2.isEmpty());

    assert(queue3.dequeue() == 20);
    assert(queue3.dequeue() == 18);
    assert(queue3.dequeue() == 16);
    queue3.enqueue(2);
    queue3.enqueue(27);
    queue3.enqueue(25);
    assert(queue3.dequeue() == 27);
    assert(queue3.dequeue() == 25);
    assert(queue3.dequeue() == 14);
    while (!queue3.isEmpty()) {
        queue3.dequeue();
    }
    assert(queue3.isEmpty());

    return 0;
}