#ifndef __SET_TYPE_H__
#define __SET_TYPE_H__

#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

namespace dsa {

inline namespace explicit_implementation {

template <typename ElementType>
class SetType;

template <typename ElementType>
SetType<ElementType> merge(const SetType<ElementType> &lhs, const SetType<ElementType> &rhs);

template <typename ElementType>
SetType<ElementType> intersection(const SetType<ElementType> &lhs, const SetType<ElementType> &rhs);

template <typename ElementType>
SetType<ElementType> difference(const SetType<ElementType> &lhs, const SetType<ElementType> &rhs);

namespace detail {
template <typename ElementType>
void __checkOperationSet(const dsa::SetType<ElementType> &lhs, const dsa::SetType<ElementType> &rhs) {
    assert(lhs.__elements.size() == rhs.__elements.size());
    // TODO: 检查输入的两个SetType映射函数一致
}
} // namespace detail

/*
 * @Author       : sphc
 * @Date         : 2023-11-10 13:01:53
 * @LastEditors  : sphc
 * @LastEditTime : 2023-11-10 14:02:07
 * @FilePath     : /include/SetType.hpp
 * @Description  : 显式实现的集合，假设集合中的数量有限，并且每个元素都能唯一映射
 */
template <typename ElementType>
class SetType {
public:
    friend void detail::__checkOperationSet<ElementType>(const SetType<ElementType> &lhs, const SetType<ElementType> &rhs);
    friend SetType<ElementType> merge<ElementType>(const SetType<ElementType> &lhs, const SetType<ElementType> &rhs);
    friend SetType<ElementType> intersection<ElementType>(const SetType<ElementType> &lhs, const SetType<ElementType> &rhs);
    friend SetType<ElementType> difference<ElementType>(const SetType<ElementType> &lhs, const SetType<ElementType> &obj);

    using size_type = std::size_t;
    using MapFunc = std::function<size_type(const ElementType &e)>;
    using DeMapFunc = std::function<ElementType(size_type)>;
    explicit SetType(MapFunc mapFunc, size_type size = __default_size);
    SetType(const SetType &) = default;
    SetType(SetType &&) = default;
    SetType &operator=(const SetType &) = default;
    SetType &operator=(SetType &&) = default;
    ~SetType() = default;

    /**
     * @description: 将集合置空
     * @return      {void}
     */
    void makeEmpty() noexcept;
    /**
     * @description: 判断集合是否为空
     * @return      {bool} 若集合为空返回 true，否则返回 false
     */
    [[nodiscard]] bool isEmpty() const noexcept;
    /**
     * @description: 判断集合是否已满
     * @return      {bool} 若集合已满返回 true，否则返回 false
     */
    [[nodiscard]] bool isFull() const noexcept;
    /**
     * @description: 获取集合中元素数量
     * @return      {size_type} 集合中的元素数量
     */
    [[nodiscard]] size_type size() const noexcept;
    /**
     * @description: 向集合中添加元素，若集合中已存在该元素，则无任何操作
     * @param       {ElementType} e 需要添加的元素
     * @return      {void}
     */
    void add(const ElementType &e) noexcept;
    /**
     * @description: 从集合中删除元素，若集合中没有该元素，则无任何操作
     * @param       {ElementType} e 需要删除的元素
     * @return      {void}
     */
    void remove(const ElementType &e) noexcept;
    /**
     * @description:
     * @param       {DeMapFunc} 从映射结果反推得到元素的函数
     * @return      {void}
     */
    void print(DeMapFunc deMapFunc) noexcept;

private:
    inline static constexpr size_type __default_size{512};
    // 位图，将元素根据映射函数映射到对应的索引处，若元素存在则用 1 标识，否则用 0 标识
    const MapFunc __mapFunc;
    std::vector<unsigned char> __elements;
};

template <typename ElementType>
SetType<ElementType>::SetType(MapFunc mapFunc, size_type size) :
    __mapFunc{mapFunc}, __elements(size, 0) {
}

/**
 * @description: 将集合置空
 * @return      {void}
 */
template <typename ElementType>
void SetType<ElementType>::makeEmpty() noexcept {
    std::for_each(std::begin(__elements), std::end(__elements), [](auto &flag) { flag = 0; });
}

/**
 * @description: 判断集合是否为空
 * @return      {bool} 若集合为空返回 true，否则返回 false
 */
template <typename ElementType>
[[nodiscard]] bool SetType<ElementType>::isEmpty() const noexcept {
    auto it = std::find(std::cbegin(__elements), std::cend(__elements), 1);
    return it == std::cend(__elements);
}

/**
 * @description: 判断集合是否已满
 * @return      {bool} 若集合已满返回 true，否则返回 false
 */
template <typename ElementType>
[[nodiscard]] bool SetType<ElementType>::isFull() const noexcept {
    auto it = std::find(std::cbegin(__elements), std::cend(__elements), 0);
    return it == std::cend(__elements);
}

/**
 * @description: 获取集合中元素数量
 * @return      {size_type} 集合中的元素数量
 */
template <typename ElementType>
[[nodiscard]] typename SetType<ElementType>::size_type SetType<ElementType>::size() const noexcept {
    return std::accumulate(std::cbegin(__elements), std::cend(__elements), 0);
}

/**
 * @description: 向集合中添加元素，若集合中已存在该元素，则无任何操作
 * @param       {ElementType} e 需要添加的元素
 * @return      {void}
 */
template <typename ElementType>
void SetType<ElementType>::add(const ElementType &e) noexcept {
    if (__elements.size() == 0) {
        return;
    }
    // TODO: 映射超出范围，抛出异常
    __elements[__mapFunc(e) % __elements.size()] = 1;
}

/**
 * @description: 从集合中删除元素，若集合中没有该元素，则无任何操作
 * @param       {ElementType} e 需要删除的元素
 * @return      {void}
 */
template <typename ElementType>
void SetType<ElementType>::remove(const ElementType &e) noexcept {
    if (__elements.size() == 0) {
        return;
    }
    // TODO: 映射超出范围，抛出异常
    __elements[__mapFunc(e) % __elements.size()] = 0;
}

/**
 * @description:
 * @param       {DeMapFunc} 从映射结果反推得到元素的函数
 * @return      {void}
 */
template <typename ElementType>
void SetType<ElementType>::print(DeMapFunc deMapFunc) noexcept {
    for (size_type i{0}; i < __elements.size(); ++i) {
        if (__elements[i]) {
            std::cout << deMapFunc(i) << " ";
        }
    }
    std::cout << std::endl;
}

template <typename ElementType>
SetType<ElementType> merge(const SetType<ElementType> &lhs, const SetType<ElementType> &rhs) {
    detail::__checkOperationSet(lhs, rhs);

    SetType<ElementType> ret{lhs};
    for (typename SetType<ElementType>::size_type i{0}; i < lhs.__elements.size(); ++i) {
        if (rhs.__elements[i] == 1) {
            ret.__elements[i] = 1;
        }
    }
    return ret;
}

template <typename ElementType>
SetType<ElementType> intersection(const SetType<ElementType> &lhs, const SetType<ElementType> &rhs) {
    detail::__checkOperationSet(lhs, rhs);

    SetType<ElementType> ret{lhs.__mapFunc, lhs.__elements.size()};
    for (typename SetType<ElementType>::size_type i{0}; i < lhs.__elements.size(); ++i) {
        if (lhs.__elements[i] == 1 && rhs.__elements[i] == 1) {
            ret.__elements[i] = 1;
        }
    }
    return ret;
}

template <typename ElementType>
SetType<ElementType> difference(const SetType<ElementType> &lhs, const SetType<ElementType> &rhs) {
    detail::__checkOperationSet(lhs, rhs);

    SetType<ElementType> ret{lhs.__mapFunc, lhs.__elements.size()};
    for (typename SetType<ElementType>::size_type i{0}; i < lhs.__elements.size(); ++i) {
        if (lhs.__elements[i] == 1 && rhs.__elements[i] != 1) {
            ret.__elements[i] = 1;
        }
    }
    return ret;
}

} // namespace explicit_implementation

namespace implicit_implementation {

template <typename ElementType>
class SetType;

template <typename ElementType>
SetType<ElementType> merge(const SetType<ElementType> &lhs, const SetType<ElementType> &rhs);

template <typename ElementType>
SetType<ElementType> intersection(const SetType<ElementType> &lhs, const SetType<ElementType> &rhs);

template <typename ElementType>
SetType<ElementType> difference(const SetType<ElementType> &lhs, const SetType<ElementType> &rhs);

/*
 * @Author       : sphc
 * @Date         : 2023-11-10 13:01:53
 * @LastEditors  : sphc
 * @LastEditTime : 2023-11-10 14:02:07
 * @FilePath     : /include/SetType.hpp
 * @Description  : 隐式实现的集合，可装入任意数量的元素
 */
template <typename ElementType>
class SetType {
public:
    friend SetType<ElementType> merge<ElementType>(const SetType<ElementType> &lhs, const SetType<ElementType> &rhs);
    friend SetType<ElementType> intersection<ElementType>(const SetType<ElementType> &lhs, const SetType<ElementType> &rhs);
    friend SetType<ElementType> difference<ElementType>(const SetType<ElementType> &lhs, const SetType<ElementType> &obj);

