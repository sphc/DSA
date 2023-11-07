#ifndef __ABSTRACT_LIST__H
#define __ABSTRACT_LIST__H

#include "List.hpp"
#include <sstream>
#include <stdexcept>

namespace dsa {

template <typename ElementType>
/*
 * @Author       : sphc
 * @Date         : 2023-10-19 13:54:32
 * @LastEditors  : sphc
 * @LastEditTime : 2023-10-22 21:38:05
 * @FilePath     : /include/AbstractList.hpp
 * @Description  : List 的抽象基类
 */
class AbstractList : public List<ElementType> {
public:
    using size_type = typename List<ElementType>::size_type;

protected:
    enum class _Operation;
    template <_Operation Operation>
    static void _checkIndex(size_type index, size_type size);

private:
    using _OperationName = std::string;
    template <_Operation operation>
    static _OperationName __getOperationName();
    /**
     * @description: 是否是需要传入索引参数的操作
     * @return      {bool} 需要传入索引参数返回 true，否则返回 false
     */
    template <_Operation Operation>
    static constexpr bool __isOperationWithIndex();
    template <_Operation Operation>
    static bool __isValidIndex(size_type index, size_type size);
    static void __throwOutOfRangeException(const std::string &operation, size_type operatePos, size_type size);
};

template <typename ElementType>
enum class AbstractList<ElementType>::_Operation {
    CLEAR,
    SIZE,
    IS_EMPTY,
    CONTAINS,
    ADD,
    ADD_BY_INDEX,
    GET,
    SET,
    REMOVE,
    INDEX_OF,
    TO_STRING
};

template <typename ElementType>
template <typename AbstractList<ElementType>::_Operation operation>
typename AbstractList<ElementType>::_OperationName AbstractList<ElementType>::__getOperationName() {
    if constexpr (operation == _Operation::CLEAR) {
        return "clear";
    } else if constexpr (operation == _Operation::SIZE) {
        return "size";
    } else if constexpr (operation == _Operation::IS_EMPTY) {
        return "isEmpty";
    } else if constexpr (operation == _Operation::CONTAINS) {
        return "contains";
    } else if constexpr (operation == _Operation::ADD) {
        return "add";
    } else if constexpr (operation == _Operation::ADD_BY_INDEX) {
        return "add";
    } else if constexpr (operation == _Operation::GET) {
        return "get";
    } else if constexpr (operation == _Operation::SET) {
        return "set";
    } else if constexpr (operation == _Operation::REMOVE) {
        return "remove";
    } else if constexpr (operation == _Operation::INDEX_OF) {
        return "indexOf";
    } else if constexpr (operation == _Operation::TO_STRING) {
        return "toString";
    } else {
        return "unknow";
    }
}

template <typename ElementType>
template <typename AbstractList<ElementType>::_Operation Operation>
constexpr bool AbstractList<ElementType>::__isOperationWithIndex() {
    return Operation == _Operation::ADD_BY_INDEX || Operation == _Operation::GET || Operation == _Operation::SET || Operation == _Operation::REMOVE;
}

template <typename ElementType>
template <typename AbstractList<ElementType>::_Operation Operation>
bool AbstractList<ElementType>::__isValidIndex(size_type index, size_type size) {
    if constexpr (!__isOperationWithIndex<Operation>()) {
        std::ostringstream sstream;
        sstream << "operation: " << __getOperationName<Operation>() << " [no index parameter need to be passed to the operation].";
        throw std::invalid_argument(sstream.str());
    }
    if constexpr (Operation == _Operation::ADD_BY_INDEX) {
        return index <= size;
    } else {
        return index < size;
    }
}

template <typename ElementType>
void AbstractList<ElementType>::__throwOutOfRangeException(const std::string &operation, size_type operatePos, size_type size) {
    std::ostringstream sstream{};
    sstream << "operation: " << operation << " [size of ArrayList: " << size << ", try to operate at pos: " << operatePos << "].";
    throw std::out_of_range(sstream.str());
}

template <typename ElementType>
template <typename AbstractList<ElementType>::_Operation Operation>
void AbstractList<ElementType>::_checkIndex(size_type index, size_type size) {
    if (!__isValidIndex<Operation>(index, size)) {
        __throwOutOfRangeException(__getOperationName<Operation>(), index, size);
    }
}

} // namespace dsa

#endif