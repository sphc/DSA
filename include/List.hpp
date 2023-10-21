#ifndef __LIST_H__
#define __LIST_H__

#include <functional>
#include <limits>
#include <string>

namespace dsa {

/*
 * @Author       : sphc
 * @Date         : 2023-10-19 13:54:08
 * @LastEditors  : sphc
 * @LastEditTime : 2023-10-21 13:09:16
 * @FilePath     : /include/List.hpp
 * @Description  : List 集合接口
 */
template <typename ElementType>
class List {
public:
    using size_type = std::size_t;
    // TODO: check npos
    inline static constexpr size_type npos{std::numeric_limits<size_type>::max()};

    /**
     * @description: 清除集合中的所有元素
     * @return      {void}
     */
    virtual void clear() = 0;

    /**
     * @description: 获取集合中元素数量
     * @return      {size_type} 集合中元素的数量
     */
    [[nodiscard]] virtual size_type size() const = 0;

    /**
     * @description: 检查集合是否有元素
     * @return      {bool} 无元素返回 true，有元素返回 false
     */
    [[nodiscard]] virtual bool isEmpty() const = 0;

    /**
     * @description: 查找元素是否出现在集合中
     * @param       {const ElementType &} element 需要查找的元素
     * @return      {bool} 存在返回 true，不存在返回 false
     */
    [[nodiscard]] virtual bool contains(const ElementType &element) const = 0;

    /**
     * @description: 往集合末尾插入元素
     * @param       {const ElementType &} element 需要插入的元素
     * @return      {void}
     */
    virtual void add(const ElementType &element) = 0;

    /**
     * @description: 在集合指定位置处插入元素
     * @param       {size_type} index 指定位置索引，取值范围 [0, size()]
     * @param       {ElementType} &element 要插入的元素
     * @return      {void}
     */
    virtual void add(size_type index, const ElementType &element) = 0;

    /**
     * @description: 获取集合指定位置处的元素
     * @param       {size_type} index 指定位置索引，取值范围 [0, size() - 1]
     * @return      {const ElementType &} 指定位置处的元素
     */
    [[nodiscard]] virtual const ElementType &get(size_type index) const = 0;

    /**
     * @description: 将集合指定位置处的元素设置为指定元素
     * @param       {size_type} index 指定位置索引，取值范围 [0, size() - 1]
     * @param       {const ElementType &} element 要设置的元素
     * @return      {ElementType} 设置之前的元素
     */
    virtual ElementType set(size_type index, const ElementType &element) = 0;

    /**
     * @description: 删除集合指定位置处的元素
     * @param       {size_type} index 指定位置索引，取值范围 [0, size() - 1]
     * @return      {ElementType} 被删除的元素
     */
    virtual ElementType remove(size_type index) = 0;

    /**
     * @description: 在集合中获取指定元素的位置索引
     * @param       {ElementType} &element 指定元素
     * @return      {size_type} 指定元素所在的位置索引，未找到则返回 ArrayList<ElementType>::npos
     */
    [[nodiscard]] virtual size_type indexOf(const ElementType &element) const = 0;

    /**
     * @description: 将集合转换为字符串表示，可用于打印等
     * @param       {function<void(ElementType &)>} toString 将集合中元素转换为字符串的方法
     * @return      {string} 集合的字符串表示
     */
    [[nodiscard]] virtual std::string toString(std::function<std::string(const ElementType &)> toString) const = 0;

protected:
    enum class _ListOperation {
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

    template <_ListOperation operation>
    static std::string _getOperationName();
};

template <typename ElementType>
template <typename List<ElementType>::_ListOperation operation>
std::string List<ElementType>::_getOperationName() {
    if constexpr (operation == _ListOperation::CLEAR) {
        return "clear";
    } else if constexpr (operation == _ListOperation::SIZE) {
        return "size";
    } else if constexpr (operation == _ListOperation::IS_EMPTY) {
        return "isEmpty";
    } else if constexpr (operation == _ListOperation::CONTAINS) {
        return "contains";
    } else if constexpr (operation == _ListOperation::ADD) {
        return "add";
    } else if constexpr (operation == _ListOperation::ADD_BY_INDEX) {
        return "add";
    } else if constexpr (operation == _ListOperation::GET) {
        return "get";
    } else if constexpr (operation == _ListOperation::SET) {
        return "set";
    } else if constexpr (operation == _ListOperation::REMOVE) {
        return "remove";
    } else if constexpr (operation == _ListOperation::INDEX_OF) {
        return "indexOf";
    } else if constexpr (operation == _ListOperation::TO_STRING) {
        return "toString";
    } else {
        return "unknow";
    }
}

} // namespace dsa

#endif