/*
Author : Saad Bin Khalid
Contact: k200161@nu.edu.pk
Last update: 26 September, 2021
*/

#pragma once
#include "Fraction.h"
using namespace std;

/**
 * A class to implement the working of a row of a matrix.
 * It can also be used as an alternative to dynamic safe array.
 * It uses 'Fractions' as its elements .
 */
class Row
{
    //? friend functions:
    /**
     * To display the row in a formatted fashion.
     * @param ostream The output stream to write to.
     * @param Row The row to display.
     * @return The same output stream for cascading the function call.
     */
    friend ostream &operator<<(ostream &os, const Row &row);
    /**
     * To input the row from an input stream  .
     * @param istream The input stream to read from.
     * @param Fraction The row to initialize.
     * @return The same input stream for cascading the function call.
     */
    friend istream &operator>>(istream &is, Row &row);

private:
    // The maximum capacity of the row.
    // Fractions cannot exceed this length.
    unsigned capacity = 0;
    // The current length occupied by the elements of row.
    // It never exceeds the 'capacity' of the row.
    unsigned length = 0;
    // The pointer to elements of row.
    // The elements are implements using 'Fraction.h'.
    Fraction *elements = nullptr;

    //? private functions:
    /**
     * To allocate memory for the elements of row.
     * @param int the maximum capacity of the row.
     * @return void
     */
    void allocate(const int &capacity);
    /**
     * To deallocate memory of row.
     * @param void
     * @return void
     */
    void deallocateRow();

public:
    //? constructors and destructor:
    // To initialize the default row as an empty row.
    Row();
    // To initialize the row by memory only.
    // No elements are inserted.
    Row(const int &capacity);
    // To initialize the row from a list of fractions.
    Row(const int &capacity, Fraction fractions[]);
    // To initialize the row from another row.
    Row(const Row &other);
    // To destroy the row when exiting.
    ~Row();

    //? access modifiers:
    /**
     * To insert an element at the end of row.
     * @param Fraction the fraction to be inserted (also supports numeric values).
     * @return The index of inserted element.
     */
    int push(const Fraction &fraction);
    /**
     * To remove an element from the end of row.
     * @param void
     * @return The removed Fraction.
     */
    Fraction pop();
    /**
     * To return the maximum available capacity of row.
     * @param void
     * @return The capacity.
     */
    unsigned getCapacity() const;
    /**
     * To return the length of row which is currently used by elements.
     * @param void
     * @return The length.
     */
    unsigned getLength() const;
    /**
     * To populate the row from given Fractions.
     * The previous elements of the row are overriden.
     * @param int the number of fractions to be inserted.
     * @param values[] the list of fractions to insert from.
     * @return void
     */
    void setFractions(const int &length, Fraction fractions[]);
    /**
     * To fill the specified elements of row with the given Fraction.
     * The previous elements of the row are overriden.
     * @param int the number of elements to override.
     * @param Fraction the fraction to fill.
     * @return void
     */
    void fillRow(const int &length, const Fraction &fraction);
    /**
     * To remove all elements of row.
     * The resulting row is now empty, but it still retains its capacity.
     * @param void
     * @return void
     */
    void clear();

    //? helpers
    /**
     * To return the number of starting 0s.
     * @param void
     * @return The number of elements after starting zeros.
     */
    unsigned startingZeroCount() const;

    //? operators:
    /**
     * To fill all elements with a new fraction.
     * @param Fraction the source fraction.
     * @return A reference to the current row for cascading function calls .
     */
    Row &operator=(const Fraction &frac);
    /**
     * To assign a new row to the current row.
     * @param Row the source row.
     * @return A reference to the current row for cascading function calls .
     */
    Row &operator=(const Row &other);
    /**
     * To find the sum of two rows.
     * @param Row the second row.
     * @return The sum of two rows.
     */
    Row operator+(const Row &other) const;
    /**
     * To add a row into the current row (element-wise).
     * @param Row the second row.
     * @return A reference to the current row for cascading function calls .
     */
    Row &operator+=(const Row &other);
    /**
     * To find the difference of two rows.
     * @param Row the second row.
     * @return The difference of two rows.
     */
    Row operator-(const Row &other) const;
    /**
     * To subtract a row from the current row (element-wise).
     * @param Row the second row.
     * @return A reference to the current row for cascading function calls .
     */
    Row &operator-=(const Row &other);
    /**
     * To find the product of a row and a fraction.
     * @param Fraction the source fraction.
     * @return The product row whose each element is a [element*fraction].
     */
    Row operator*(const Fraction &frac) const;
    /**
     * To multiply every element of row by a Fraction.
     * @param Fraction the source fraction.
     * @return A reference to the current row for cascading function calls .
     */
    Row &operator*=(const Fraction &frac);
    /**
     * To find the division of a row and a fraction.
     * @param Fraction the source fraction.
     * @return The resulting row whose each element is a [element/fraction].
     */
    Row operator/(const Fraction &frac) const;
    /**
     * To divide every element of row by a Fraction.
     * @param Fraction the source fraction.
     * @return A reference to the current row for cascading function calls .
     */
    Row &operator/=(const Fraction &frac);
    /**
     * To compare two rows.
     * @param Row the second row.
     * @return True if both rows are equal; otherwise, false.
     */
    bool operator==(const Row &other) const;
    /**
     * To compare two rows.
     * @param Row the second row.
     * @return false if both rows are equal; otherwise, true.
     */
    bool operator!=(const Row &other) const;
    /**
     * To acces an element of row.
     * @param int the index of element.
     * @return the Fraction element at the index, if any.
     */
    Fraction operator[](const int &index) const;
};