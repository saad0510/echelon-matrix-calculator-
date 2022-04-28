/*
Author : Saad Bin Khalid
Contact: k200161@nu.edu.pk
Last update: 26 September, 2021
*/

#include <iostream>
#include <fstream>
#include <exception>
#include "includes/Matrix.h"

using namespace std;

int main()
{
    // opening the input file
    ifstream inputFile = ifstream("input.txt");
    if (!inputFile.is_open())
        throw runtime_error("Exception: Input file not found. Try again.");

    // reading the dimensions of matrix
    unsigned rows = 0;
    unsigned cols = 0;
    inputFile >> rows >> cols;
    // allocate memory for the matrix
    Fraction **matrix = new Fraction *[rows];
    for (unsigned i = 0; i < rows; i++)
        matrix[i] = new Fraction[cols];

    // reading the elements
    for (unsigned row = 0; row < rows; row++)
    {
        for (unsigned col = 0; col < cols; col++)
        {
            double x;
            inputFile >> x;
            matrix[row][col] = Fraction(x);

            if (inputFile.eof())
            {
                row = rows; // to break outer loop
                break;
            }
        }
    }

    // declaring the Matrix
    Matrix m(rows, cols, matrix);

    // add this line if you want to see each step
    // m.showSteps(true);

    cout << "* Original Matrix:\n"
         << m << "\n";

    m.toEchelon();
    cout << "* Echelon Form:\n"
         << m << "\n";

    // pass true to transform to reduce form
    m.toEchelon(true);
    cout << "* Reduced Echelon Form:\n"
         << m << "\n";

    // deallocating memory
    for (unsigned i = 0; i < rows; i++)
        delete[] matrix[i];
    delete[] matrix;
    return 0;
}
