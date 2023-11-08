/*
 * @Author       : sphc
 * @Date         : 2023-10-19 13:56:20
 * @LastEditors  : sphc
 * @LastEditTime : 2023-10-22 19:43:41
 * @FilePath     : /src/testArrayList.cpp
 * @Description  :
 */

#include "ArrayList.hpp"
#include "List.hpp"
#include "boost/type_index.hpp"
#include "boost/uuid/random_generator.hpp"
#include "boost/uuid/uuid_io.hpp"
#include <cassert>
#include <iostream>

class TestObject {
public:
    TestObject(int _) :
        uuid{boost::uuids::to_string(boost::uuids::random_generator()())} {
#ifdef DEBUG
        std::cout << "TestObject()" << std::endl;
#endif
    }
    TestObject(const TestObject &) {
#ifdef DEBUG
        std::cout << "TestObject(const TestObject &)" << std::endl;
#endif
    }
    TestObject(TestObject &&) {
#ifdef DEBUG
        std::cout << "TestObject(TestObject &&)" << std::endl;
#endif
    }
    TestObject &operator=(const TestObject &) {
#ifdef DEBUG
        std::cout << "operator=(const TestObject &)" << std::endl;
#endif
        return *this;
    }
    TestObject &operator=(TestObject &&) {
#ifdef DEBUG
        std::cout << "operator=(TestObject &&)" << std::endl;
#endif
        return *this;
    }
    ~TestObject() {
#ifdef DEBUG
        std::cout << "~TestObject()" << std::endl;
#endif
        ++destructorCallCount;
    }

    bool operator==(const TestObject &rhs) const {
#ifdef DEBUG
        std::cout << "operator==(const TestObject &)" << std::endl;
#endif
        return uuid == rhs.uuid;
    }

    bool operator!=(const TestObject &rhs) const {
#ifdef DEBUG
        std::cout << "operator==(const TestObject &)" << std::endl;
#endif
        return uuid != rhs.uuid;
    }

    static uint32_t getDestructorCallCount() {
        return destructorCallCount;
    }

private:
    std::string uuid;
    inline static uint32_t destructorCallCount{0};
};

template <typename ElementType>
class ListTest final {
public:
    using ListType = dsa::List<ElementType>;
    ListTest(ListType *list) :
        __list{list} {
    }
    ListTest(const ListTest &) = delete;
    ListTest(ListTest &&) = delete;
    ListTest &operator=(const ListTest &) = delete;
    ListTest &operator=(ListTest &&) = delete;

    void clear() {
        std::cout << "start test clear()." << std::endl;

        // 构造后 clear
        assert(__list->size() == 0);
        __list->clear();
        assert(__list->size() == 0);

        // 添加元素后 clear
        __list->add(1);
        __list->add(3);
        __list->add(5);
        __list->add(7);
        __list->add(9);
        assert(__list->size() != 0);
        __list->clear();
        assert(__list->size() == 0);

        // 添加元素且发生扩容后 clear
        __list->add(1);
        __list->add(3);
        __list->add(5);
        __list->add(7);
        __list->add(9);
        __list->add(2);
        __list->add(4);
        __list->add(6);
        __list->add(8);
        __list->add(10);
        __list->add(30);
        __list->add(26);
        __list->add(40);
        __list->add(13);
        __list->add(16);
        assert(__list->size() != 0);
        __list->clear();
        assert(__list->size() == 0);

        // 重复 clear
        __list->clear();
        assert(__list->size() == 0);

        std::cout << "test clear() for " << boost::typeindex::type_id_runtime(*__list).pretty_name() << " success." << std::endl;
    }

    void size() {
        std::cout << "start test size()." << std::endl;

        assert(__list->size() == 0);
        __list->add(1);
        assert(__list->size() == 1);
        __list->add(3);
        assert(__list->size() == 2);
        __list->add(5);
        assert(__list->size() == 3);
        __list->add(7);
        assert(__list->size() == 4);
        __list->add(9);
        assert(__list->size() == 5);

        __list->add(2);
        __list->add(4);
        __list->add(6);
        __list->add(8);
        __list->add(10);
        __list->add(30);
        __list->add(26);
        __list->add(40);
        __list->add(13);
        __list->add(16);
        assert(__list->size() == 15);

        __list->add(100);
        __list->add(35);
        __list->add(36);
        __list->add(47);
        __list->add(63);
        __list->add(86);
        __list->add(88);
        __list->add(78);
        __list->add(73);
        assert(__list->size() == 24);

        // __list->remove(__list->size() - 1);
        // assert(__list->size() == 23);
        // __list->remove(__list->size() - 1);
        // assert(__list->size() == 22);
        // __list->remove(__list->size() - 1);
        // assert(__list->size() == 21);
        // __list->remove(__list->size() - 1);
        // __list->remove(__list->size() - 1);
        // __list->remove(__list->size() - 1);
        // __list->remove(__list->size() - 1);
        // __list->remove(__list->size() - 1);
        // assert(__list->size() == 16);
        // __list->remove(__list->size() - 1);
        // __list->remove(__list->size() - 1);
        // __list->remove(__list->size() - 1);
        // __list->remove(__list->size() - 1);
        // __list->remove(__list->size() - 1);
        // __list->remove(__list->size() - 1);
        // __list->remove(__list->size() - 1);
        // assert(__list->size() == 9);

        std::cout << "test size() for " << boost::typeindex::type_id_runtime(*__list).pretty_name() << " success." << std::endl;
    }

    // bool isEmpty() {
    // }

    // bool contains(const ElementType &element) {
    // }

    void add() {
        std::cout << "start test add()." << std::endl;

        assert(__list->size() == 0);
        __list->add(1);
        assert(__list->size() == 1);
        __list->add(3);
        assert(__list->size() == 2);
        __list->add(5);
        assert(__list->size() == 3);
        __list->add(7);
        assert(__list->size() == 4);
        __list->add(9);
        assert(__list->size() == 5);

        __list->add(2);
        __list->add(4);
        __list->add(6);
        __list->add(8);
        __list->add(10);
        __list->add(30);
        __list->add(26);
        __list->add(40);
        __list->add(13);
        __list->add(16);
        assert(__list->size() == 15);

        std::cout << "test add() for " << boost::typeindex::type_id_runtime(*__list).pretty_name() << " success." << std::endl;
    }

    // void add(size_type index, const ElementType &element) {
    // }

private:
    std::shared_ptr<ListType> __list;
};

// const ElementType &get(size_type index) {
// }

// ElementType set(size_type index, const ElementType &element) {
// }

// ElementType remove(size_type index) {
// }

// size_type indexOf(const ElementType &element) {
// }

// std::string toString(std::function<std::string(const ElementType &)> toString) {
// }

int main() {
    {
        ListTest<int> test{new dsa::ArrayList<int>{}};
        test.clear();
    }
    {
        ListTest<TestObject> test{new dsa::ArrayList<TestObject>{}};
        test.clear();
    }
    // {
    //     ListTest<int> test{new dsa::ArrayList<int>{}};
    //     test.size();
    // }
    // {
    //     ListTest<TestObject> test{new dsa::ArrayList<TestObject>{}};
    //     test.size();
    // }
    // {
    //     ListTest<int> test{new dsa::ArrayList<int>{}};
    //     test.add();
    // }
    // {
    //     ListTest<TestObject> test{new dsa::ArrayList<TestObject>{}};
    //     test.add();
    // }
    return 0;
}