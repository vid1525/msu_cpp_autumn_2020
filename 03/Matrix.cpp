#include "Matrix.h"

MatrixRow::MatrixRow() : Columns(0), matrix(nullptr) {}

MatrixRow::MatrixRow(const int columns) : Columns(columns) {
    matrix = new int[Columns];
    for (int i = 0; i < Columns; ++i) {
        matrix[i] = 0;
    }
}

MatrixRow::~MatrixRow() {
    delete [] matrix;
}

int MatrixRow::getColumns() const {
    return Columns;
}

const int &MatrixRow::operator [](const int index) const {
    if (index >= Columns) {
        throw std::out_of_range("Index is out of range\n");
    }
    return matrix[index];
}

int &MatrixRow::operator [](const int index) {
    if (index >= Columns) {
        throw std::out_of_range("Index is out of range\n");
    }
    return matrix[index];
}

const MatrixRow &MatrixRow::operator *=(const int value) {
    for (int i = 0; i < Columns; ++i) {
        matrix[i] *= value;
    }
    return *this;
}

const MatrixRow MatrixRow::operator +(const MatrixRow &value) const {
    sizeException(value.getColumns());
    MatrixRow ans(Columns);
    for (int i = 0; i < Columns; ++i) {
        ans[i] = matrix[i] + value[i];
    }
    return ans;
}

const MatrixRow &MatrixRow::operator =(const MatrixRow &value) {
    delete [] matrix;
    Columns = value.getColumns();
    matrix = new int[Columns];
    for (int i = 0; i < Columns; ++i) {
        matrix[i] = value[i];
    }
    return *this;
}

bool MatrixRow::operator ==(const MatrixRow &value) const {
    sizeException(value.getColumns());
    for (int i = 0; i < Columns; ++i) {
        if (matrix[i] != value[i]) {
            return false;
        }
    }
    return true;
}

bool MatrixRow::operator !=(const MatrixRow &value) const {
    sizeException(value.getColumns());
    for (int i = 0; i < Columns; ++i) {
        if (matrix[i] != value[i]) {
            return true;
        }
    }
    return false;
}

void MatrixRow::printMatrix(std::ostream &fout) const {
    for (int i = 0; i < Columns; ++i) {
        fout << matrix[i] << " ";
    }
    fout << "\n";
}

void MatrixRow::sizeException(const int value) const {
    if (value != Columns) {
        throw "Matrix sizes are different\n";
    }
}

                    ////// MATRIX CLASS //////

Matrix::Matrix(const int rows, const int columns) : Columns(columns), Rows(rows) {
    matrix = new MatrixRow[Rows];
    for (int i = 0; i < Rows; ++i) {
        matrix[i] = MatrixRow(Columns);
    }
}

Matrix::Matrix(const Matrix &value) {
    matrix = new MatrixRow[value.getRows()];
    for (int i = 0; i < Rows; ++i) {
        matrix[i] = value[i];
    }
}

Matrix::~Matrix() {
    delete [] matrix;
}

int Matrix::getColumns() const {
    return Columns;
}

int Matrix::getRows() const {
    return Rows;
}

const MatrixRow &Matrix::operator [](const int index) const {
    if (index >= Rows) {
        throw std::out_of_range("Index is out of range\n");
    }
    return matrix[index];
}

MatrixRow &Matrix::operator [](const int index) {
    if (index >= Rows) {
        throw std::out_of_range("Index is out of range\n");
    }
    return matrix[index];
}

const Matrix &Matrix::operator *=(const int value) {
    for (int i = 0; i < Rows; ++i) {
        matrix[i] *= value;
    }
    return *this;
}

Matrix Matrix::operator +(const Matrix &value) const {
    sizeException(value.getRows());
    Matrix ans(Rows, Columns);
    for (int i = 0; i < Rows; ++i) {
        ans[i] = matrix[i] + value[i];
    }
    return ans;
}

Matrix &Matrix::operator =(const Matrix &value) {
    if (value == *this) {
        return *this;
    }
    delete [] matrix;
    Columns = value.getColumns();
    Rows = value.getRows();
    matrix = new MatrixRow[Rows];
    for (int i = 0; i < Rows; ++i) {
        matrix[i] = value[i];
    }
    return *this;
}

bool Matrix::operator ==(const Matrix &value) const {
    if (value.getColumns() != Columns || value.getRows() != Rows) {
        return false;
    }
    for (int i = 0; i < Rows; ++i) {
        if (matrix[i] != value[i]) {
            return false;
        }
    }
    return true;
}

bool Matrix::operator !=(const Matrix &value) const {
    if (value.getColumns() != Columns || value.getRows() != Rows) {
        return true;
    }
    for (int i = 0; i < Rows; ++i) {
        if (matrix[i] != value[i]) {
            return true;
        }
    }
    return false;
}

void Matrix::printMatrix(std::ostream &fout) const {
    for (int i = 0; i < Rows; ++i) {
        matrix[i].printMatrix(fout);
    }
    fout << "\n";
}

void Matrix::sizeException(const int value) const {
    if (value != Rows) {
        throw "Matrix sizes are different\n";
    }
}
