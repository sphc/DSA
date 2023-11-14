/*
 * @Author       : sphc
 * @Date         : 2023-11-14 12:50:12
 * @LastEditors  : sphc
 * @LastEditTime : 2023-11-14 13:51:25
 * @FilePath     : /src/Polynomial.cpp
 * @Description  :
 */
#include "Polynomial.hpp"

namespace dsa {

Polynomial::Polynomial(int maxExponent) :
    __coefficients(maxExponent + 1, 0) {
}

void Polynomial::print(std::ostream &os) {
    decltype(__coefficients.size()) i{1};
    for (auto it = __coefficients.crbegin(); it != __coefficients.crend(); ++it) {
        if (i != 1) {
            std::cout << " + ";
        }
        std::cout << *it << "x^" << __coefficients.size() - i;
        ++i;
    }
}

Polynomial &Polynomial::operator=(Polynomial &&obj) {
    std::cout << "Polynomial operator=(Polynomial &&)" << std::endl;
    if (this != &obj) {
        __coefficients = std::move(obj.__coefficients);
    }
    return *this;
}

Polynomial::Polynomial(std::initializer_list<double> il) :
    __coefficients(std::move(il)) {
}

Polynomial &Polynomial::operator=(std::initializer_list<double> il) {
    __coefficients = std::move(il);
    return *this;
}

double &Polynomial::operator[](std::size_t index) & {
    return const_cast<double &>(static_cast<const Polynomial &>(*this).operator[](index));
}

const double &Polynomial::operator[](std::size_t index) const & {
    return __coefficients[index];
}

} // namespace dsa