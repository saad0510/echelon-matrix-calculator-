/*
Author : Saad Bin Khalid
Contact: k200161@nu.edu.pk
Last update: 26 September, 2021
*/

#pragma once
#include "Row.h"
using namespace std;

// A structure to hold attributes of an element of a matrix
struct Element
{
    // the fraction value of element
    Fraction frac = 0;
    // the row number of element
    unsigned row = 0;
    // the column number of element
    unsigned col = 0;
};

/**
 * A class to implement the working of a general matrix.
 * It supports all workings of a matrix.
 */
class Matrix
{
    //? frind functions:
    /**
     * To display the Matrix in a formatted fashion.
     * @param ostream The output stream to write to.
     * @param Row The Matrix to display.
     * @return The same output stream for cascading the function call.
     */
    friend ostream &operator<<(ostream &os, const Matrix &matrix);

public:
    // the body to hold rows of matrix
    Row *body = nullptr;
    // the number of of matrix
    unsigned rows = 0;
    // the number of columns of matrix
    unsigned cols = 0;
    // a flag to control the ouput of each step
    bool steps = false;

    //? private functions:
    /**
     * To allocate memory for rows of the matrix
     * @param int the number of rows.
     * @return void
     */
    void allocateRows(const int &rows);
    /**
     * To allocate memory for columns of the matrix
     * @param int the number of columns.
     * @param Fraction[][] the elements of matrix.
     * @return void
     */
    void allocateColumns(const int &cols, Fraction *fractions[]);
    /**
     * To deallocate memory for matrix.
     * @param void.
     * @return void.
     */
    void deallocateMatrix();

public:
    //? constructors and destructor:
    // to initialize the matrix of given dimensions with the given Fractions
    Matrix(const int &rows, const int &cols, Fraction **fractions);
    // to destroy the matrix when exiting
    ~Matrix();

    //? access modifiers:
    /**
     * To fill the specified number of rows with given fraction.
     * @param int number of rows.
     * @param Fraction the source fraction.
     * @return void
     */
    void fillRow(const int &row, const Fraction &frac);
    /**
     * To fill all rows with given fraction.
     * @param Fraction the source fraction.
     * @return void
     */
    void fill(const Fraction &frac);

    //? EROs (Elementary row operations):
    /**
     * To add the source row into destination row after multiplying it a by a factor, if any.
     * @param int destination row.
     * @param int source row.
     * @param Fraction the factor (by default, it is 1).
     * @return void
     */
    void add(const int &rowDest, const int &rowSrc, const Fraction &multiplier = 1);
    /**
     * To multiply the specified row by given factor.
     * @param int row number.
     * @param Fraction the factor.
     * @return void
     */
    void multiply(const int &row, const Fraction &factor);
    /**
     * To divide the specified row by given fraction.
     * @param int row number.
     * @param Fraction the fraction.
     * @return void
     */
    void divide(const int &row, const Fraction &factor);
    /**
     * To interchange two rows.
     * @param int row1 number.
     * @param int row2 number.
     * @return void
     */
    void change(const int &row1, const int &row2);

    //? helper functions:
    /**
     * To sort matrix rows according to their number of starting 0s.
     * @param void
     * @return void
     */
    void sortRows();
    /**
     * To transform current matrix into echelon form.
     * @param bool an indicator to control transformation to reduced echelon form
     * @return void
     */
    void toEchelon(const bool &reduced = false);
    /**
     * To show steps whenever the matrix is transformed to a new state
     * @param bool a flad to control ouptut
     * @return void
     */
    void showSteps(const bool &show)
    {
        this->steps = show;
    }
};

// todo: copy constructor
// todo: operater overloading