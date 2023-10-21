#ifndef __ABSTRACT_LIST__H
#define __ABSTRACT_LIST__H

#include "List.hpp"

namespace dsa {
template <typename ElementType>
class AbstractList : public List<ElementType> {
};
} // namespace dsa

#endif