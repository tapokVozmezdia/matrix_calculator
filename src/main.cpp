#include <iostream>

#include "fraction.hpp"
#include "matrix.hpp"

int main()
{
    std::cout << "Hello, World!" << std::endl;

    Matrix<Fraction> m1;

    m1(3, 2) = "3/2";

    Matrix<Fraction> m2(m1);
    m1(3, 1) = "44/24";

    std::cout << "M1:\n" << m1 << "\nM2:\n" << m2 << std::endl;

    Matrix<Fraction> m3(5, 3);
    for (int i = 1; i <= 5; ++i)
        for (int j = 1; j <= 3; ++j)
            m3(i, j) = (i-1)*3 + j - 1;

    std::cout << "M3:\n" << m3 << std::endl;

    std::cout << "M3 =\n" << m3 - (m3 * Fraction(std::string("-1/3"))) << std::endl;

    return 0;
}