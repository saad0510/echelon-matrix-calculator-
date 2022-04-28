/*
Author : Saad Bin Khalid
Contact: k200161@nu.edu.pk
Last update: 26 September, 2021
*/


#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <math.h>
#include <exception>
using namespace std;

/**
 * A class to implement the working of fractions in Math.
 * Supports all arithmetic functions applicable to traditional fractions.
 * Any numeric value is convertible to Fraction object
 */
class Fraction
{
    //? friend functions:
    /**
     * To display the fraction in a formatted fashion.
     * @param ostream The output stream to write to.
     * @param Fraction The fraction to display.
     * @return The same output stream for cascading the function call.
     */
    friend ostream &operator<<(ostream &os, const Fraction &other);
    /**
     * To input the fraction from an input stream.
     * @param istream The input stream to read from.
     * @param Fraction The fraction to initialize.
     * @return The same input stream for cascading the function call.
     */
    friend istream &operator>>(istream &is, Fraction &other);

private:
    // The numerator of the fraction.
    int numerator;
    // The denominator of the fraction.
    int denominator;

    //? private functions:
    /**
     * To find the greatest common divisor (GCD) of two numbers.
     * @param int number 1.
     * @param int number 2.
     * @return the GCD of the numbers.
     */
    int gcd(int a, int b) const;

public:
    //? constructor and destructor:
    // To initialize the default value of fraction as 0.
    Fraction();
    // To initialize the value of fraction from a number.
    Fraction(const int &value);
    // To initialize the value of fraction.
    Fraction(const int &numerator, const int &denominator);
    // To initialize the value of fraction from another fraction.
    Fraction(const Fraction &other);

    //? access modifiers:
    /**
     * To return the numerator of object.
     * @param void
     * @return The copy of this object's numerator.
     */
    int getNumerator() const;
    /**
     * To return the denominator of fraction.
     * @param void
     * @return The copy of this fraction's denominator.
     */
    int getDenominator() const;
    /**
     * To set the value of fraction.
     * @param int numerator of the fraction.
     * @param int denominator of the fraction.
     * @return void
     */
    void setValue(int numerator, int denominator);

    //? helper functions:
    /**
     * To reduce the fraction to a decimal value.
     * @param void.
     * @return The decimal equivalent of fraction.
     */
    double toDouble() const;
    /**
     * To transform the fraction into a formatted string.
     * @param void.
     * @return The string representation of fraction.
     */
    string toString() const;

    //? operator overloading :
    /**
     * To assign a new fraction to the current fraction.
     * @param Fraction the source fraction.
     * @return A reference to the current fraction for cascading function calls .
     */
    Fraction &operator=(const Fraction &other);
    /**
     * To sum two fractions.
     * @param Fraction the second fraction.
     * @return The sum of fractions.
     */
    Fraction operator+(const Fraction &other) const;
    /**
     * To add a fraction in the current fraction.
     * @param Fraction the second fraction.
     * @return A reference to the current fraction for cascading function calls.
     */
    Fraction &operator+=(const Fraction &other);
    /**
     * To subtract two fractions.
     * @param Fraction the second fraction.
     * @return The difference between the fractions.
     */
    Fraction operator-(const Fraction &other) const;
    /**
     * To subtract a fraction from the current fraction.
     * @param Fraction the second fraction.
     * @return A reference to the current fraction for cascading function calls. 
     */
    Fraction &operator-=(const Fraction &other);
    /**
     * To multiply two fractions.
     * @param Fraction the second fraction.
     * @return The product of fractions.
     */
    Fraction operator*(const Fraction &other) const;
    /**
     * To multiply a fraction with the current fraction.
     * @param Fraction the second fraction.
     * @return A reference to the current fraction for cascading function calls.
     */
    Fraction &operator*=(const Fraction &other);
    /**
     * To divide two fractions.
     * @param Fraction the second fraction.
     * @return The result of division of fractions.
     */
    Fraction operator/(const Fraction &other) const;
    /**
     * To divide a fraction with the current fraction.
     * @param Fraction the second fraction.
     * @return A reference to the current fraction for cascading function calls.
     */
    Fraction &operator/=(const Fraction &other);
    /**
     * To compare two fractions.
     * @param Fraction the second fraction.
     * @return True if both fractions are equal; otherwise, false.
     */
    bool operator==(const Fraction &other) const;
    /**
     * To compare two fractions.
     * @param Fraction the second fraction.
     * @return True if both fractions are not equal; otherwise, false.
     */
    bool operator!=(const Fraction &other) const;
};