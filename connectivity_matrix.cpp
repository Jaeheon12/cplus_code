#include <iomanip>
#include <iostream>
#include <math.h>

using namespace std;

#include "page_rank.hpp"
#include "connectivity_matrix.hpp"

/***
 *
 * Default Constructor
 *
 * Programmer : Jaeheon Jung
 * Date : 02/FEB/2019
 */
Matrix::Matrix() {
    rowSize = 1;
    colSize = 1;

    matrix = NULL;
}

/***
 * Parameterized Constructor
 *
 * Parameter n : int - the number of rows and columns of the matrix
 *
 * This constructor generates a matrix where all values are 0 with n rows and n columns
 *
 * Programmer : Jaeheon Jung
 * Date : 02/FEB/2019
 */
Matrix::Matrix(int n) {
    rowSize = n;
    colSize = n;

    try  {
        if (n <= 0)
            throw n;
    }
    catch (int x)  {
        cout << "The row and column of the matrix must be more than 0." << endl;
        cout << "Found : row : " << n << ", col : " << n << endl;
        exit(1);
    }


    matrix = new double*[n];

    for(int i = 0; i < n; i++) {
        matrix[i] = new double[n];
        for(int j = 0; j < n; j++) {
            matrix[i][j] = 0.00;
        }
    }
}

/***
 * Parameterized Constructor
 *
 * Parameter r : int - the number of rows of the matrix
 * Parameter c : int - the number of columns of the matrix
 *
 * This constructor generates a matrix where all values are 0 with r rows and c columns
 *
 * Programmer : Jaeheon Jung
 * Date : 02/FEB/2019
 */
Matrix::Matrix(int r, int c) {
    try  {
        if (r <= 0)
            throw r;
        if (c <= 0)
            throw c;
    }
    catch (int x)  {
        cout << "The row and column of the matrix must be more than 0." << endl;
        cout << "Found : row : " << r << ", col : " << c << endl;
        exit(1);
    }

    rowSize = r;
    colSize = c;

    matrix = new double*[r];
    for(int i = 0; i < r; i++) {
        matrix[i] = new double[c];
        for(int j = 0; j < c; j++) {
            matrix[i][j] = 0.00;
        }
    }
}

/***
 * Parameterized Constructor
 *
 * Parameter arr : a pointer to an array of double - this 1d array becomes 2d array matrix
 * Parameter size : int - the size of the array - must be square. 1x1, or 2x2, or 3x3, etc..
 *
 * This constructor generates a matrix where all values are 0 with r rows and c columns
 *
 * Programmer : Jaeheon Jung
 * Date : 02/FEB/2019
 */
Matrix::Matrix(double arr[], int size) {
    double sqrtedSize;
    try  {
        sqrtedSize = sqrt(size);
        if(sqrtedSize*sqrtedSize != size)
            throw size;
    }
    catch (int x)  {
        cout << "Error : the size of an array must be square. 1x1, or 2x2, or 3x3, etc... " << endl;
        cout << "Found : " << size << endl;
        exit(1);
    }

    rowSize = sqrtedSize;
    colSize = sqrtedSize;

    int index = 0;
    matrix = new double*[rowSize];
    for(int i = 0; i < rowSize; i++) {
        matrix[i] = new double[colSize];
        for(int j = 0; j < colSize; j++) {
            matrix[i][j] = arr[index++];
        }
    }
}

/***
 * Destructor
 *
 * This destructor frees memory where member variable matrix has been allocated
 *
 * Programmer : Jaeheon Jung
 * Date : 02/FEB/2019
 */
Matrix::~Matrix() {
    for(int i = 0; i < rowSize; i++) {
        delete matrix[i];
    }
    delete matrix;
}

/***
 * getImportance()
 *
 * This function gets the importance of the matrix by dividing each value by the sum of each column's value
 *
 * Programmer : Jaeheon Jung
 * Date : 02/FEB/2019
 */
