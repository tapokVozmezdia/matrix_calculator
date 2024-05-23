#pragma once

#include <iostream>

#include "lmc.hpp"

class Fraction
{
    public:
        // returns fraction that is equal to zero
        Fraction() = default;

        // returns fraction that is equal to an integer
        Fraction(llint value);

        // argument list: numerator, denominator
        Fraction(llint num, llint den);

        // returns fraction that is equal to another fraction
        Fraction(const Fraction& other);

        Fraction& operator=(llint value);
        // gets a string in format 'x/y' as an argument. example: f1 = "5/3" 
        Fraction& operator=(const std::string& other);
        Fraction& operator=(const Fraction& other);

        Fraction operator+(llint value);
        Fraction operator+(const Fraction& other);

        Fraction operator*(llint value);
        Fraction operator*(const Fraction& other);

        Fraction operator-(llint value);
        Fraction operator-(const Fraction& other);

        Fraction operator/(llint value);
        Fraction operator/(const Fraction& other);

        Fraction& operator+=(llint value);
        Fraction& operator+=(const Fraction& other);

        Fraction& operator*=(llint value);
        Fraction& operator*=(const Fraction& other);

        Fraction& operator-=(llint value);
        Fraction& operator-=(const Fraction& other);

        Fraction& operator/=(llint value);
        Fraction& operator/=(const Fraction& other);

        bool operator==(llint value);
        bool operator==(const Fraction& other);

        Fraction& operator++();
        Fraction& operator--();

        friend std::ostream& operator<<
            (std::ostream& ostream, const Fraction& fraction);

        friend std::istream& operator>>
            (std::istream& istream, Fraction& fraction);

        llint Numerator();
        llint Denominator();

        // returns a float representation
        double Float();

        void setNumerator(llint value);
        void setDenominator(llint value);

    private:
        void __simplify();

        llint _numerator = 0;
        llint _denominator = 1;
};