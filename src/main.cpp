#include <iostream>

#include "fraction.hpp"

int main()
{
    std::cout << "Hello, World!" << std::endl;
    // Fraction f1 = 21;
    // Fraction f2 = f1;
    // f2 = 5;
    // f1 = "-988/12";
    // std::cout << "Fr1: " << f1 << "\nFr2: " << f2 << std::endl;

    Fraction f1, f2;

    std::cout << "Please type in two fractions:" << std::endl;
    std::cin >> f1 >> f2;

    std::cout << "Fr1:\t" << f1 << "\nFr2:\t" << f2 << std::endl;

    return 0;
}