    using size_type = std::size_t;
    SetType() = default;
    SetType(const SetType &) = default;
    SetType(SetType &&) = default;
    SetType &operator=(const SetType &) = default;
    SetType &operator=(SetType &&) = default;
    ~SetType() = default;

    /**
     * @description: 将集合置空
     * @return      {void}
     */
    void makeEmpty() noexcept;
    /**
     * @description: 判断集合是否为空
     * @return      {bool} 若集合为空返回 true，否则返回 false
     */
    [[nodiscard]] bool isEmpty() const noexcept;
    /**
     * @description: 获取集合中元素数量
     * @return      {size_type} 集合中的元素数量
     */
    [[nodiscard]] size_type size() const noexcept;
    /**
     * @description: 向集合中添加元素，若集合中已存在该元素，则无任何操作
     * @param       {ElementType} e 需要添加的元素
     * @return      {void}
     */
    void add(const ElementType &e);
    /**
     * @description: 向集合中添加元素，若集合中已存在该元素，则无任何操作
     * @param       {ElementType} e 需要添加的元素
     * @return      {void}
     */
    void add(ElementType &&e);
    /**
     * @description: 从集合中删除元素，若集合中没有该元素，则无任何操作
     * @param       {ElementType} e 需要删除的元素
     * @return      {void}
     */
    void remove(const ElementType &e);
    /**
     * @description:
     * @return      {void}
     */
    void print() noexcept;

private:
    std::vector<ElementType> __elements;
};

/**
 * @description: 将集合置空
 * @return      {void}
 */
template <typename ElementType>
void SetType<ElementType>::makeEmpty() noexcept {
    __elements.clear();
}

/**
 * @description: 判断集合是否为空
 * @return      {bool} 若集合为空返回 true，否则返回 false
 */
template <typename ElementType>
[[nodiscard]] bool SetType<ElementType>::isEmpty() const noexcept {
    return __elements.empty();
}

/**
 * @description: 获取集合中元素数量
 * @return      {size_type} 集合中的元素数量
 */
template <typename ElementType>
[[nodiscard]] typename SetType<ElementType>::size_type SetType<ElementType>::size() const noexcept {
    return __elements.size();
}

/**
 * @description: 向集合中添加元素，若集合中已存在该元素，则无任何操作
 * @param       {ElementType} e 需要添加的元素
 * @return      {void}
 */
template <typename ElementType>
void SetType<ElementType>::add(const ElementType &e) {
    __elements.push_back(e);
}

/**
 * @description: 向集合中添加元素，若集合中已存在该元素，则无任何操作
 * @param       {ElementType} e 需要添加的元素
 * @return      {void}
 */
template <typename ElementType>
void SetType<ElementType>::add(ElementType &&e) {
    __elements.push_back(std::move(e));
}

/**
 * @description: 从集合中删除元素，若集合中没有该元素，则无任何操作
 * @param       {ElementType} e 需要删除的元素
 * @return      {void}
 */
template <typename ElementType>
void SetType<ElementType>::remove(const ElementType &e) {
    // TODO: 二分查找
    auto it{std::find(std::cbegin(__elements), std::cend(__elements), e)};
    if (it != std::cend(__elements)) {
        __elements.erase(it);
    }
}

/**
 * @description:
 * @return      {void}
 */
template <typename ElementType>
void SetType<ElementType>::print() noexcept {
    std::for_each(std::cbegin(__elements), std::cend(__elements), [](const auto &e) { std::cout << e << " "; });
    std::cout << std::endl;
}

template <typename ElementType>
SetType<ElementType> merge(const SetType<ElementType> &lhs, const SetType<ElementType> &rhs) {
    // TODO: 使用二分查找，在元素多的表里面查
    SetType<ElementType> ret{lhs};
    std::for_each(std::cbegin(rhs.__elements), std::cend(rhs.__elements), [&ret](const auto &e) {
        if (std::find(std::cbegin(ret.__elements), std::cend(ret.__elements), e) == std::cend(ret.__elements)) {
            ret.__elements.push_back(e);
        }
    });
    return ret;
}

template <typename ElementType>
SetType<ElementType> intersection(const SetType<ElementType> &lhs, const SetType<ElementType> &rhs) {
    // TODO: 使用二分查找，在元素多的表里面查
    SetType<ElementType> ret{};
    std::for_each(std::cbegin(rhs.__elements), std::cend(rhs.__elements), [&ret, &lhs](const auto &e) {
        if (std::find(std::cbegin(lhs.__elements), std::cend(lhs.__elements), e) != std::cend(lhs.__elements)) {
            ret.__elements.push_back(e);
        }
    });
    return ret;
}

template <typename ElementType>
SetType<ElementType> difference(const SetType<ElementType> &lhs, const SetType<ElementType> &rhs) {
    // TODO: 使用二分查找，在元素多的表里面查
    SetType<ElementType> ret{lhs};
    std::for_each(std::cbegin(rhs.__elements), std::cend(rhs.__elements), [&ret](const auto &e) {
        auto it{std::find(std::cbegin(ret.__elements), std::cend(ret.__elements), e)};
        if (it != std::cend(ret.__elements)) {
            ret.__elements.erase(it);
        }
    });
    return ret;
}

} // namespace implicit_implementation

} // namespace dsa

#endif