void Matrix::getImportance() {
    int numCols;
    for(int i = 0; i < colSize; i++) {
        numCols = 0;
        for(int j = 0; j < rowSize; j++) {
            if (matrix[j][i] == 1) {
                numCols++;
            }
        }
        if (numCols > 0) {
            for (int j = 0; j < rowSize; j++) {
                matrix[j][i] /= numCols;
            }
        }

        if (i == colSize - 1) {
            for(int j = 0; j < rowSize; j++) {
                matrix[j][i] = 1/(double)rowSize;
            }
        }
    }
}

/***
 * getTeleportation()
 *
 * This function gets the teleporation of the matrix by the number of webpages (row size in this case)
 *
 * Programmer : Jaeheon Jung
 * Date : 02/FEB/2019
 */
void Matrix::getTeleportation() {
    for (int i = 0; i < rowSize; i++) {
        for(int j = 0; j < colSize; j++) {
            matrix[i][j] = 1/(double)rowSize;
        }
    }
}

/***
 * getSum()
 *
 * This function gets the sum of each value in the matrix
 *
 * return the sum of each value in the matrix
 *
 * Programmer : Jaeheon Jung
 * Date : 02/FEB/2019
 */
double Matrix::getSum() {
    double sum = 0;
    for (int i = 0; i < rowSize; i++) {
        for(int j = 0; j < colSize; j++) {
            sum += matrix[i][j];
        }
    }
    return sum;
}

/***
 * printFormattedResult()
 *
 * This function gets formats the final version of Page Rank alogorithm matrix
 *
 * return the sum of each value in the matrix
 *
 * Programmer : Jaeheon Jung
 * Date : 02/FEB/2019
 */
void Matrix::printFormattedResult() {
    char page = 'A';
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            cout << fixed;
            cout << setprecision(2) << "Page " << page++ << " : " << setw(5) << (matrix[i][j]*100) << "%";
        }
        cout << endl;
    }
}

/***
 * set_value
 *
 * Parameter row : row number where value is changed
 * Parameter col : column number where value is changed
 * Parameter value : double - the value that replaces the original valye
 *
 * This function sets the value at the point where row and column match
 *
 * Programmer : Jaeheon Jung
 * Date : 02/FEB/2019
 */
void Matrix::set_value(int row, int col, double value) {
    try  {
        if ((row < 0 || row >= rowSize) || (col < 0 || col >= colSize)) {
            throw -1;
        }
    }
    catch (int x)  {
        cout << "Error : Out of Boundary" << endl;
        cout << "Found : row : " << row << ", col : " << col << endl;
        exit(1);
    }

    matrix[row][col] = value;
}

/***
 * get_value
 *
 * Parameter row : row number where value is changed
 * Parameter col : column number where value is changed
 *
 * return double - the value at the point where row and column match
 *
 * This function returns the value at the point where row and column match
 *
 * Programmer : Jaeheon Jung
 * Date : 02/FEB/2019
 */
double Matrix::get_value(int row, int col) {
    try  {
        if ((row < 0 || row >= rowSize) || (col < 0 || col >= colSize)) {
            throw -1;
        }
    }
    catch (int x)  {
        cout << "Error : Out of Boundary" << endl;
        cout << "Found : row : " << row << ", col : " << col << endl;
        exit(1);
    }
    return matrix[row][col];
}

/***
 * clear
 *
 * This function sets all values in the matrix with 0s
 *
 * Programmer : Jaeheon Jung
 * Date : 02/FEB/2019
 */
void Matrix::clear() {
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            matrix[i][j] = 0.0;
        }
    }
}

ostream& operator<<(ostream& stream, const Matrix& obj)  {
    for (int i = 0; i < obj.rowSize; i++) {
        for (int j = 0; j < obj.colSize; j++) {
            cout << "[" << setw(4) << obj.matrix[i][j] << "]";
        }
        cout << endl;
    }
    return stream;
}


