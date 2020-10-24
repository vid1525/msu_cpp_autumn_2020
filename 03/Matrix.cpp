#include <cstdlib>
#include <iostream>
#include <fstream>

class MatrixRow {
public:
    MatrixRow(const int columns);
    ~MatrixRow();
    int getColumns() const;

    virtual const MatrixRow &operator *=(const int value);
    virtual const MatrixRow &operator =(const MatrixRow &value);
    virtual int &operator[](const int index) const;
    virtual const MatrixRow operator +(const MatrixRow &value) const;
    virtual bool operator ==(const MatrixRow &value) const;
    virtual bool operator !=(const MatrixRow &value) const;
    virtual void printMatrix(std::ostream &fout) const;
protected:
    void sizeException(const int value) const;
    int Columns;
private:
    int *matrix;
};

MatrixRow::MatrixRow(const int columns) {
    Columns = columns;
    matrix = new int[columns];
}

MatrixRow::~MatrixRow() {
    delete [] matrix;
}

int MatrixRow::getColumns() const {
    return Columns;
}

int &MatrixRow::operator[](const int index) const {
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
    sizeException(value.getColumns());
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

///////////////////////////////////////////////////////

class Matrix : public MatrixRow {
public:
    Matrix(const int rows, const int columns) : MatrixRow(columns);
    ~Matrix();

    int getRows() const {
        return Rows;
    }

    const Matrix &operator *=(const int value) override;
    const Matrix &operator =(const Matrix &value) override;
    int &operator[](const int index) const override;
    const Matrix operator +(const Matrix &value) const override;
    bool operator ==(const Matrix &value) const override;
    bool operator !=(const Matrix &value) const override;
    void printMatrix(std::ostream &fout) const override;
private:
    MatrixRow *matrix;
    int Rows;
};

Matrix::Matrix(const int rows, const int columns) : MatrixRow(columns) {
    Rows = rows;
    Columns = columns;
    matrix = new MatrixRow *[rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new MatrixRow(columns);
    }
}
Matrix::~Matrix() {
    for (int i = 0; i < rows; ++i) {
        delete [] matrix[i];
    }
    delete [] matrix;
}

const Matrix &Matrix::operator *=(const int value) override {
    for (int i = 0; i < Rows; ++i) {
        matrix[i] *= value;
    }
    return *this;
}
const Matrix Matrix::&operator =(const Matrix &value) override;
int &Matrix::operator[](const int index) const override;
const Matrix Matrix::operator +(const Matrix &value) const override;
bool Matrix::operator ==(const Matrix &value) const override;
bool Matrix::operator !=(const Matrix &value) const override;
void Matrix::printMatrix(std::ostream &fout) const override;
