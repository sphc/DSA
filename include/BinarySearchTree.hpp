/*
 * @Author       : sphc
 * @Date         : 2023-10-20 18:54:55
 * @LastEditors  : sphc
 * @LastEditTime : 2023-10-22 22:34:22
 * @FilePath     : /include/BinarySearchTree.hpp
 * @Description  :
 */
class BinarySearchTree {
public:
    int size();
    bool isEmpty();
    void clear();
    void add(E);
    void remove(E);
    bool contains(E);

    // 计算树的高度： 迭代 + 递归
    // 判断是否为完全二叉树
};