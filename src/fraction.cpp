#include <exception>
#include <string>
#include <sstream>
#include <numeric>

#include "fraction.hpp"

std::ostream& operator<<(std::ostream& ostream, const Fraction& fraction)
{
    ostream << fraction._numerator << "/" << fraction._denominator;
    return ostream;
}

Fraction::Fraction(llint value) 
{
    this->_numerator = value;
}

Fraction::Fraction(const Fraction& other) 
{
    this->_numerator = other._numerator;
    this->_denominator = other._denominator;
}

Fraction& Fraction::operator=(llint value) 
{
    this->_numerator = value;
    this->_denominator = 1;
    return *this;
}

Fraction& Fraction::operator=(const std::string& other)
{
    if (other.length() == 0)
        return *this;

    std::stringstream s(other);

    std::string num, den;
    getline(s, num, '/');
    getline(s, den);
    
    this->_numerator = stoi(num);
    this->_denominator = stoi(den);

    this->__simplify();

    return *this;
}

void Fraction::setNumerator(llint value)
{
    this->_numerator = value;
    this->__simplify();
}

void Fraction::setDenominator(llint value)
{
    if (value == 0)
        throw std::logic_error("zero division error");

    this->_denominator = value;
    this->__simplify();
}

//--

void Fraction::__simplify()
{
    if (this->_denominator == 0)
        throw std::logic_error("zero division error");

    while(std::gcd(this->_numerator, this->_denominator) != 1)
    {
        llint gcd = std::gcd(this->_numerator, this->_denominator);
        this->_numerator /= gcd;
        this->_denominator /= gcd;
    }
}