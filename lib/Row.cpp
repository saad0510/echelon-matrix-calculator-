/*
Author : Saad Bin Khalid
Contact: k200161@nu.edu.pk
Last update: 26 September, 2021
*/

#include "../includes/Row.h"

//? constructors and destrutor:

Row::Row() = default;

Row::Row(const int &capacity)
{
    allocate(capacity);
}

Row::Row(const int &capacity, Fraction fractions[])
{
    allocate(capacity);
    setFractions(capacity, fractions);
}

Row::Row(const Row &other)
{
    allocate(other.capacity);
    setFractions(other.capacity, other.elements);
}

Row::~Row()
{
    deallocateRow();
}

//? private functions:

void Row::allocate(const int &capacity)
{
    if (capacity <= 0)
        throw out_of_range("The capacity must be a greater than 0");

    this->length = 0;
    this->capacity = capacity;
    this->elements = new Fraction[capacity];
}

void Row::deallocateRow()
{
    delete[] this->elements;
    this->elements = nullptr;
    this->length = 0;
    this->capacity = 0;
}

//? access modifiers:

int Row::push(const Fraction &fraction)
{
    // if row is already full
    if (this->length == this->capacity)
        throw overflow_error("The row is already full");

    const unsigned newIndex = this->length++;
    elements[newIndex] = fraction;
    return newIndex;
}

Fraction Row::pop()
{
    // if row is already empty
    if (this->length == 0)
        throw underflow_error("The row is already empty");

    return elements[--length];
}

unsigned Row::getCapacity() const
{
    return capacity;
}

unsigned Row::getLength() const
{
    return length;
}

void Row::setFractions(const int &length, Fraction fractions[])
{
    if (length <= 0)
        throw underflow_error("The specified length should be greater than 0");
    if (length > this->capacity)
        throw overflow_error("The specified length is more than the available capacity");

    this->length = 0;
    for (unsigned i = 0; i < length; i++)
        push(fractions[i]);
}

void Row::fillRow(const int &length, const Fraction &fraction)
{
    if (length <= 0)
        throw underflow_error("The specified length should be greater than 0");
    if (length > this->capacity)
        throw overflow_error("The specified length is more than the available capacity");

    this->length = 0;
    for (unsigned i = 0; i < length; i++)
        push(fraction);
}

void Row::clear()
{
    this->length = 0;
}

//? helper functions:

unsigned Row::startingZeroCount() const
{
    unsigned count;
    for (count = 0; count < this->length; count++)
        if (elements[count] != 0)
            break;
    return count;
}

//? operations:

Row &Row::operator=(const Fraction &frac)
{
    fillRow(this->length, Fraction(frac));
    return *this;
}

Row &Row::operator=(const Row &other)
{
    if (other.capacity != this->capacity)
    {
        deallocateRow();
        allocate(other.capacity);
    }
    setFractions(other.capacity, other.elements);
    return *this;
}

Row Row::operator+(const Row &other) const
{
    if (this->capacity != other.capacity)
        throw runtime_error("In order to add two rows, there capacity must be same");

    Row temp(this->capacity);
    for (unsigned col = 0; col < this->capacity; col++)
        temp.push(elements[col] + other.elements[col]);
    return temp;
}

Row &Row::operator+=(const Row &other)
{
    if (this->capacity != other.capacity)
        throw runtime_error("In order to add two rows, there capacity must be same");

    for (unsigned i = 0; i < this->length; i++)
        elements[i] += other.elements[i];
    return *this;
}

Row Row::operator-(const Row &other) const
{
    if (this->capacity != other.capacity)
        throw runtime_error("In order to subtract two rows, there capacity must be same");

    Row temp(this->capacity);
    for (unsigned col = 0; col < this->capacity; col++)
        temp.push(elements[col] - other.elements[col]);
    return temp;
}

Row &Row::operator-=(const Row &other)
{
    if (this->capacity != other.capacity)
        throw runtime_error("In order to subtract two rows, there capacity must be same");

    for (unsigned i = 0; i < this->length; i++)
        elements[i] -= other.elements[i];
    return *this;
}

Row Row::operator*(const Fraction &frac) const
{
    Row temp(this->capacity);
    for (unsigned col = 0; col < this->capacity; col++)
        temp.push(elements[col] * frac);
    return temp;
}

Row &Row::operator*=(const Fraction &frac)
{
    for (unsigned i = 0; i < this->length; i++)
        elements[i] *= frac;
    return *this;
}

Row Row::operator/(const Fraction &frac) const
{
    Row temp(this->capacity);
    for (unsigned col = 0; col < this->capacity; col++)
        temp.push(elements[col] / frac);
    return temp;
}

Row &Row::operator/=(const Fraction &frac)
{
    for (unsigned i = 0; i < this->length; i++)
        elements[i] /= frac;
    return *this;
}

bool Row::operator==(const Row &other) const
{
    if (this->capacity != other.capacity)
        throw runtime_error("In order to compare two rows, there capacity must be same");

    bool areEqual = true;
    for (unsigned col = 0; col < this->capacity; col++)
    {
        if (elements[col] != other.elements[col])
        {
            areEqual = false;
            break;
        }
    }
    return areEqual;
}

bool Row::operator!=(const Row &other) const
{
    return !(*this == other);
}

Fraction Row::operator[](const int &index) const
{
    if (index < 0 || index >= this->length)
        throw out_of_range("The index is out of range of the available length");
    return elements[index];
}

//? friend functions:

ostream &operator<<(ostream &os, const Row &row)
{
    os << "[";
    for (unsigned col = 0; col < row.length; col++)
    {
        os << setw(10);
        os << row.elements[col];
        os << setw(4);
    }
    os << "]";
    return os;
}
istream &operator>>(istream &is, Row &row)
{
    for (unsigned col = 0; col < row.getCapacity(); col++)
    {
        is >> row.elements[col];
    }
    return is;
}