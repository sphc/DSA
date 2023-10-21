#ifndef __ARRAY_LIST_H__
#define __ARRAY_LIST_H__

#include "AbstractList.hpp"
#include <algorithm>
#include <functional>
#include <iterator>
#include <limits>
#include <map>
#include <memory>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>

#ifdef DEBUG
#include <iostream>
#endif

namespace dsa {

/**
 * @author: sphc
 * @date: 2023-10-18 15:23:00
 */
template <typename ElementType>
class ArrayList final : public AbstractList<ElementType> {
public:
    using size_type = typename std::allocator<ElementType>::size_type;
    // TODO: check npos
    inline static constexpr size_type npos{std::numeric_limits<size_type>::max()};

    ArrayList(size_type capacity = __DEFAULT_CAPACITY);
    ArrayList(const ElementType &) = delete;
    ArrayList(ElementType &&) = delete;
    ArrayList &operator=(const ElementType &) = delete;
    ArrayList &operator=(ElementType &&) = delete;
    ~ArrayList();

    /**
     * @description: 清除集合中的所有元素
     * @return      {void}
     */
    void clear() override;

    /**
     * @description: 获取集合中元素数量
     * @return      {size_type} 集合中元素的数量
     */
    [[nodiscard]] size_type size() const override;

    /**
     * @description: 检查集合是否有元素
     * @return      {bool} 无元素返回 true，有元素返回 false
     */
    [[nodiscard]] bool isEmpty() const override;

    /**
     * @description: 查找元素是否出现在集合中
     * @param       {const ElementType &} element 需要查找的元素
     * @return      {bool} 存在返回 true，不存在返回 false
     */
    [[nodiscard]] bool contains(const ElementType &element) const override;

    /**
     * @description: 往集合末尾插入元素
     * @param       {const ElementType &} element 需要插入的元素
     * @return      {void}
     */
    void add(const ElementType &element) override;

    /**
     * @description: 在集合指定位置处插入元素
     * @param       {size_type} index 指定位置索引，取值范围 [0, size()]
     * @param       {ElementType} &element 要插入的元素
     * @return      {void}
     */
    void add(size_type index, const ElementType &element) override;

    /**
     * @description: 获取集合指定位置处的元素
     * @param       {size_type} index 指定位置索引，取值范围 [0, size() - 1]
     * @return      {const ElementType &} 指定位置处的元素
     */
    [[nodiscard]] const ElementType &get(size_type index) const override;

    /**
     * @description: 将集合指定位置处的元素设置为指定元素
     * @param       {size_type} index 指定位置索引，取值范围 [0, size() - 1]
     * @param       {const ElementType &} element 要设置的元素
     * @return      {ElementType} 设置之前的元素
     */
    ElementType set(size_type index, const ElementType &element) override;

    /**
     * @description: 删除集合指定位置处的元素
     * @param       {size_type} index 指定位置索引，取值范围 [0, size() - 1]
     * @return      {ElementType} 被删除的元素
     */
    ElementType remove(size_type index) override;

    /**
     * @description: 在集合中获取指定元素的位置索引
     * @param       {ElementType} &element 指定元素
     * @return      {size_type} 指定元素所在的位置索引，未找到则返回 ArrayList<ElementType>::npos
     */
    [[nodiscard]] size_type indexOf(const ElementType &element) const override;

    /**
     * @description: 将集合转换为字符串表示，可用于打印等
     * @param       {function<void(ElementType &)>} toString 将集合中元素转换为字符串的方法
     * @return      {string} 集合的字符串表示
     */
    [[nodiscard]] std::string toString(std::function<std::string(const ElementType &)> toString) const override;

    // 新增方法
    /**
     * @description: 获取集合能够容纳的元素数量
     * @return      {size_type} 集合容量
     */
    [[nodiscard]] size_type capacity() const;

private:
    ElementType *__data;
    size_type __size;
    size_type __capacity;

    inline static std::allocator<ElementType> __allocator{};
    inline static constexpr size_type __DEFAULT_CAPACITY{10};

    using __ListOperation = typename AbstractList<ElementType>::_ListOperation;
    /**
     * @description: 是否是需要传入索引参数的操作
     * @return      {bool} 需要传入索引参数返回 true，否则返回 false
     */
    template <__ListOperation Operation>
    static constexpr bool __isOperationWithIndex();
    template <__ListOperation Operation>
    static bool __isValidIndex(size_type index, size_type size);
    static void __throwOutOfRangeException(const std::string &operation, size_type operatePos, size_type size);
    template <__ListOperation Operation>
    static void __checkIndex(size_type index, size_type size);

