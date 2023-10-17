#ifndef __FIB_H__
#define __FIB_H__

#include <unordered_map>

namespace dsa {
namespace recursion {
template <typename UnsignedInteger>
UnsignedInteger fib(UnsignedInteger n) {
    if (n <= 1) {
        return n;
    }
    return fib(n - 1) + fib(n - 2);
}

template <typename MapType, typename UnsignedInteger>
UnsignedInteger __fibCachedImpl(MapType &cache, UnsignedInteger n) {
    if (n <= 1) {
        return n;
    }
    UnsignedInteger frontOne{};
    UnsignedInteger frontTwo{};
    if (cache[n - 1] != 0) {
        frontOne = cache[n - 1];
    } else {
        frontOne = cache[n - 1] = __fibCachedImpl(cache, n - 1);
    }
    if (cache[n - 2] != 0) {
        frontTwo = cache[n - 2];
    } else {
        frontTwo = cache[n - 2] = __fibCachedImpl(cache, n - 2);
    }
    return frontOne + frontTwo;
}

template <typename UnsignedInteger>
UnsignedInteger fibCached(UnsignedInteger n) {
    std::unordered_map<UnsignedInteger, UnsignedInteger> cache{};
    return __fibCachedImpl(cache, n);
}
} // namespace recursion

namespace iteration {
template <typename UnsignedInteger>
UnsignedInteger fib(UnsignedInteger n) {
    if (n == 0) {
        return n;
    }
    UnsignedInteger front{0};
    UnsignedInteger current{1};
    while (--n) {
        current += front;
        front = current - front;
    }
    return current;
}
} // namespace iteration
} // namespace dsa

#endif