bool operator==(const Matrix& obj1, const Matrix& obj2) {
    for (int i = 0; i < obj1.rowSize; i++) {
        for (int j = 0; j < obj1.colSize; j++) {
            double diff = obj1.matrix[i][j] - obj2.matrix[i][j];
            if (-0.00005 > diff || diff > 0.00005) {
                return false;
            }
        }
    }
    return true;
}

bool operator!=(const Matrix& obj1, const Matrix& obj2) {
    if (obj1 == obj2) {
        return false;
    }
    return true;
}

void Matrix::operator++(int n) {
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            matrix[i][j]++;
        }
    }
}

void operator--(Matrix& obj, int n) {
    for (int i = 0; i < obj.rowSize; i++) {
        for (int j = 0; j < obj.colSize; j++) {
            obj.matrix[i][j]--;
        }
    }
}

void Matrix::operator+=(Matrix &obj) {
    for (int i = 0; i < obj.rowSize; i++) {
        for (int j = 0; j < obj.colSize; j++) {
            matrix[i][j] += obj.matrix[i][j];
        }
    }
}

Matrix operator+(Matrix &obj1, Matrix &obj2) {
    Matrix tmp(obj1.rowSize, obj1.colSize);

    for (int i = 0; i < obj1.rowSize; i++) {
        for (int j = 0; j < obj1.colSize; j++) {
            tmp.matrix[i][j] = obj1.matrix[i][j] + obj2.matrix[i][j];
        }
    }
    return tmp;
}

void Matrix::operator-=(Matrix &obj) {
    for (int i = 0; i < obj.rowSize; i++) {
        for (int j = 0; j < obj.colSize; j++) {
            matrix[i][j] -= obj.matrix[i][j];
        }
    }
}

// m3 = (m2 - m1)
Matrix operator-(Matrix &obj1, Matrix &obj2) {
    Matrix tmp(obj1.rowSize, obj1.colSize);

    for (int i = 0; i < obj1.rowSize; i++) {
        for (int j = 0; j < obj1.colSize; j++) {
            tmp.matrix[i][j] = obj1.matrix[i][j] - obj2.matrix[i][j];
        }
    }
    return tmp;
}

void Matrix::operator*=(double num) {
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            matrix[i][j] *= num;
        }
    }
}

void Matrix::operator*=(Matrix &obj) {
    Matrix tmp(4);

    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            tmp.matrix[i][j] = 0;
            for (int z = 0; z < colSize; z++) {
                tmp.matrix[i][j] += matrix[i][z]*obj.matrix[z][j];
            }
        }
    }

    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            matrix[i][j] = tmp.matrix[i][j];

        }
    }
}

Matrix operator*(Matrix &obj1, Matrix &obj2) {
    Matrix mtrxToReturn(obj2.rowSize, obj2.colSize);
    Matrix tmp(4);

    for (int i = 0; i < obj1.rowSize; i++) {
        for (int j = 0; j < obj1.colSize; j++) {
            tmp.matrix[i][j] = 0;
            for (int z = 0; z < obj1.colSize; z++) {
                tmp.matrix[i][j] += obj1.matrix[i][z]*obj2.matrix[z][j];
            }
        }
    }

    for (int i = 0; i < obj2.rowSize; i++) {
        for (int j = 0; j < obj2.colSize; j++) {
            mtrxToReturn.matrix[i][j] = tmp.matrix[i][j];
        }
    }

    return mtrxToReturn;
}

Matrix &Matrix::operator=(Matrix obj) {
    mySwap(*this, obj);
    return *this;
}

void mySwap(Matrix &obj1, Matrix &obj2) {
    using std::swap;

    swap(obj1.rowSize, obj2.rowSize);
    swap(obj1.colSize, obj2.colSize);


    obj1.matrix = new double *[obj1.rowSize];
    for (int i = 0; i < obj1.rowSize; i++) {
        obj1.matrix[i] = new double[obj1.colSize];
        for (int j = 0; j < obj1.colSize; j++) {
            obj1.matrix[i][j] = 0.000;
        }
    }

    swap(obj1.matrix, obj2.matrix);
}
