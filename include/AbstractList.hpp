#ifndef __ABSTRACT_LIST__H
#define __ABSTRACT_LIST__H

#include "List.hpp"

namespace dsa {

template <typename ElementType>
/*
 * @Author       : sphc
 * @Date         : 2023-10-19 13:54:32
 * @LastEditors  : sphc
 * @LastEditTime : 2023-10-21 14:00:31
 * @FilePath     : /include/AbstractList.hpp
 * @Description  : List 的抽象基类
 */
class AbstractList : public List<ElementType> {
};

} // namespace dsa

#endif