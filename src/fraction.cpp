#include <exception>
#include <string>
#include <sstream>
#include <numeric>
#include <cmath>

#include "fraction.hpp"

std::ostream& operator<<(std::ostream& ostream, const Fraction& fraction)
{
    if (fraction._denominator != 1)
        ostream << fraction._numerator << "/" << fraction._denominator;
    else   
        ostream << fraction._numerator;

    return ostream;
}

std::istream& operator>>(std::istream& istream, Fraction& fraction)
{
    std::string value;
    istream >> value;
    fraction = value;
    return istream;
}

Fraction::Fraction(int value)
{
    this->_numerator = value;
}

Fraction::Fraction(uint value)
{
    this->_numerator = value;
}

Fraction::Fraction(llint value) 
{
    this->_numerator = value;
}

Fraction::Fraction(float value)
{
    *this = value;
}

Fraction::Fraction(double value)
{
    *this = value;
}

Fraction::Fraction(llint num, llint den)
{
    if (den == 0)
        throw std::logic_error("zero division error");

    this->_numerator = num;
    this->_denominator = den;

    this->__simplify();
}

Fraction::Fraction(const std::string& fraction)
{
    *this = fraction;
}

Fraction::Fraction(const char* fraction)
{
    *this = fraction;
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

Fraction& Fraction::operator=(float value)
{
    llint den = 1;

    while(true)
    {   
        if (value == std::round(value))
        {
            this->_numerator = value;
            this->_denominator = den;

            this->__simplify();

            return *this;
        }
        value *= 10;
        den *= 10;
    }
}

Fraction& Fraction::operator=(double value)
{
    *this = static_cast<float>(value);
    return *this;
}

Fraction& Fraction::operator=(const std::string& other)
{
    if (other.length() == 0)
        return *this;

    if (lmc::is_double(other))
    {
        *this = std::stof(other);
        return *this;
    }

    std::stringstream s(other);

    std::string num, den;
    getline(s, num, '/');
    getline(s, den);
    
    this->_numerator = stoi(num);
    if (den.length() != 0)
        this->_denominator = stoi(den);

    if (this->_denominator == 0)
        throw std::logic_error("zero division error");

    this->__simplify();

    return *this;
}

Fraction& Fraction::operator=(const char* other)
{
    *this = std::string(other);
    return *this;
}

Fraction& Fraction::operator=(const Fraction& other)
{
    this->_numerator = other._numerator;
    this->_denominator = other._denominator;

    return *this;
}

Fraction Fraction::operator+(llint value)
{
    Fraction result(*this);

    result._numerator += (value * result._denominator);
    result.__simplify();

    return result;
}

Fraction Fraction::operator+(const Fraction& other)
{
    Fraction result;
    result.setNumerator(
        this->_numerator * other._denominator +
        other._numerator * this->_denominator
    );
    result.setDenominator(
        this->_denominator * other._denominator
    );
    if (result._denominator == 0)
        throw std::logic_error("zero division error");

    result.__simplify();

    return result;
}

Fraction Fraction::operator*(llint value)
{
    Fraction result(*this);
    result._numerator *= value;
    result.__simplify();

    return result;
}

Fraction Fraction::operator*(const Fraction& other)
{
    Fraction result(
        this->_numerator * other._numerator,
        this->_denominator * other._denominator
    );
    result.__simplify();

    return result;
}

Fraction Fraction::operator-(llint value)
{
    Fraction result(*this + (-1 * value));
    return result;
}

Fraction Fraction::operator-(const Fraction& other)
{
    Fraction result(*this + (Fraction(
        other._numerator, other._denominator
    ) * -1));
    return result;
}

Fraction Fraction::operator/(llint value)
{
    if (value == 0)
        throw std::logic_error("zero division error");

    Fraction result(
        this->_numerator,
        this->_denominator * value
    );
    result.__simplify();

    return result;
}

Fraction Fraction::operator/(const Fraction& other)
{
    Fraction result(
        this->_numerator * other._denominator,
        this->_denominator * other._numerator
    );
    result.__simplify();

    return result;
}

Fraction& Fraction::operator+=(llint value)
{
    *this = *this + value;
    return *this;
}

Fraction& Fraction::operator+=(const Fraction& other)
{
    *this = *this + other;
    return *this;
}

Fraction& Fraction::operator*=(llint value)
{
    *this = *this * value;
    return *this;
}

Fraction& Fraction::operator*=(const Fraction& other)
{
    *this = *this * other;
    return *this;
}

Fraction& Fraction::operator-=(llint value)
{
    *this = *this - value;
    return *this;
}

Fraction& Fraction::operator-=(const Fraction& other)
{
    *this = *this - other;
    return *this;
}

Fraction& Fraction::operator/=(llint value)
{
    *this = *this / value;
    return *this;
}

Fraction& Fraction::operator/=(const Fraction& other)
{
    *this = *this / other;
    return *this;
}

bool Fraction::operator==(llint value)
{
    if (this->_denominator != 1 || this->_numerator != value)
        return false;

    return true;
}

bool Fraction::operator==(const Fraction& other)
{
    if (this->_numerator != other._numerator 
        || this->_denominator != other._denominator)
        return false;

    return true;
}

bool Fraction::operator!=(llint value)
{
    return !(*this == value);
}

bool Fraction::operator!=(const Fraction& other)
{
    return !(*this == other);
}

Fraction& Fraction::operator++()
{
    return ((*this) += 1);
}

Fraction& Fraction::operator--()
{
    return ((*this) -= 1);
}

llint Fraction::Numerator()
{
    return this->_numerator;
}

llint Fraction::Denominator()
{
    return this->_denominator;
}

double Fraction::Float()
{
    return (
        static_cast<double>(this->_numerator) /
        static_cast<double>(this->_denominator)
    );
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

    if (this->_denominator < 0)
    {
        this->_denominator *= -1;
        this->_numerator *= -1;
    }
}