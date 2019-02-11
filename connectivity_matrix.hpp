#ifndef ASG1_MATRIX_H
#define ASG1_MATRIX_H

#include <algorithm>

using namespace std;

constexpr double p = 0.85;

class Matrix {
private:
    int rowSize;
    int colSize;
    double **matrix;

public:
    Matrix();
    Matrix(int n);
    Matrix(int r, int c);
    Matrix(double arr[], int size);
    ~Matrix();

    void getImportance();
    void getTeleportation();
    double getSum();
    void printFormattedResult();

    void set_value(int row, int col, double value);
    double get_value(int row, int col);
    void clear();

    friend ostream& operator<<(ostream& stream, const Matrix& obj);
    friend bool operator==(const Matrix& obj1, const Matrix& obj2);
    friend bool operator!=(const Matrix& obj1, const Matrix& obj2);

    void operator++(int n);
    friend void operator--(Matrix& obj, int n);

    void operator+=(Matrix &obj);
    void operator-=(Matrix &obj);
    friend Matrix operator+(Matrix &obj1, Matrix &obj2);
    friend Matrix operator-(Matrix &obj1, Matrix &obj2);

    Matrix &operator=(Matrix obj);
    friend void mySwap(Matrix& obj1, Matrix& obj2);

    void operator*=(double num);
    void operator*=(Matrix &obj);
    friend Matrix operator*(Matrix &obj1, Matrix &obj2);
};

#endif //ASG1_MATRIX_H
