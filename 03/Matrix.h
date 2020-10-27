#include <cstdlib>
#include <iostream>
#include <fstream>

#ifndef MATRIX_H
#define MATRIX_H

class MatrixRow {
public:
    MatrixRow();
    MatrixRow(const int columns);
    ~MatrixRow();
    const int &operator[](const int index) const;
    int &operator[](const int index);

    friend class Matrix;

private:
    int *matrix;
    void sizeException(const int value) const;
    int Columns;

    int getColumns() const;

    MatrixRow &operator *=(const int value);
    MatrixRow &operator =(const MatrixRow &value);
    MatrixRow operator +(const MatrixRow &value);
    bool operator ==(const MatrixRow &value) const;
    bool operator !=(const MatrixRow &value) const;
    void printMatrix(std::ostream &fout) const;
};

class Matrix {
public:
    Matrix(const int rows, const int columns);
    Matrix(const Matrix &value);
    ~Matrix();
    int getColumns() const;
    int getRows() const;

    Matrix &operator *=(const int value);
    Matrix &operator =(const Matrix &value);
    const MatrixRow &operator [](const int index) const;
    MatrixRow &operator [](const int index);
    Matrix operator +(const Matrix &value) const;
    bool operator ==(const Matrix &value) const;
    bool operator !=(const Matrix &value) const;
    void printMatrix(std::ostream &fout) const;
private:
    MatrixRow *matrix;
    void sizeException(const int value) const;
    int Columns;
    int Rows;
};

#endif
