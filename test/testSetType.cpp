#include "SetType.hpp"
#include <cassert>
#include <iostream>

void testImplicitImplementation() {
    dsa::implicit_implementation::SetType<char> setA{};
    assert(setA.isEmpty());
    assert(setA.size() == 0);
    setA.add('b');
    setA.add('c');
    setA.add('d');
    setA.add('a');
    setA.add('e');
    setA.add('g');
    setA.add('f');
    setA.add('h');
    setA.add('k');
    setA.add('j');
    setA.add('i');
    setA.add('l');
    assert(setA.size() == 12);
    std::cout << "setA: " << std::endl;
    std::cout << "  expect  : a b c d e f g h i j k l" << std::endl;
    std::cout << "  real    : ";
    setA.print();

    dsa::implicit_implementation::SetType<char> setB{};
    assert(setB.isEmpty());
    assert(setB.size() == 0);
    setB.add('d');
    setB.add('a');
    setB.add('c');
    setB.add('j');
    setB.add('k');
    setB.add('m');
    setB.add('n');
    setB.add('o');
    setB.add('p');
    setB.add('q');
    setB.add('r');
    setB.add('s');
    setB.add('t');
    setB.add('u');
    assert(setB.size() == 14);
    std::cout << "setB: " << std::endl;
    std::cout << "  expect  : a c d j k m n o p q r s t u" << std::endl;
    std::cout << "  real    : ";
    setB.print();

    dsa::implicit_implementation::SetType<char> mergeAB{dsa::implicit_implementation::merge(setA, setB)};
    assert(mergeAB.size() == 21);
    std::cout << "mergeAB: " << std::endl;
    std::cout << "  expect  : a b c d e f g h i j k l m n o p q r s t u" << std::endl;
    std::cout << "  real    : ";
    mergeAB.print();
    mergeAB.add('v');
    mergeAB.add('w');
    mergeAB.add('x');
    mergeAB.add('y');
    mergeAB.add('z');
    std::cout << "mergeAB: " << std::endl;
    std::cout << "  expect  : a b c d e f g h i j k l m n o p q r s t u v w x y z" << std::endl;
    std::cout << "  real    : ";
    mergeAB.print();

    dsa::implicit_implementation::SetType<char> mergeBA{dsa::implicit_implementation::merge(setB, setA)};
    assert(mergeBA.size() == 21);
    std::cout << "mergeBA: " << std::endl;
    std::cout << "  expect  : a b c d e f g h i j k l m n o p q r s t u" << std::endl;
    std::cout << "  real    : ";
    mergeBA.print();
    mergeBA.add('v');
    mergeBA.add('w');
    mergeBA.add('x');
    mergeBA.add('y');
    mergeBA.add('z');
    std::cout << "mergeBA: " << std::endl;
    std::cout << "  expect  : a b c d e f g h i j k l m n o p q r s t u v w x y z" << std::endl;
    std::cout << "  real    : ";
    mergeBA.print();

    dsa::implicit_implementation::SetType<char> intersectionAB{dsa::implicit_implementation::intersection(setA, setB)};
    assert(intersectionAB.size() == 5);
    std::cout << "intersectionAB: " << std::endl;
    std::cout << "  expect  : a c d j k" << std::endl;
    std::cout << "  real    : ";
    intersectionAB.print();
    intersectionAB.remove('j');
    intersectionAB.remove('k');
    assert(intersectionAB.size() == 3);
    std::cout << "intersectionAB: " << std::endl;
    std::cout << "  expect  : a c d" << std::endl;
    std::cout << "  real    : ";
    intersectionAB.print();
    intersectionAB.remove('c');
    intersectionAB.remove('a');
    intersectionAB.remove('d');
    assert(intersectionAB.isEmpty());
    intersectionAB.remove('c');
    assert(intersectionAB.isEmpty());

    dsa::implicit_implementation::SetType<char> intersectionBA{dsa::implicit_implementation::intersection(setB, setA)};
    assert(intersectionBA.size() == 5);
    std::cout << "intersectionBA: " << std::endl;
    std::cout << "  expect  : a c d j k" << std::endl;
    std::cout << "  real    : ";
    intersectionBA.print();
    intersectionBA.remove('j');
    intersectionBA.remove('k');
    assert(intersectionBA.size() == 3);
    std::cout << "intersectionBA: " << std::endl;
    std::cout << "  expect  : a c d" << std::endl;
    std::cout << "  real    : ";
    intersectionBA.print();
    intersectionBA.remove('c');
    intersectionBA.remove('a');
    intersectionBA.remove('d');
    assert(intersectionBA.isEmpty());
    intersectionBA.remove('c');
    assert(intersectionBA.isEmpty());

    dsa::implicit_implementation::SetType<char> differenceAB{dsa::implicit_implementation::difference(setA, setB)};
    assert(differenceAB.size() == 7);
    std::cout << "differenceAB: " << std::endl;
    std::cout << "  expect  : b e f g h i l" << std::endl;
    std::cout << "  real    : ";
    differenceAB.print();

    dsa::implicit_implementation::SetType<char> differenceBA{dsa::implicit_implementation::difference(setB, setA)};
    assert(differenceBA.size() == 9);
    std::cout << "differenceBA: " << std::endl;
    std::cout << "  expect  : m n o p q r s t u" << std::endl;
    std::cout << "  real    : ";
    differenceBA.print();
}

