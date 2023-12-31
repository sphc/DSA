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
#include <string>

#ifdef DEBUG
#include <cassert>
#include <iostream>
#endif

namespace dsa {

/*
 * @Author       : sphc
 * @Date         : 2023-10-18 13:32:32
 * @LastEditors  : sphc
 * @LastEditTime : 2023-10-21 13:45:49
 * @FilePath     : /include/ArrayList.hpp
 * @Description  : List 集合数组实现
 */
template <typename ElementType>
class ArrayList final : public AbstractList<ElementType> {
public:
    using size_type = typename AbstractList<ElementType>::size_type;

    ArrayList(size_type capacity = __DEFAULT_CAPACITY);
    ArrayList(const ElementType &) = delete;
    ArrayList(ElementType &&) = delete;
    ArrayList &operator=(const ElementType &) = delete;
    ArrayList &operator=(ElementType &&) = delete;
    ~ArrayList() override;

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

    using Allocator = std::allocator<ElementType>;
    using AllocatorTraits = std::allocator_traits<Allocator>;
    inline static Allocator __allocator{};
    inline static constexpr size_type __DEFAULT_CAPACITY{10};

    using __ListOperation = typename AbstractList<ElementType>::_Operation;

    void __reallocToFitNewCapacity(size_type newCapacity);
    void __ensureCapacity(size_type needCapacity);
    void __shrinkIfNecessary();
    void __destroyAllElement();
    static size_type __initCapacity(size_type capacity);

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
    __data{AllocatorTraits::allocate(__allocator, __initCapacity(capacity))}, __size{0}, __capacity{__initCapacity(capacity)} {
}

template <typename ElementType>
ArrayList<ElementType>::~ArrayList() {
    __destroyAllElement();
    AllocatorTraits::deallocate(__allocator, __data, __capacity);
}

// checked
template <typename ElementType>
void ArrayList<ElementType>::clear() {
    __destroyAllElement();
    __size = 0;
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
    AbstractList<ElementType>::template _checkIndex<__ListOperation::GET>(index, size());
    return __data[index];
}

template <typename ElementType>
ElementType ArrayList<ElementType>::set(size_type index, const ElementType &element) {
    AbstractList<ElementType>::template _checkIndex<__ListOperation::SET>(index, size());
    ElementType old{std::move(__data[index])};
    __data[index] = element;
    return old;
}

template <typename ElementType>
void ArrayList<ElementType>::add(size_type index, const ElementType &element) {
    AbstractList<ElementType>::template _checkIndex<__ListOperation::ADD_BY_INDEX>(index, size());
    __ensureCapacity(size() + 1);
    // 这种情况无需移动元素，直接在尾部构造
    if (index == size()) {
        AllocatorTraits::construct(__allocator, __data + __size++, element);
        return;
    }
    AllocatorTraits::construct(__allocator, __data + __size, __data[__size - 1]);
    // auto it {std::move(rbegin() + 1, rend() - index, rbegin())};
    auto it{std::move_backward(begin() + index, end() - 1, end())};
    *it = element;
    ++__size;
}

template <typename ElementType>
ElementType ArrayList<ElementType>::remove(size_type index) {
    AbstractList<ElementType>::template _checkIndex<__ListOperation::REMOVE>(index, size());
    ElementType old{std::move(__data[index])};
    std::move(begin() + index + 1, end(), begin() + index);
    AllocatorTraits::destroy(__allocator, __data + __size--);
    __shrinkIfNecessary();
    return old;
}

template <typename ElementType>
[[nodiscard]] typename ArrayList<ElementType>::size_type ArrayList<ElementType>::indexOf(const ElementType &element) const {
    auto it{std::find(cbegin(), cend(), element)};
    return it != cend() ? it - cbegin() : AbstractList<ElementType>::npos;
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
void ArrayList<ElementType>::__reallocToFitNewCapacity(size_type newCapacity) {
#ifdef DEBUG
    std::cout << "__reallocToFitNewCapacity() [newCapacity = " << newCapacity << ", __capacity = " << __capacity << ", __size = " << __size << "]." << std::endl;
    assert(__size <= newCapacity);
#endif
    auto newData{AllocatorTraits::allocate(__allocator, newCapacity)};
    std::uninitialized_move(begin(), end(), newData);
    __destroyAllElement();
    AllocatorTraits::deallocate(__allocator, __data, __capacity);
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
void ArrayList<ElementType>::__destroyAllElement() {
    std::for_each(begin(), end(), [](auto &obj) {
        AllocatorTraits::destroy(__allocator, &obj);
    });
}

template <typename ElementType>
typename ArrayList<ElementType>::size_type ArrayList<ElementType>::__initCapacity(size_type capacity) {
    return capacity < __DEFAULT_CAPACITY ? __DEFAULT_CAPACITY : capacity;
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

    iterator operator+(size_type step) const {
        return iterator{__cur + step};
    }

    iterator &operator+=(size_type step) {
        __cur += step;
        return *this;
    }

    iterator operator-(size_type step) const {
        return iterator{__cur - step};
    }

    iterator &operator-=(size_type step) {
        __cur -= step;
        return *this;
    }

    difference_type operator-(iterator rhs) const {
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

    reference operator*() const {
        return *__cur;
    }

    pointer operator->() const {
        return __cur;
    }

    bool operator==(iterator rhs) const {
        return __cur == rhs.__cur;
    }

    bool operator!=(iterator rhs) const {
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

    const_iterator operator+(size_type step) const {
        return iterator{__cur + step};
    }

    const_iterator &operator+=(size_type step) {
        __cur += step;
        return *this;
    }

    const_iterator operator-(size_type step) const {
        return iterator{__cur - step};
    }

    const_iterator &operator-=(size_type step) {
        __cur -= step;
        return *this;
    }

    difference_type operator-(const_iterator rhs) const {
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

    reference operator*() const {
        return *__cur;
    }

    pointer operator->() const {
        return __cur;
    }

    bool operator==(const_iterator rhs) const {
        return __cur == rhs.__cur;
    }

    bool operator!=(const_iterator rhs) const {
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