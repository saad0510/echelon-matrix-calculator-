/*
Author : Saad Bin Khalid
Contact: k200161@nu.edu.pk
Last update: 26 September, 2021
*/

#include "../includes/Fraction.h"

//? constructor and destructor:

Fraction::Fraction()
{
    setValue(0, 1);
}

Fraction::Fraction(const int &value)
{
    setValue(value, 1);
}

Fraction::Fraction(const int &numerator, const int &denominator)
{
    setValue(numerator, denominator);
}

Fraction::Fraction(const Fraction &other)
{
    setValue(other.numerator, other.denominator);
}

//? private functions:

int Fraction::gcd(int a, int b) const
{
    int r;
    while (b > 0)
    {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

//? access modifiers:

int Fraction::getNumerator() const
{
    return numerator;
}

int Fraction::getDenominator() const
{
    return denominator;
}

void Fraction::setValue(int numerator, int denominator)
{
    // handling an undefined state
    if (denominator == 0)
    {
        throw logic_error("Denominator cannot be zero.");
    }
    else if (denominator < 0)
    {
        // transfer - sign to numerator
        numerator = -numerator;
        denominator = -denominator;
    }
    // simplifying the fraction
    int GCD = gcd(abs(numerator), abs(denominator));
    this->numerator = numerator / GCD;
    this->denominator = denominator / GCD;
}

//? helper functions:

double Fraction::toDouble() const
{
    return static_cast<double>(this->numerator) / this->denominator;
}

string Fraction::toString() const
{
    string s;
    s += to_string(this->numerator);
    if (this->denominator != 1)
    {
        s += "/";
        s += to_string(this->denominator);
    }
    return s;
}

//? operator overloading :

Fraction &Fraction::operator=(const Fraction &other)
{
    setValue(other.numerator, other.denominator);
    return *this;
}

Fraction Fraction::operator+(const Fraction &other) const
{
    const int num = this->numerator * other.denominator + this->denominator * other.numerator;
    const int denom = this->denominator * other.denominator;
    return Fraction(num, denom);
}

Fraction &Fraction::operator+=(const Fraction &other)
{
    *this = *this + other;
    return *this;
}

Fraction Fraction::operator-(const Fraction &other) const
{
    return *this + Fraction(-other.numerator, other.denominator);
}

Fraction &Fraction::operator-=(const Fraction &other)
{
    *this = *this - other;
    return *this;
}

Fraction Fraction::operator*(const Fraction &other) const
{
    return Fraction(numerator * other.numerator, denominator * other.denominator);
}

Fraction &Fraction::operator*=(const Fraction &other)
{
    // avoiding " *this = *this * other " to save some function calls
    setValue(numerator * other.numerator, denominator * other.denominator);
    return *this;
}

Fraction Fraction::operator/(const Fraction &other) const
{
    return Fraction(numerator * other.denominator, denominator * other.numerator);
}

Fraction &Fraction::operator/=(const Fraction &other)
{
    // avoiding " *this = *this / other " to save some functions' calls
    setValue(numerator * other.denominator, denominator * other.numerator);
    return *this;
}

bool Fraction::operator==(const Fraction &other) const
{
    return this->toDouble() == other.toDouble();
}

bool Fraction::operator!=(const Fraction &other) const
{
    return this->toDouble() != other.toDouble();
}

//? friend functions:

ostream &operator<<(ostream &os, const Fraction &other)
{
    os << other.toString();
    return os;
}
istream &operator>>(istream &is, Fraction &other)
{
    is >> other.numerator;
    is >> other.denominator;
    return is;
}