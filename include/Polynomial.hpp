#ifndef __POLYNOMIAL_H__
#define __POLYNOMIAL_H__

#include <initializer_list>
#include <iostream>
#include <vector>

namespace dsa {

/*
 * @Author       : sphc
 * @Date         : 2023-11-14 12:45:28
 * @LastEditors  : sphc
 * @LastEditTime : 2023-11-14 13:41:46
 * @FilePath     : /include/Polynomial.hpp
 * @Description  :
 */

class Polynomial {
public:
    Polynomial(int maxExponent);
    Polynomial(const Polynomial &) = default;
    Polynomial(Polynomial &&) = default;
    Polynomial(std::initializer_list<double> il);
    ~Polynomial() = default;

    Polynomial &operator=(const Polynomial &) = default;
    Polynomial &operator=(Polynomial &&obj);
    Polynomial &operator=(std::initializer_list<double> il);

    double &operator[](std::size_t index) &;
    const double &operator[](std::size_t index) const &;

    void print(std::ostream &os);

private:
    std::vector<double> __coefficients;
};

} // namespace dsa

#endif