    void __reallocToFitNewCapacity(size_type newCapacity);
    void __ensureCapacity(size_type needCapacity);
    void __shrinkIfNecessary();

    class iterator;
    iterator begin();
    iterator end();
    class const_iterator;
    const_iterator cbegin() const;
    const_iterator cend() const;

    class reverse_iterator;
    reverse_iterator rbegin();
    reverse_iterator rend();
};

template <typename ElementType>
ArrayList<ElementType>::ArrayList(size_type capacity) :
    __data{__allocator.allocate(capacity)}, __size{0}, __capacity{capacity} {
}

template <typename ElementType>
ArrayList<ElementType>::~ArrayList() {
    clear();
    __allocator.deallocate(__data, __capacity);
}

template <typename ElementType>
void ArrayList<ElementType>::clear() {
    while (__size--) {
        __allocator.destroy(__data + __size);
    }
}

template <typename ElementType>
[[nodiscard]] typename ArrayList<ElementType>::size_type ArrayList<ElementType>::size() const {
    return __size;
}

template <typename ElementType>
[[nodiscard]] typename ArrayList<ElementType>::size_type ArrayList<ElementType>::capacity() const {
    return __capacity;
}

template <typename ElementType>
[[nodiscard]] bool ArrayList<ElementType>::isEmpty() const {
    return size() == 0;
}

template <typename ElementType>
[[nodiscard]] bool ArrayList<ElementType>::contains(const ElementType &element) const {
    return std::find(cbegin(), cend(), element) != cend();
}

template <typename ElementType>
void ArrayList<ElementType>::add(const ElementType &element) {
    add(__size, element);
}

template <typename ElementType>
[[nodiscard]] const ElementType &ArrayList<ElementType>::get(size_type index) const {
    __checkIndex<__ListOperation::GET>(index, size());
    return __data[index];
}

template <typename ElementType>
ElementType ArrayList<ElementType>::set(size_type index, const ElementType &element) {
    __checkIndex<__ListOperation::SET>(index, size());
    ElementType old{std::move(__data[index])};
    __data[index] = element;
    return old;
}

template <typename ElementType>
void ArrayList<ElementType>::add(size_type index, const ElementType &element) {
    __checkIndex<__ListOperation::ADD_BY_INDEX>(index, size());
    __ensureCapacity(size() + 1);
    // 这种情况无需移动元素，直接在尾部构造
    if (index == size()) {
        __allocator.construct(__data + __size++, element);
        return;
    }
    __allocator.construct(__data + __size, __data[__size - 1]);
    // auto it {std::move(rbegin() + 1, rend() - index, rbegin())};
    auto it{std::move_backward(begin() + index, end() - 1, end())};
    *it = element;
    ++__size;
}

template <typename ElementType>
ElementType ArrayList<ElementType>::remove(size_type index) {
    __checkIndex<__ListOperation::REMOVE>(index, size());
    ElementType old{std::move(__data[index])};
    std::move(begin() + index + 1, end(), begin() + index);
    __allocator.destroy(__data + __size--);
    __shrinkIfNecessary();
    return old;
}

template <typename ElementType>
[[nodiscard]] typename ArrayList<ElementType>::size_type ArrayList<ElementType>::indexOf(const ElementType &element) const {
    auto it{std::find(cbegin(), cend(), element)};
    return it != cend() ? it - cbegin() : npos;
}

template <typename ElementType>
[[nodiscard]] std::string ArrayList<ElementType>::toString(std::function<std::string(const ElementType &)> toString) const {
    std::ostringstream sstream{};
    sstream << "[";
    std::for_each(cbegin(), cend(), [&sstream, &toString](const auto &e) { sstream << toString(e) << ", "; });
    std::string result{sstream.str()};
    if (result.size() > 1) {
        result.pop_back();
        result.pop_back();
    }
    result += "]";
    return result;
}

template <typename ElementType>
template <typename ArrayList<ElementType>::__ListOperation Operation>
constexpr bool ArrayList<ElementType>::__isOperationWithIndex() {
    return Operation == __ListOperation::ADD_BY_INDEX || Operation == __ListOperation::GET || Operation == __ListOperation::SET || Operation == __ListOperation::REMOVE;
}

template <typename ElementType>
template <typename ArrayList<ElementType>::__ListOperation Operation>
bool ArrayList<ElementType>::__isValidIndex(size_type index, size_type size) {
    if constexpr (!__isOperationWithIndex<Operation>()) {
        std::ostringstream sstream;
        sstream << "operation: " << AbstractList<ElementType>::template _getOperationName<Operation>() << " [no index parameter need to be passed to the operation].";
        throw std::invalid_argument(sstream.str());
    }
    if constexpr (Operation == __ListOperation::ADD_BY_INDEX) {
        return index <= size;
    } else {
        return index < size;
    }
}

template <typename ElementType>
void ArrayList<ElementType>::__throwOutOfRangeException(const std::string &operation, size_type operatePos, size_type size) {
    std::ostringstream sstream{};
    sstream << "operation: " << operation << " [size of ArrayList: " << size << ", try to operate at pos: " << operatePos << "].";
    throw std::out_of_range(sstream.str());
}

template <typename ElementType>
template <typename ArrayList<ElementType>::__ListOperation Operation>
void ArrayList<ElementType>::__checkIndex(size_type index, size_type size) {
    if (!__isValidIndex<Operation>(index, size)) {
        __throwOutOfRangeException(AbstractList<ElementType>::template _getOperationName<Operation>(), index, size);
    }
}

template <typename ElementType>
void ArrayList<ElementType>::__reallocToFitNewCapacity(size_type newCapacity) {
#ifdef DEBUG
    std::cout << "__reallocToFitNewCapacity() [newCapacity = " << newCapacity << ", __capacity = " << __capacity << ", __size = " << __size << "]." << std::endl;
    assert(__size <= newCapacity);
#endif
    auto newData{__allocator.allocate(newCapacity)};
    for (size_type i{0}; i < size(); ++i) {
        __allocator.construct(newData + i, std::move(__data[i]));
        __allocator.destroy(__data + i);
    }
    __allocator.deallocate(__data, __capacity);
    __data = newData;
    __capacity = newCapacity;
}

template <typename ElementType>
void ArrayList<ElementType>::__ensureCapacity(size_type needCapacity) {
    if (needCapacity > __capacity) {
        __reallocToFitNewCapacity(__capacity << 1);
    }
}

template <typename ElementType>
void ArrayList<ElementType>::__shrinkIfNecessary() {
    if (__size < __capacity >> 2) {
        __reallocToFitNewCapacity(__capacity >> 2);
    }
}

template <typename ElementType>
class ArrayList<ElementType>::iterator {
public:
    // iterator traits
    using difference_type = typename std::allocator<ElementType>::difference_type;
    using value_type = ElementType;
    using pointer = value_type *;
    using reference = value_type &;
    using iterator_category = std::bidirectional_iterator_tag;

