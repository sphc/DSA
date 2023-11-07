#ifndef __UTILITY_H__
#define __UTILITY_H__
#include <utility>

namespace dsa {

template <typename ElementType>
void swap(ElementType &&lhs, ElementType &&rhs) {
    ElementType tmp{std::move(lhs)};
    lhs = std::move(rhs);
    rhs = std::move(tmp);
}

} // namespace dsa

#endif