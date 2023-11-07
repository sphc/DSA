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
    return 0;
}