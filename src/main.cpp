#include <iostream>

#include "fraction.hpp"
#include "matrix.hpp"

int main()
{
    std::cout << "Hello, World!" << std::endl;

    Matrix<Fraction> m1(3, 3), m2(3, 3);

    std::cout << "enter the first matrix:" << std::endl;
    std::cin >> m1;

    std::cout << "m1 inverse:\n" << m1.Inverse() << std::endl;

    return 0;
}