    iterator(pointer pos) :
        __cur{pos} {
    }
    iterator(const iterator &rhs) :
        __cur{rhs.__cur} {
    }
    iterator(iterator &&rhs) :
        __cur{rhs.__cur} {
    }
    iterator &operator=(const iterator &rhs) {
        __cur = rhs.__cur;
    }
    iterator &operator=(iterator &&rhs) {
        __cur = rhs.__cur;
    }

    iterator operator+(size_type step) {
        return iterator{__cur + step};
    }

    iterator &operator+=(size_type step) {
        __cur += step;
        return *this;
    }

    iterator operator-(size_type step) {
        return iterator{__cur - step};
    }

    iterator &operator-=(size_type step) {
        __cur -= step;
        return *this;
    }

    difference_type operator-(iterator rhs) {
        return __cur - rhs.__cur;
    }

    iterator &operator++() {
        ++__cur;
        return *this;
    }

    iterator &operator--() {
        --__cur;
        return *this;
    }

    iterator operator++(int _) {
        pointer old = __cur;
        ++__cur;
        return iterator{old};
    }

    iterator operator--(int _) {
        pointer old = __cur;
        --__cur;
        return iterator{old};
    }

    reference operator*() {
        return *__cur;
    }

    pointer operator->() {
        return __cur;
    }

    bool operator==(iterator rhs) {
        return __cur == rhs.__cur;
    }

    bool operator!=(iterator rhs) {
        return !(*this == rhs);
    }

private:
    pointer __cur;
};

template <typename ElementType>
class ArrayList<ElementType>::const_iterator {
public:
    // iterator traits
    using difference_type = typename std::allocator<ElementType>::difference_type;
    using value_type = ElementType;
    using pointer = const value_type *;
    using reference = const value_type &;
    using iterator_category = std::bidirectional_iterator_tag;