void testExplicitImplementation() {
    dsa::SetType<char> setA{[](const auto &c) { return c - 'a'; }, 26};
    assert(setA.isEmpty());
    assert(setA.size() == 0);
    setA.add('b');
    setA.add('c');
    setA.add('d');
    setA.add('a');
    setA.add('e');
    setA.add('g');
    setA.add('f');
    setA.add('h');
    setA.add('k');
    setA.add('j');
    setA.add('i');
    setA.add('l');
    assert(setA.size() == 12);
    std::cout << "setA: " << std::endl;
    std::cout << "  expect  : a b c d e f g h i j k l" << std::endl;
    std::cout << "  real    : ";
    setA.print([](size_t i) { return 'a' + i; });

    dsa::SetType<char> setB{[](const auto &c) { return c - 'a'; }, 26};
    assert(setB.isEmpty());
    assert(setB.size() == 0);
    setB.add('d');
    setB.add('a');
    setB.add('c');
    setB.add('j');
    setB.add('k');
    setB.add('m');
    setB.add('n');
    setB.add('o');
    setB.add('p');
    setB.add('q');
    setB.add('r');
    setB.add('s');
    setB.add('t');
    setB.add('u');
    assert(setB.size() == 14);
    std::cout << "setB: " << std::endl;
    std::cout << "  expect  : a c d j k m n o p q r s t u" << std::endl;
    std::cout << "  real    : ";
    setB.print([](size_t i) { return 'a' + i; });

    dsa::SetType<char> mergeAB{dsa::merge(setA, setB)};
    assert(mergeAB.size() == 21);
    std::cout << "mergeAB: " << std::endl;
    std::cout << "  expect  : a b c d e f g h i j k l m n o p q r s t u" << std::endl;
    std::cout << "  real    : ";
    mergeAB.print([](size_t i) { return 'a' + i; });
    mergeAB.add('v');
    mergeAB.add('w');
    mergeAB.add('x');
    mergeAB.add('y');
    mergeAB.add('z');
    assert(mergeAB.isFull());
    mergeAB.add('g');
    assert(mergeAB.isFull());
    std::cout << "mergeAB: " << std::endl;
    std::cout << "  expect  : a b c d e f g h i j k l m n o p q r s t u v w x y z" << std::endl;
    std::cout << "  real    : ";
    mergeAB.print([](size_t i) { return 'a' + i; });

    dsa::SetType<char> mergeBA{dsa::merge(setB, setA)};
    assert(mergeBA.size() == 21);
    std::cout << "mergeBA: " << std::endl;
    std::cout << "  expect  : a b c d e f g h i j k l m n o p q r s t u" << std::endl;
    std::cout << "  real    : ";
    mergeBA.print([](size_t i) { return 'a' + i; });
    mergeBA.add('v');
    mergeBA.add('w');
    mergeBA.add('x');
    mergeBA.add('y');
    mergeBA.add('z');
    assert(mergeBA.isFull());
    mergeBA.add('d');
    assert(mergeBA.isFull());
    std::cout << "mergeBA: " << std::endl;
    std::cout << "  expect  : a b c d e f g h i j k l m n o p q r s t u v w x y z" << std::endl;
    std::cout << "  real    : ";
    mergeBA.print([](size_t i) { return 'a' + i; });

    dsa::SetType<char> intersectionAB{dsa::intersection(setA, setB)};
    assert(intersectionAB.size() == 5);
    std::cout << "intersectionAB: " << std::endl;
    std::cout << "  expect  : a c d j k" << std::endl;
    std::cout << "  real    : ";
    intersectionAB.print([](size_t i) { return 'a' + i; });
    intersectionAB.remove('j');
    intersectionAB.remove('k');
    assert(intersectionAB.size() == 3);
    std::cout << "intersectionAB: " << std::endl;
    std::cout << "  expect  : a c d" << std::endl;
    std::cout << "  real    : ";
    intersectionAB.print([](size_t i) { return 'a' + i; });
    intersectionAB.remove('c');
    intersectionAB.remove('a');
    intersectionAB.remove('d');
    assert(intersectionAB.isEmpty());
    intersectionAB.remove('c');
    assert(intersectionAB.isEmpty());

    dsa::SetType<char> intersectionBA{dsa::intersection(setB, setA)};
    assert(intersectionBA.size() == 5);
    std::cout << "intersectionBA: " << std::endl;
    std::cout << "  expect  : a c d j k" << std::endl;
    std::cout << "  real    : ";
    intersectionBA.print([](size_t i) { return 'a' + i; });
    intersectionBA.remove('j');
    intersectionBA.remove('k');
    assert(intersectionBA.size() == 3);
    std::cout << "intersectionBA: " << std::endl;
    std::cout << "  expect  : a c d" << std::endl;
    std::cout << "  real    : ";
    intersectionBA.print([](size_t i) { return 'a' + i; });
    intersectionBA.remove('c');
    intersectionBA.remove('a');
    intersectionBA.remove('d');
    assert(intersectionBA.isEmpty());
    intersectionBA.remove('c');
    assert(intersectionBA.isEmpty());

    dsa::SetType<char> differenceAB{dsa::difference(setA, setB)};
    assert(differenceAB.size() == 7);
    std::cout << "differenceAB: " << std::endl;
    std::cout << "  expect  : b e f g h i l" << std::endl;
    std::cout << "  real    : ";
    differenceAB.print([](size_t i) { return 'a' + i; });

    dsa::SetType<char> differenceBA{dsa::difference(setB, setA)};
    assert(differenceBA.size() == 9);
    std::cout << "differenceBA: " << std::endl;
    std::cout << "  expect  : m n o p q r s t u" << std::endl;
    std::cout << "  real    : ";
    differenceBA.print([](size_t i) { return 'a' + i; });
}

int main() {
    testImplicitImplementation();
    // testExplicitImplementation();
    return 0;
}