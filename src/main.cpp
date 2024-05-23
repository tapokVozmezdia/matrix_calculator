#include <iostream>

#include "fraction.hpp"
#include "matrix.hpp"

int main()
{
    std::cout << "Hello, World!" << std::endl;

    Matrix<Fraction> m1;

    std::cout << m1 << std::endl;

    m1(3, 2) = "3/2";

    std::cout << m1 << std::endl;

    return 0;
}