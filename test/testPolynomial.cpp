#include "Polynomial.hpp"

dsa::Polynomial f(double c2, double c1, double c0) {
    dsa::Polynomial ret{c0, c1, c2};
    return ret;
}

int main() {
    dsa::Polynomial q{3};
    q = f(3, 4, 5);
    q.print(std::cout);
    std::cout << std::endl;
    return 0;
}