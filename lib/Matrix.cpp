/*
Author : Saad Bin Khalid
Contact: k200161@nu.edu.pk
Last update: 26 September, 2021
*/

#include "../includes/Matrix.h"

//? constructors and destructor:

Matrix::Matrix(const int &rows, const int &cols, Fraction **fractions)
{
    allocateRows(rows);
    allocateColumns(cols, fractions);
}

Matrix::~Matrix()
{
    deallocateMatrix();
}

//? private functions:

void Matrix::allocateRows(const int &rows)
{
    if (rows <= 0)
        throw range_error("The number of rows must be greater than 0");

    this->rows = rows;
    this->body = new Row[rows];
}

void Matrix::allocateColumns(const int &cols, Fraction *fractions[])
{
    if (cols <= 0)
        throw range_error("The number of cols must be greater than 0");

    this->cols = cols;
    for (unsigned i = 0; i < this->rows; i++)
        body[i] = Row(cols, fractions[i]);
}

void Matrix::deallocateMatrix()
{
    delete[] body;
    this->rows = 0;
    this->cols = 0;
}

//? access modifiers:

void Matrix::fillRow(const int &row, const Fraction &frac)
{
    if (row <= 0 || row > this->rows)
        throw out_of_range("The row to be filled is out of range ");

    body[row - 1].clear();
    body[row - 1].fillRow(this->cols, frac);
}
void Matrix::fill(const Fraction &frac)
{
    for (unsigned i = 0; i < this->rows; i++)
        fillRow(i, frac);
}

//? EROs (Elementary row operations):

void Matrix::add(const int &rowDest, const int &rowSrc, const Fraction &multiplier)
{
    if (rowDest <= 0 || rowDest > this->rows)
        throw out_of_range("The destination row is out of range");
    if (rowSrc <= 0 || rowSrc > this->rows)
        throw out_of_range("The source row is out of range");

    body[rowDest - 1] += body[rowSrc - 1] * multiplier;
}

void Matrix::multiply(const int &row, const Fraction &factor)
{
    if (row <= 0 || row > this->rows)
        throw out_of_range("The row is out of range");

    body[row - 1] *= factor;
}

void Matrix::divide(const int &row, const Fraction &factor)
{
    if (row <= 0 || row > this->rows)
        throw out_of_range("The row is out of range");

    body[row - 1] /= factor;
}

void Matrix::change(const int &row1, const int &row2)
{
    if (row1 <= 0 || row1 > this->rows)
        throw out_of_range("The row is out of range");
    if (row2 <= 0 || row2 > this->rows)
        throw out_of_range("The row is out of range");

    Row row1Copy(body[row1 - 1]);
    body[row1 - 1] = body[row2 - 1];
    body[row2 - 1] = row1Copy;
}

//? helper functions:

void Matrix::sortRows()
{
    for (unsigned pass = 1; pass < rows; pass++)
    {
        for (unsigned i = 0; i < rows - 1; i++)
        {
            unsigned currRow = body[i].startingZeroCount();
            unsigned nextRow = body[i + 1].startingZeroCount();

            if (currRow > nextRow)
            {
                change(i + 1, i + 2);
                if (this->steps)
                {
                    cout << "Change R" << i + 1 << " with R" << i + 2 << "\n";
                    cout << *this << "\n";
                }
            }
            // if equal num of levels, change to put 1 on the top
            else if (currRow == nextRow)
            {
                // skip if there is no nonzero values in the row
                if (currRow >= this->cols || nextRow >= this->cols)
                    continue;

                // checking the first non zero values
                if (body[i][currRow] != 1 && body[i][nextRow] == 1)
                {
                    change(i + 1, i + 2);
                    if (this->steps)
                    {
                        cout << "Change R" << i + 1 << " with R" << i + 2 << "\n";
                        cout << *this << "\n";
                    }
                }
            }
        }
    }
}

void Matrix::toEchelon(const bool &reduced)
{
    // array to hold target elements of each column
    // target element is the element after which all elements are 0
    Element targetElements[cols];

    // maximum row of the target elements
    unsigned maxRow = 0;
    // maximum col of the target elements
    unsigned maxCol = 0;

    // sorting the rows
    sortRows();

    // iterating through the matrix column-wise
    for (unsigned col = 0; col < cols; col++)
    {
        Element &target = targetElements[col];
        for (unsigned row = 0; row < rows; row++)
        {
            const Fraction element = body[row][col];
            // skip if element is 0
            if (element == 0)
                continue;
            // if it is the first column
            if (col == 0)
            {
                target.row = row + 1;
                target.col = col + 1;
                target.frac = element;
                break;
            }

            // if the element is to the far right of the previous target elements
            const Element &prevTarget = targetElements[col - 1];
            if (col > (prevTarget.col - 1) && row > (prevTarget.row - 1))
            {
                target.row = row + 1;
                target.col = col + 1;
                target.frac = element;
                break;
            };
            // if there is no taget element in this column
            target.frac = 0;
            target.row = rows;
            target.col = cols;
        }

        // transforming the matrix
        if (target.frac != 0)
        {
            // make target value 1
            if (target.frac != 1)
            {
                divide(target.row, target.frac);
                if (this->steps)
                {
                    cout << "Dividing R" << target.row << " by " << target.frac << endl;
                    cout << *this << "\n";
                }
            }

            // determine whether the result should be a reduced echelon or not
            const unsigned startingRow = reduced ? 0 : target.row;
            // make all elements of the column 0
            for (unsigned row = startingRow; row < rows; row++)
            {
                const Fraction oldVal = body[row][col];
                const Fraction newVal = oldVal * -1;

                // skip the element if it is the target element
                if (row == target.row - 1)
                    continue;
                // skip the element if it is already 0
                if (oldVal == 0)
                    continue;

                add(row + 1, target.row, newVal);

                if (this->steps)
                {
                    cout << "Adding " << newVal << "*R" << target.row << " in R" << row + 1 << endl;
                    cout << *this << "\n";
                }
            }
        }
    }
}

//? friend functions:

ostream &operator<<(ostream &os, const Matrix &matrix)
{
    for (unsigned row = 0; row < matrix.rows; row++)
        os << matrix.body[row] << "\n";
    return os;
}