    const_iterator(pointer pos) :
        __cur{pos} {
    }
    const_iterator(const const_iterator &rhs) :
        __cur{rhs.__cur} {
    }
    const_iterator(const_iterator &&rhs) :
        __cur{rhs.__cur} {
    }
    const_iterator &operator=(const const_iterator &rhs) {
        __cur = rhs.__cur;
    }
    const_iterator &operator=(const_iterator &&rhs) {
        __cur = rhs.__cur;
    }

    const_iterator operator+(size_type step) {
        return iterator{__cur + step};
    }

    const_iterator &operator+=(size_type step) {
        __cur += step;
        return *this;
    }

    const_iterator operator-(size_type step) {
        return iterator{__cur - step};
    }

    const_iterator &operator-=(size_type step) {
        __cur -= step;
        return *this;
    }

    difference_type operator-(const_iterator rhs) {
        return __cur - rhs.__cur;
    }

    const_iterator &operator++() {
        ++__cur;
        return *this;
    }

    const_iterator &operator--() {
        --__cur;
        return *this;
    }

    const_iterator operator++(int _) {
        pointer old = __cur;
        ++__cur;
        return iterator{old};
    }

    const_iterator operator--(int _) {
        pointer old = __cur;
        --__cur;
        return iterator{old};
    }

    reference operator*() {
        return *__cur;
    }

    pointer operator->() {
        return __cur;
    }

    bool operator==(const_iterator rhs) {
        return __cur == rhs.__cur;
    }

    bool operator!=(const_iterator rhs) {
        return !(*this == rhs);
    }

private:
    pointer __cur;
};

template <typename ElementType>
class ArrayList<ElementType>::reverse_iterator {
public:
    // iterator traits
    using difference_type = typename std::allocator<ElementType>::difference_type;
    using value_type = ElementType;
    using pointer = ElementType *;
    using reference = ElementType &;
    using iterator_category = std::bidirectional_iterator_tag;

    reverse_iterator(pointer pos) :
        __cur{pos} {
    }
    reverse_iterator(const reverse_iterator &rhs) :
        __cur{rhs.__cur} {
    }
    reverse_iterator(reverse_iterator &&rhs) :
        __cur{rhs.__cur} {
    }
    reverse_iterator &operator=(const reverse_iterator &rhs) {
        __cur = rhs.__cur;
    }
    reverse_iterator &operator=(reverse_iterator &&rhs) {
        __cur = rhs.cur;
    }

    reverse_iterator operator+(size_type step) {
        return reverse_iterator{__cur - step};
    }

    reverse_iterator &operator+=(size_type step) {
        __cur -= step;
        return *this;
    }

    reverse_iterator operator-(size_type step) {
        return reverse_iterator{__cur + step};
    }

    reverse_iterator &operator-=(size_type step) {
        __cur += step;
        return *this;
    }

    difference_type operator-(reverse_iterator rhs) {
        return rhs.__cur - __cur;
    }

    reverse_iterator &operator++() {
        --__cur;
        return *this;
    }

    reverse_iterator &operator--() {
        ++__cur;
        return *this;
    }

    reverse_iterator operator++(int _) {
        pointer old = __cur;
        --__cur;
        return reverse_iterator{old};
    }

    reverse_iterator operator--(int _) {
        pointer old = __cur;
        ++__cur;
        return reverse_iterator{old};
    }

    reference operator*() {
        return *(__cur - 1);
    }

    pointer operator->() {
        return __cur - 1;
    }

    bool operator==(reverse_iterator rhs) {
        return __cur == rhs.__cur;
    }

    bool operator!=(reverse_iterator rhs) {
        return !(*this == rhs);
    }

private:
    pointer __cur;
};

template <typename ElementType>
typename ArrayList<ElementType>::iterator ArrayList<ElementType>::begin() {
    return iterator{__data};
}

template <typename ElementType>
typename ArrayList<ElementType>::iterator ArrayList<ElementType>::end() {
    return iterator{__data + __size};
}

template <typename ElementType>
typename ArrayList<ElementType>::const_iterator ArrayList<ElementType>::cbegin() const {
    return const_iterator{__data};
}

template <typename ElementType>
typename ArrayList<ElementType>::const_iterator ArrayList<ElementType>::cend() const {
    return const_iterator{__data + __size};
}

template <typename ElementType>
typename ArrayList<ElementType>::reverse_iterator ArrayList<ElementType>::rbegin() {
    return reverse_iterator{__data + __size};
}

template <typename ElementType>
typename ArrayList<ElementType>::reverse_iterator ArrayList<ElementType>::rend() {
    return reverse_iterator{__data};
}

} // namespace dsa

#endif