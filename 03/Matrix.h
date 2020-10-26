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
    int &operator[](const int index) const;

    friend class Matrix;

private:
    int *matrix;
    void sizeException(const int value) const;
    int Columns;

    int getColumns() const;

    const MatrixRow &operator *=(const int value);
    const MatrixRow &operator =(const MatrixRow &value);
    const MatrixRow operator +(const MatrixRow &value) const;
    bool operator ==(const MatrixRow &value) const;
    bool operator !=(const MatrixRow &value) const;
    void printMatrix(std::ostream &fout) const;
};

class Matrix {
public:
    Matrix(const int rows, const int columns);
    ~Matrix();
    int getColumns() const;
    int getRows() const;

    const Matrix &operator *=(const int value);
    const Matrix &operator =(const Matrix &value);
    MatrixRow &operator[](const int index) const;
    const Matrix operator +(const Matrix &value) const;
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
