#ifndef __ARRAY_LIST_H__
#define __ARRAY_LIST_H__

#include <algorithm>
#include <exception>
#include <functional>
#include <iterator>
#include <limits>
#include <memory>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>

namespace dsa {

/**
 * @author: sphc
 * @date: 2023-10-18 15:23:00
 */
template <typename ElementType>
class ArrayList final {
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
     * 清除集合中的所有元素
     */
    void clear();
    /**
     * 获取集合中元素数量
     * @return: 集合中元素的数量
     */
    [[nodiscard]] size_type size() const;
    /**
     * 获取集合能够容纳的元素数量
     * @return: 集合容量
     */
    [[nodiscard]] size_type capacity() const;
    /**
     * 检查集合是否有元素
     * @return: 无元素则返回 true
     */
    [[nodiscard]] bool isEmpty() const;
    /**
     * 查找元素是否出现在集合中
     * @param element: 需要查找的元素
     * @return: 存在返回 true，不存在返回 false
     */
    [[nodiscard]] bool contains(const ElementType &element) const;
    /**
     * 往集合末尾插入元素
     * @param element: 需要插入的元素
     */
    void add(const ElementType &element);
    /**
     * 获取集合指定位置处的元素
     * @param index: 指定位置索引，取值范围 [0, size() - 1]
     * @return: 指定位置处的元素
     */
    [[nodiscard]] const ElementType &get(size_type index) const;
    /**
     * 将集合指定位置处的元素设置为指定元素
     * @param index: 指定位置索引，取值范围 [0, size() - 1]
     * @param element: 要设置的元素
     * @return: 设置之前的元素
     */
    ElementType set(size_type index, const ElementType &element);
    /**
     * 在集合指定位置处插入元素
     * @param index: 指定位置索引，取值范围 [0, size()]
     * @element: 要插入的元素
     */
    void add(size_type index, const ElementType &element);
    /**
     * 删除集合指定位置处的元素
     * @param index: 指定位置索引，取值范围 [0, size() - 1]
     * @return: 被删除的元素
     */
    ElementType remove(size_type index);
    /**
     * 在集合中获取指定元素的位置索引
     * @param element: 指定元素
     * @return: 指定元素所在的位置索引，未找到则返回 ArrayList<ElementType>::npos
     */
    [[nodiscard]] size_type indexOf(const ElementType &element) const;
    /**
     * 将集合转换为字符串表示，可用于打印等
     * @param toString: 将集合中元素转换为字符串的方法
     * @return: 集合的字符串表示
     */
    [[nodiscard]] std::string toString(std::function<void(const ElementType &)> toString) const;

private:
    ElementType *__data;
    size_type __size;
    size_type __capacity;

    inline static std::allocator<ElementType> __allocator{};
    inline static constexpr size_type __DEFAULT_CAPACITY{10};

    void checkIndex(size_type index);
    void ensureCapacity(size_type needCapacity);

    class iterator;
    iterator begin();
    iterator end();

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
    return std::find(begin(), end(), element) != end();
}

template <typename ElementType>
void ArrayList<ElementType>::add(const ElementType &element) {
    add(__size, element);
}

template <typename ElementType>
[[nodiscard]] const ElementType &ArrayList<ElementType>::get(size_type index) const {
    checkIndex(index);
    return __data[index];
}

template <typename ElementType>
ElementType ArrayList<ElementType>::set(size_type index, const ElementType &element) {
    checkIndex(index);
    ElementType old{std::move(__data[index])};
    __data[index] = element;
    return old;
}

template <typename ElementType>
void ArrayList<ElementType>::add(size_type index, const ElementType &element) {
    if (index > size()) {
        throw std::out_of_range("");
    }
    ensureCapacity(size() + 1);
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
    checkIndex(index);
    ElementType old{std::move(__data[index])};
    std::move(begin() + index + 1, end(), begin() + index);
    __allocator.destroy(__data + __size--);
    return old;
}

template <typename ElementType>
[[nodiscard]] typename ArrayList<ElementType>::size_type ArrayList<ElementType>::indexOf(const ElementType &element) const {
    auto it{std::find(begin(), end(), element)};
    return it != end() ? it - begin() : npos;
}

template <typename ElementType>
[[nodiscard]] std::string ArrayList<ElementType>::toString(std::function<void(const ElementType &)> toString) const {
    std::ostringstream sstream{};
    sstream << "[";
    std::for_each(begin(), end(), [&sstream, &toString](const auto &e) { sstream << toString(e) << ", "; });
    std::string result{std::move(sstream.str())};
    if (result.size() > 1) {
        result.pop_back();
        result.pop_back();
    }
    result += "]";
    return result;
}

template <typename ElementType>
void ArrayList<ElementType>::checkIndex(size_type index) {
    if (index >= size()) {
        std::ostringstream sstream{};
        sstream << "size of ArrayList: " << size() << ", current access pos: " << index << ".";
        throw std::out_of_range(sstream.str());
    }
}

template <typename ElementType>
void ArrayList<ElementType>::ensureCapacity(size_type needCapacity) {
    if (needCapacity > __capacity) {
        ElementType *newData{__allocator.allocate(__capacity << 2)};
        for (size_type i{0}; i < size(); ++i) {
            __allocator.construct(newData + i, std::move(__data[i]));
            __allocator.destroy(__data + i);
        }
        __allocator.deallocate(__data, __capacity);
        __data = newData;
        __capacity <<= 2;
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

    difference_type operator-(const iterator &rhs) {
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

    bool operator==(const iterator &rhs) {
        return __cur == rhs.__cur;
    }

    bool operator!=(const iterator &rhs) {
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

    difference_type operator-(const reverse_iterator &rhs) {
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

    bool operator==(const reverse_iterator &rhs) {
        return __cur == rhs.__cur;
    }

    bool operator!=(const reverse_iterator &rhs) {
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
typename ArrayList<ElementType>::reverse_iterator ArrayList<ElementType>::rbegin() {
    return reverse_iterator{__data + __size};
}

template <typename ElementType>
typename ArrayList<ElementType>::reverse_iterator ArrayList<ElementType>::rend() {
    return reverse_iterator{__data};
}

} // namespace dsa

#endif