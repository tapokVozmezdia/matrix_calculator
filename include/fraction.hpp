#include <iostream>

#include "lmc.hpp"

using i = int;

class Fraction
{
    public:
        // returns fraction that is equal to zero
        Fraction() = default;

        // returns fraction that is equal to an integer
        Fraction(llint value);

        // returns fraction that is equal to another fraction
        Fraction(const Fraction& other);

        Fraction& operator=(llint value);
        // gets a string in format 'x/y' as an argument. example: f1 = "5/3" 
        Fraction& operator=(const std::string& other);
        Fraction& operator=(const Fraction& other);

        friend std::ostream& operator<<
            (std::ostream& ostream, const Fraction& fraction);

        void setNumerator(llint value);
        void setDenominator(llint value);

    private:
        void __simplify();

        llint _numerator = 0;
        llint _denominator = 1;
};